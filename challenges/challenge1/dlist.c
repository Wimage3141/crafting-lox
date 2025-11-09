#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
    struct Node *prev;
};

void printList(struct Node *head) {
    struct Node *temp = head;
    while(temp) {
        printf("%d\n", temp->val);
        temp = temp->next;
    }
}

void insert(struct Node *head, int newVal) {
    struct Node *newNode = malloc(sizeof (struct Node) );
    newNode->val = newVal;
    if(!head) {
        head = newNode;
        return;
    }

    if(!head->next) {
        head->next = newNode;
        newNode->prev = head;
        return;
    }

    struct Node *curr = head;

    while(curr->next) {
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->prev = curr;
}

void deleteNode(struct Node **head_ref, int delVal) {
    struct Node *head = *head_ref;
    if(!head) {
        printf("List is empty\n");
        return;
    }
    if(!head->next) {
        if(head->val == delVal) {
            head = NULL;
            return;
        }
    }

    if(head->val == delVal) {
        struct Node *new_head = head->next;
        head->next = NULL;
        new_head->prev = NULL;
        free(head);
        *head_ref = new_head;
        return;
    }

    struct Node *before = head;
    struct Node *after = head->next;

    while(head) {
        if(head->val == delVal) {
            struct Node *toDelete = head;
            before->next = before->next->next;
            after->prev = after->prev->prev;
            head = NULL;
            return;
        }
        before = head;
        head = head->next;
        if(head->next) after = head->next;
    }
}

// To test if it actually is a doubly linked list
void printBothWays(struct Node *head) {
    if(!head) printf("List is empty\n");
    if(!head->next) printf("%d\n", head->val);

    printf("Forward\n");
    while(head->next) {
        printf("%d\n", head->val);
        head = head->next;
    }

    printf("\nBackward\n");
    while(head) {
        head = head->prev;
        if(!head) return;
        printf("%d\n", head->val);
    }
}


int main() {
    struct Node *head = malloc(sizeof(struct Node));
    head->val = 20;
    
    insert(head, 30);
    insert(head, 40);
    insert(head, 50);
    insert(head, 60);
    insert(head, 70);

    printf("Before deletion:\n");
    printList(head);

    printf("After deletion:\n");
    deleteNode(&head, 20);
    printList(head);



    return 0;
}