#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define MAX_WORDS 100
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

// ==============================
// Vetor de palavras desfeitas
// ==============================

char redoWords[MAX_WORDS][MAX_WORD_LEN];
int redoWordCount = 0;

// =======================
// Funções principais
// =======================

void insertChar(char c) {
    push(&textStack, c);
    redoWordCount = 0;  // limpa histórico de redo
}

void backspaceChar() {
    if (!isEmpty(&textStack)) {
        pop(&textStack);
        redoWordCount = 0;  // limpa histórico de redo
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

// Desfaz uma palavra e salva no vetor
void undoWord() {
    if (isEmpty(&textStack) || redoWordCount >= MAX_WORDS) return;

    char word[MAX_WORD_LEN];
    int i = 0;

    // Remove até espaço ou início da pilha
    while (!isEmpty(&textStack) && i < MAX_WORD_LEN - 1) {
        char c = pop(&textStack);
        word[i++] = c;
        if (isspace(c)) break;
    }

    // Inverte a palavra para armazenar corretamente
    for (int j = 0; j < i; j++) {
        redoWords[redoWordCount][j] = word[i - j - 1];
    }
    redoWords[redoWordCount][i] = '\0';
    redoWordCount++;
}

// Refaz a última palavra desfeita
void redoWord() {
    if (redoWordCount <= 0) return;

    redoWordCount--;
    char* word = redoWords[redoWordCount];

    for (int i = 0; word[i] != '\0'; i++) {
        push(&textStack, word[i]);
    }
}

// Inicializa o editor
void initEditor() {
    initStack(&textStack);
    redoWordCount = 0;
}
