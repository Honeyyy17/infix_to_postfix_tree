#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define the structure of a node
typedef struct Node {
    char info;
    struct Node *lchild, *rchild;
} Node;

// Stack structure for tree nodes
typedef struct Stack {
    Node *nodes[100];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *stack) {
    stack->top = -1;
}

// Push a node onto the stack
void push(Stack *stack, Node *node) {
    stack->nodes[++stack->top] = node;
}

// Pop a node from the stack
Node *pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->nodes[stack->top--];
}

// Create a new tree node
Node *createNode(char ch) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->info = ch;
    newNode->lchild = newNode->rchild = NULL;
    return newNode;
}

// Create an expression tree from a postfix expression
Node *createExpressionTree(char *postfix) {
    Stack stack;
    initStack(&stack);
    for (int i = 0; i < strlen(postfix); i++) {
        char ch = postfix[i];
        Node *newNode = createNode(ch);
        if (isalnum(ch)) { // Operand
            push(&stack, newNode);
        } else { // Operator
            newNode->rchild = pop(&stack);
            newNode->lchild = pop(&stack);
            push(&stack, newNode);
        }
    }
    return pop(&stack); // Root of the expression tree
}

// In-order traversal (infix form)
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->lchild);
        printf("%c ", root->info);
        inorder(root->rchild);
    }
}

// Pre-order traversal (prefix form)
void preorder(Node *root) {
    if (root != NULL) {
        printf("%c ", root->info);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

// Post-order traversal (postfix form)
void postorder(Node *root) {
    if (root != NULL) {
        postorder(root->lchild);
        postorder(root->rchild);
        printf("%c ", root->info);
    }
}

// Main function
int main() {
    char postfix[100];
    printf("Enter a valid postfix expression: ");
    scanf("%s", postfix);

    Node *root = createExpressionTree(postfix);

    printf("\nInfix Expression: ");
    inorder(root);

    printf("\nPrefix Expression: ");
    preorder(root);

    printf("\nPostfix Expression: ");
    postorder(root);

    return 0;
}