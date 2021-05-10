#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* next;
};

void remove_from_list(struct node* lst1, struct node* lst2) {
    struct node* cur_node1 = lst1;
    struct node* temp;
    while (cur_node1 != NULL) {
        struct node* cur_node2 = lst2;
        while (cur_node2->next != NULL) {
            if (cur_node2->next && cur_node1->value == cur_node2->next->value) {
                temp = cur_node2->next->next;
                free(cur_node2->next);
                cur_node2->next = temp;
                continue; // we don't move forward until all matching nodes have been dropped
            }

            cur_node2 = cur_node2->next;
        }
        cur_node1 = cur_node1->next;
    }
}

struct node* create_node(int val, struct node* next) {
    struct node* n = (struct node*) malloc(sizeof(struct node));
    n->value = val;
    n->next = next;

    return n;
}

int main(void) {
    struct node* lst1 = create_node(1,
        create_node(3,
            NULL));
    struct node* lst2 = create_node(5,
        create_node(4,
            create_node(8,
                create_node(9,
                    create_node(4,
                        create_node(3,
                            create_node(3,
                                create_node(8,
                                    create_node(7,
                                        create_node(1,
                                            create_node(9,
                                                NULL)))))))))));
    remove_from_list(lst1, lst2);
    return 0;
}