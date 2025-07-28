# Editor de Texto em C com Pilha

Este é um editor de texto simples implementado em C que utiliza uma estrutura de dados do tipo pilha para armazenar os caracteres digitados.

Front utiliza webassembly para utilizar o C como back-end

## Características

- **Pilha de caracteres**: Cada caractere digitado é empilhado
- **Exibição em tempo real**: O texto aparece na tela conforme você digita
- **Backspace funcional**: Remove o último caractere da pilha
- **Suporte a espaços múltiplos**: Preserva quantos espaços você quiser entre caracteres
- **Quebras de linha**: Suporte completo a Enter para múltiplas linhas
- **Tabulação**: Suporte a Tab para indentação
- **Caracteres especiais**: Suporte completo a acentos (á, é, í, ó, ú, ã, õ, ç) e caracteres UTF-8
- **Interface expansiva**: Editor com área de trabalho ampla e redimensionável
- **Undo/Redo**: Sistema de desfazer e refazer por palavras
- **Formatação**: Botões para negrito e itálico
- **Salvamento**: Exporta conteúdo como arquivo TXT

## Como usar

1. Compile o programa:
```bash
chmod +x build.sh
```

2. Execute o docker:
```bash
./build.sh
```