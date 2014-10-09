#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int value;
    struct Queue *next;
};

struct Queue *head, *tail;

void push(int x) {
    struct Queue *new_node = malloc(sizeof(struct Queue));
    new_node->value = x;
    new_node->next = NULL;
    if (tail == NULL) {
        head = tail = new_node;
    } else {
        head->next = new_node;
        head = new_node;
    }
}

int pop() {
    int value = tail->value;
    tail = tail->next;
    return value;
}

int main() {
    int n, i;
    head = tail = NULL;
    freopen("queue2.in",  "r", stdin);
    freopen("queue2.out", "w", stdout);
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
