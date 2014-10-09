#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int value;
    struct Stack *next;
};

struct Stack *head;

void push(int x) {
    struct Stack *new_node = malloc(sizeof(struct Stack));
    new_node->value = x;
    new_node->next = head;
    head = new_node;
}

int pop() {
    int value = head->value;
    head = head->next;
    return value;
}

int main() {
    int n, i;
    head = NULL;
    freopen("stack2.in",  "r", stdin);
    freopen("stack2.out", "w", stdout);
    scanf("%d%*c", &n);
    for (i = 0; i < n; i++) {
        char cmd;
        scanf("%c%*c", &cmd);
        if (cmd == '+') {
            int value;
            scanf("%d%*c", &value);
            push(value);
        } else {
            printf("%d\n", pop());
        }
    }
    return 0;
}
