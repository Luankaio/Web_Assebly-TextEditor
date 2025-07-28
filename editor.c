#include <string.h>
#include <stdlib.h>

// Defines ajustados para suporte ampliado
#define MAX_BUFFER 3000
#define MAX_PALAVRA 150

// ======================
// Estrutura da pilha
// ======================

typedef struct {
    char conteudo[MAX_BUFFER];
    int topo;
} Pilha;

Pilha pilhaTexto;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_BUFFER - 1;
}

void empilhar(Pilha *p, char caractere) {
    if (!pilhaCheia(p)) {
        p->conteudo[++p->topo] = caractere;
    }
}

char desempilhar(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->conteudo[p->topo--];
    }
    return '\0';
}

// ======================
// Lista para refazer
// ======================

typedef struct NoPalavra {
    char palavra[MAX_PALAVRA];
    struct NoPalavra* proximo;
} NoPalavra;

NoPalavra* cabecaRefazer = NULL;

void empilharPalavraRefazer(const char* palavra) {
    NoPalavra* novoNo = (NoPalavra*)malloc(sizeof(NoPalavra));
    strcpy(novoNo->palavra, palavra);
    novoNo->proximo = cabecaRefazer;
    cabecaRefazer = novoNo;
}

char* desempilharPalavraRefazer() {
    if (cabecaRefazer == NULL) return NULL;
    
    NoPalavra* temp = cabecaRefazer;
    cabecaRefazer = cabecaRefazer->proximo;
    char* resultado = strdup(temp->palavra);
    free(temp);
    return resultado;
}

void limparListaRefazer() {
    while (cabecaRefazer != NULL) {
        NoPalavra* temp = cabecaRefazer;
        cabecaRefazer = cabecaRefazer->proximo;
        free(temp);
    }
}

// ======================
// Núcleo funcional
// ======================

void inserirCaractere(char c) {
    empilhar(&pilhaTexto, c);
    // Limpa histórico ao inserir novo conteúdo
    if (c != ' ') {
        limparListaRefazer();
    }
}

void inserirStringUTF8(const char* str) {
    int comprimento = strlen(str);
    int posicao = 0;
    while (posicao < comprimento) {
        empilhar(&pilhaTexto, str[posicao++]);
    }
    if (str[0] != ' ') {
        limparListaRefazer();
    }
}

void apagarCaractere() {
    if (!pilhaVazia(&pilhaTexto)) {
        char removido = desempilhar(&pilhaTexto);
        
        // Trata caracteres multibyte UTF-8
        while (!pilhaVazia(&pilhaTexto) && (removido & 0xC0) == 0x80) {
            removido = desempilhar(&pilhaTexto);
        }
        
        limparListaRefazer();
    }
}

const char* obterTexto() {
    static char buffer[MAX_BUFFER + 1];
    for (int idx = 0; idx <= pilhaTexto.topo; idx++) {
        buffer[idx] = pilhaTexto.conteudo[idx];
    }
    buffer[pilhaTexto.topo + 1] = '\0';
    return buffer;
}

void desfazerPalavra() {
    if (pilhaVazia(&pilhaTexto)) return;

    char palavraTemp[MAX_PALAVRA];
    int contador = 0;

    // Coleta caracteres até espaço ou início
    while (!pilhaVazia(&pilhaTexto)) {
        char c = desempilhar(&pilhaTexto);
        palavraTemp[contador++] = c;
        if (c == ' ' || contador >= MAX_PALAVRA - 1) break;
    }

    // Inverte a sequência
    int inicio = 0, fim = contador - 1;
    while (inicio < fim) {
        char temp = palavraTemp[inicio];
        palavraTemp[inicio] = palavraTemp[fim];
        palavraTemp[fim] = temp;
        inicio++;
        fim--;
    }
    palavraTemp[contador] = '\0';

    empilharPalavraRefazer(palavraTemp);
}

void refazerPalavra() {
    char* palavra = desempilharPalavraRefazer();
    if (!palavra) return;

    int idx = 0;
    while (palavra[idx]) {
        empilhar(&pilhaTexto, palavra[idx++]);
    }
    free(palavra);
}

// Configuração inicial
void iniciarEditor() {
    inicializarPilha(&pilhaTexto);
    limparListaRefazer();
}

// Função auxiliar para debug
int tamanhoAtualPilha() {
    return pilhaTexto.topo + 1;
}