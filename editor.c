#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_WORD_LEN 50

// =======================
// Pilha (Stack) para texto
// =======================

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

Stack textStack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->data[++s->top] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    }
    return '\0';
}

// =======================
// linked list para redo
// =======================

typedef struct WordNode {
    char word[MAX_WORD_LEN];
    struct WordNode* next;
} WordNode;

WordNode* redoHead = NULL;  // topo da pilha de palavras desfeitas

void pushRedoWord(const char* word) {
    WordNode* node = (WordNode*)malloc(sizeof(WordNode));
    strcpy(node->word, word);
    node->next = redoHead;
    redoHead = node;
}

char* popRedoWord() {
    if (redoHead == NULL) return NULL;
    WordNode* temp = redoHead;
    redoHead = redoHead->next;
    char* result = strdup(temp->word);  // copia a palavra antes de liberar
    free(temp);
    return result;
}

void clearRedoList() {
    while (redoHead != NULL) {
        WordNode* temp = redoHead;
        redoHead = redoHead->next;
        free(temp);
    }
}

// =======================
// Funções principais
// =======================

void insertChar(char c) {
    push(&textStack, c);
    clearRedoList();  // limpa histórico de redo ao digitar
}

void backspaceChar() {
    if (!isEmpty(&textStack)) {
        pop(&textStack);
        clearRedoList();  // limpa histórico de redo ao apagar
    }
}

const char* getText() {
    static char buffer[MAX_SIZE + 1];
    for (int i = 0; i <= textStack.top; i++) {
        buffer[i] = textStack.data[i];
    }
    buffer[textStack.top + 1] = '\0';
    return buffer;
}

// Desfaz uma palavra e salva na lista ligada
void undoWord() {
    if (isEmpty(&textStack)) return;

    char word[MAX_WORD_LEN];
    int i = 0;

    // Remove até espaço ou início da pilha
    while (!isEmpty(&textStack) && i < MAX_WORD_LEN - 1) {
        char c = pop(&textStack);
        word[i++] = c;
        if (isspace(c)) break;
    }

    // Inverter para armazenar corretamente
    for (int j = 0; j < i / 2; j++) {
        char temp = word[j];
        word[j] = word[i - j - 1];
        word[i - j - 1] = temp;
    }
    word[i] = '\0';

    pushRedoWord(word);
}

// Refaz a última palavra da lista ligada
void redoWord() {
    char* word = popRedoWord();
    if (!word) return;

    for (int i = 0; word[i] != '\0'; i++) {
        push(&textStack, word[i]);
    }
    free(word);  // liberar a cópia
}

// Inicializa o editor
void initEditor() {
    initStack(&textStack);
    clearRedoList();
}
