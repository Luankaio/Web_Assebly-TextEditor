FROM emscripten/emsdk:3.1.50

WORKDIR /app

COPY . .

RUN emcc editor.c -o editor.js \
  -sEXPORTED_FUNCTIONS=_insertChar,_backspaceChar,_getText,_undoWord,_redoWord,_initEditor \
  -sEXPORTED_RUNTIME_METHODS=ccall,cwrap \
  -sALLOW_MEMORY_GROWTH=1

CMD python3 -m http.server 8080
