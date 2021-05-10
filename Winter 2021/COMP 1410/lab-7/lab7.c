/* ========================================
 * COMP-1410 Lab 7
 * ----------------------------------------
 * Name:                    Isaac Kilbourne
 * External Sources:        None
 * ========================================
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct strnode {
    char str[5];
    struct strnode* next;
};

struct strnode* create_node(char*, struct strnode*);
struct strnode* free_node(struct strnode*);
void concat_nodes(struct strnode*, char*);
void test();

int main(void) {
    test(); // moved to a function so I don't have to stare at it

    // since we pass the NEXT pointer, and not the previous,
    // the list should be assembled in reverse.
    struct strnode* head = NULL;
    for (char a = 'Z'; a >= 'A'; a--) {
        head = create_node((char[]) { a, 0 }, head);
    }

    char concat[64] = { 0 }; // 64 chars is ample space for the expected 51-char result
    concat_nodes(head, concat);
    assert(!strcmp("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z", concat));
    return 1;
}

/**
 * creates a strnode containing str and given next poiner.
 * Caller must free with free_node.
 * Returns NULL if memory failed to be allocated.
 */
struct strnode* create_node(char* str, struct strnode* next) {
    struct strnode* node;
    node = (struct strnode*)calloc(sizeof(struct strnode), 1);

    if (node == NULL) return NULL;

    strncpy(node->str, str, 4);
    node->next = next;
    return node;
}

/**
 * Frees the strnode at the provided pointer. Returns a pointer to the
 * next node in the list, or NULL.
 */
struct strnode* free_node(struct strnode* node) {
    void* head = node->next; // a pointer is a pointer
    free(node);
    return head;
}

/**
 * Stores a the space-separated string of the values
 * formed by the list starting at the provided head node.
 * Requires str points to enough memory to store the result.
 */
void concat_nodes(struct strnode* head, char* str) {
    struct strnode* current_node = head;
    int arr_pos = 0;
    for (; current_node != NULL; current_node = current_node->next) {
        strncpy(str + arr_pos, current_node->str, 4);
        short len = strnlen(current_node->str, 4);
        if (len != 0) {
            arr_pos += len;
            str[arr_pos++] = ' ';
        }
    }
    str[arr_pos - 1] = 0;
}

/**
 * Tests the 3 functions. Moved to its own function so I didn't have to
 * stare at the tests while writing the rest of the code.
 */
void test() {
    struct strnode* tail = create_node("", NULL);
    struct strnode* body = create_node("Body with long text followed by a tail with empty text", tail);
    struct strnode* head = create_node("Head", body);

    // string matching
    assert(!strcmp("", tail->str));
    assert(!strcmp("Body", body->str));
    assert(!strcmp("Head", head->str));

    // pointer matching
    assert(tail->next == NULL);
    assert(body->next == tail);
    assert(head->next == body);
    puts("[PASS] create_node");

    char result[16] = { 0 };
    concat_nodes(head, result);
    assert(!strcmp(result, "Head Body"));

    concat_nodes(body, result);
    assert(!strcmp(result, "Body"));

    concat_nodes(tail, result);
    assert(!strcmp(result, ""));
    puts("[PASS] concat_nodes");

    assert(free_node(head) == body);
    assert(free_node(body) == tail);
    assert(free_node(tail) == NULL);
    puts("[PASS] free_node");
}