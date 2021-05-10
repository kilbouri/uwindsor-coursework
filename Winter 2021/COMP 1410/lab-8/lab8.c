/* ========================================
 * COMP-1410 Lab 8
 * ----------------------------------------
 * Name:                    Isaac Kilbourne
 * External Sources:        None
 * ========================================
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* create_node(int, struct node*, struct node*);
void free_tree(struct node*);
int height(struct node*);
int num_leaves(struct node*);

int main(void) {

    // empty tree test case
    assert(!height(NULL));
    assert(!num_leaves(NULL));

    /**
     * Tree from example:
     *     40
     *    /  \
     *   20  50
     *  /  \   \
     * 10  30  60
     * Height: 3
     * Leaves: 3
     */
    // From the handout: "Your testing should only use trees as an abstract data type".
    // You want to make me suffer by denying me access to my data? Here you go. Suffer in return.
    struct node* root = create_node(40,
        create_node(20,
            create_node(10, NULL, NULL),
            create_node(30, NULL, NULL)),
        create_node(50,
            NULL,
            create_node(60, NULL, NULL)));

    assert(height(root) == 3);
    assert(num_leaves(root) == 3);

    /**
     * Now we modify (as in recreate because modification isn't allowed)
     * the above tree to give a singular longest path
     *     40
     *    /  \
     *   20  50
     *  /  \   \
     * 10  30  60
     *           \
     *           70
     * Height: 4
     * Leaves: 3
     */
    free_tree(root);
    root = create_node(40,
        create_node(20,
            create_node(10, NULL, NULL),
            create_node(30, NULL, NULL)),
        create_node(50,
            NULL,
            create_node(60,
                NULL,
                create_node(70, NULL, NULL))));

    assert(height(root) == 4);
    assert(num_leaves(root) == 3);

    puts("[PASS] height()");
    puts("[PASS] num_leaves()");
    free_tree(root);
}

/**
 * Creates and returns a tree node containing given data and left/right leaves.
 * Caller must free. Returns NULL if allocation failed.
 */
struct node* create_node(int item, struct node* left, struct node* right) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    if (new_node) {
        new_node->data = item;
        new_node->left = left;
        new_node->right = right;
    }

    return new_node;
}

/**
 * Frees the memory associated with the given node and all of its children
 */
void free_tree(struct node* root) {
    if (root->left)
        free_tree(root->left);

    if (root->right)
        free_tree(root->right);

    free(root);
}

/**
 * Returns the height of the tree with given root
 */
int height(struct node* root) {
    if (!root) return 0; // recursive base case, empty tree (NULL root)

    int height_left = height(root->left);
    int height_right = height(root->right);

    return ((height_left > height_right) ? height_left : height_right) + 1;
}

/**
 * Returns the number of leaves in the tree with given root
 */
int num_leaves(struct node* root) {
    if (!root) return 0; // recursive base case, empty tree (NULL root)

    int leaves = num_leaves(root->left) + num_leaves(root->right);
    leaves = leaves ? leaves : 1;

    return leaves;
}