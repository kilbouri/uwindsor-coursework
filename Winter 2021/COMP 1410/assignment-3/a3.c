/* ========================================
 * COMP-1410 Assignment 3
 * ----------------------------------------
 * Student name:            Isaac Kilbourne
 * External Sources:        None
 * ========================================
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct snode {
    int id;
    char* name;
    struct snode* next;
};
struct slist {
    struct snode* head;
};
struct treenode {
    char word[10];
    int value;
    struct treenode* left;
    struct treenode* right;
};

struct slist* create_list();
struct snode* create_snode(int id, char* name);
void free_node(struct snode*);
void free_nodes(struct snode* node);
bool insert_student(int, char[], struct slist*);
bool remove_student(int, struct slist*);
char* find_student(int, struct slist*);
void free_list(struct slist*);
void merge_lists(struct slist* out, struct slist*, struct slist*);
bool check_sorted(struct slist* list);

struct treenode* create_node(char[10], int);
struct treenode* insert_node(char[10], int, struct treenode*);
int lookup_word(char[], struct treenode*);
void free_tree(struct treenode*);
void test();

int main(void) {

    test();

    char input[10] = { 0 };
    struct treenode* tree = NULL;
    int id = 1;
    while (true) {
        scanf(" %9s", input);
        if (!strcmp(input, ".")) break;

        int result = lookup_word(input, tree);
        if (result) printf("%d ", result);
        else {
            printf("%s ", input);
            tree = insert_node(input, id++, tree);
        }
    }

    return 0;
}

/**
 * Creates an empty student list (NULL head).
 * The list is sorted by ascending student IDs.
 * Caller must free.
 */
struct slist* create_list() {
    struct slist* lst;
    lst = (struct slist*) malloc(sizeof(struct slist));

    if (lst)
        lst->head = NULL;

    return lst;
}

/**
 * Creates a new student record
 */
struct snode* create_snode(int id, char* name) {
    struct snode* node = NULL;
    node = (struct snode*) malloc(sizeof(struct snode));

    if (node) {
        char* str = (char*) calloc(1 + strlen(name), sizeof(char));
        strcpy(str, name);

        node->id = id;
        node->name = str;
        node->next = NULL;
    }

    return node;
}

/**
 * Frees the memory associated with the provided student record.
 */
void free_node(struct snode* node) {
    free(node->name);
    free(node);
}

/**
 * Attempts to add a student with given ID and name to the given list.
 * Returns false if the student already exists (by ID), otherwise modifies
 * the list and returns true.
 */
bool insert_student(int id, char name[], struct slist* lst) {
    struct snode* new_node = create_snode(id, name);

    // empty list or "lowest ID" condition
    if (lst->head == NULL || id < lst->head->id) {
        new_node->next = lst->head;
        lst->head = new_node;
        return true;
    }

    struct snode* current = lst->head;

    while (current->next != NULL && current->next->id <= id)
        current = current->next;

    // matching ID found
    if (id == current->id)
        return false;

    // current has the highest ID less than that of the node we are adding
    new_node->next = current->next;
    current->next = new_node;

    return true;
}

/**
 * Attempts to remove a student with given ID from the provided list.
 * Returns false if the student was not found. If a matching record is found,
 * true is returned and the memory associated is freed.
 */
bool remove_student(int id, struct slist* lst) {

    // case: empty list OR ID is less than the first node's ID
    if (lst->head == NULL || id < lst->head->id)
        return false;

    // case: id is that of the head node, so we're removing the head
    if (id == lst->head->id) {
        struct snode* to_free = lst->head;
        lst->head = lst->head->next;

        free_node(to_free);
        return true;
    }

    // finds the node that preceeds the node to remove, or the last if it didn't exist
    struct snode* current = lst->head;
    while (current->next != NULL && current->next->id < id)
        current = current->next;

    // if the ID is not a match, we hit the end of the list without finding the ID
    if (current->id != id)
        return false;

    // current is now the node preceeding the one to free
    struct snode* to_free = current->next;
    current->next = to_free->next;

    free_node(to_free);
    return true;

}

/**
 * Returns the name of the student with the matching ID, or null if no
 * suitable record was found. The returned string is dynamically allocated
 * and must be freed by the caller or by removing the record entirely.
 */
char* find_student(int id, struct slist* lst) {
    // finds the node with matching ID or the last node if no match was found
    struct snode* current = lst->head;
    while (current->next != NULL && current->next->id <= id)
        current = current->next;

    if (current->id == id)
        return current->name;

    return NULL;
}

/**
 * Frees an entire list and its associated nodes.
 */
void free_list(struct slist* lst) {
    if (lst->head)
        free_nodes(lst->head);
    free(lst);
}

/**
 * Utility for freeing all nodes following the given node
 */
void free_nodes(struct snode* node) {
    if (node->next)
        free_nodes(node->next);

    free_node(node);
}

/**
 * Merges the student records from two provided lists into the provided
 * output list. Frees the two original lists once the merge is completed.
 * In the event of an ID collision, the student from lst1 will be used.
 * Requires that the output list starts completely empty.
 */
void merge_lists(struct slist* out, struct slist* lst1, struct slist* lst2) {
    // these keep track of where we are in each list
    struct snode* node_a = lst1->head;
    struct snode* node_b = lst2->head;
    struct snode* node_out = NULL;

    struct snode* to_append = NULL;
    while (node_a != NULL || node_b != NULL) {
        // ugly but works... determines the node to append
        if (node_a == NULL) {
            to_append = node_b;
            node_b = node_b->next;
        } else if (node_b == NULL) {
            to_append = node_a;
            node_a = node_a->next;
        } else if (node_a->id < node_b->id) {
            to_append = node_a;
            node_a = node_a->next;
        } else if (node_b->id < node_a->id) {
            to_append = node_b;
            node_b = node_b->next;
        } else {
            to_append = node_a;
            node_a = node_a->next;
            node_b = node_b->next;
        }

        // we haven't set the head node of the out list yet!
        if (node_out == NULL) {
            out->head = to_append;
            node_out = to_append;
        } else {
            node_out->next = to_append;
            node_out = to_append;
        }
    }

    // free not free_list is used because we need to maintain the data in the nodes
    free(lst1);
    free(lst2);
}

/**
 * Checks if a list is sorted or not.
 */
bool check_sorted(struct slist* list) {
    if (!list || !list->head) return true;

    int prev = list->head->id;
    for (struct snode* curr = list->head->next; curr != NULL; curr = curr->next)
        if (curr->id <= prev) return false;

    return true;
}

/**
 * Creates a new tree node with the given word and value.
 */
struct treenode* create_node(char word[], int val) {
    struct treenode* node = (struct treenode*) calloc(1, sizeof(struct treenode));
    strncpy(node->word, word, 9);
    node->value = val;

    return node;
}

/**
 * Inserts a new node containing the given word and value into the tree with
 * the given root (or NULL, denoting an empty tree). If the word already exists
 * within the tree, the value will be updated. Returns the new root node.
 */
struct treenode* insert_node(char word[], int value, struct treenode* tree) {
    if (!tree) return create_node(word, value);

    int cmp = strcmp(word, tree->word);

    if (!cmp) tree->value = value;
    else if (cmp < 0 && tree->left) insert_node(word, value, tree->left);
    else if (0 < cmp && tree->right) insert_node(word, value, tree->right);
    else if (cmp < 0) tree->left = create_node(word, value);
    else if (0 < cmp) tree->right = create_node(word, value);

    return tree;
}

/**
 * Returns the numeric value associated with the given word in the tree, or 0
 * if the word does not appear in said tree. Requires the tree meets the sorting
 * property.
 */
int lookup_word(char word[10], struct treenode* tree) {
    if (!tree) return 0;

    int cmp = strcmp(word, tree->word);
    if (cmp < 0) return lookup_word(word, tree->left);
    if (0 < cmp) return lookup_word(word, tree->right);

    return tree->value;
}

/**
 * Frees all memory associated in the tree with given root node
 */
void free_tree(struct treenode* tree) {
    if (!tree) return; // prevent seg faults when tree is NULL
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

/**
 * I hate staring at test code.
 */
void test() {

    /**
     * find_student
     */
    struct slist* l1 = create_list();
    insert_student(3872, "3872a", l1);
    insert_student(4414, "4414a", l1);
    insert_student(4280, "4280a", l1);
    insert_student(1439, "1439a", l1);
    insert_student(2865, "2865a", l1);
    insert_student(2221, "2221a", l1);
    insert_student(2090, "2090a", l1);

    struct slist* l2 = create_list();
    insert_student(21, "", l2);
    insert_student(1568, "1568b", l2);
    insert_student(1816, "1816b", l2);
    insert_student(1344, "1344b", l2);
    insert_student(1963, "1963b", l2);
    insert_student(2221, "2221b", l2);
    insert_student(2090, "2090b", l2);

    assert(!strcmp("2090a", find_student(2090, l1)));
    assert(!strcmp("4414a", find_student(4414, l1)));
    assert(!strcmp("2090b", find_student(2090, l2)));
    assert(!strcmp("", find_student(21, l2)));
    puts("[PASS] find_student()");

    /**
     * merge_lists
     */
    struct slist* merged = create_list();
    merge_lists(merged, l1, l2);
    assert(check_sorted(merged));

    free_list(merged);
    merged = create_list();
    struct slist* l3 = create_list();
    insert_student(3872, "3872a", l3);
    insert_student(4414, "4414a", l3);
    insert_student(4280, "4280a", l3);
    insert_student(1439, "1439a", l3);
    insert_student(2865, "2865a", l3);
    insert_student(2221, "2221a", l3);
    insert_student(2090, "2090a", l3);
    merge_lists(merged, l3, create_list());
    assert(check_sorted(merged));
    puts("[PASS] merge_lists()");

    /**
     * lookup_word()
     */
    struct treenode* root = NULL;

    char* words[] = {
        // generated with Random Everything for VS Code
        "lion", "remove", "something", "round", "ship",
        "foreign", "brown", "said", "turn", "pole",
        "nails", "share", "pictured", "solve", "threw",
        "garage", "situation", "somebody", "front", NULL
    };

    // first we build the tree
    for (int i = 0; words[i] != NULL; i++)
        root = insert_node(words[i], i, root);

    // then we check all words get looked up correctly
    for (int i = 0; words[i] != NULL; i++)
        assert(i == lookup_word(words[i], root));

    // a special case: adding a word that already exists
    root = insert_node(words[0], 99, root);
    assert(99 == lookup_word(words[0], root));

    // a special case: finding a word in an empty tree
    assert(0 == lookup_word("o_o", NULL));

    // a final special case: finding a word that doesn't exist
    assert(0 == lookup_word("snafu", root));

    puts("[PASS] lookup_word()");

}