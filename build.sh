#!/bin/bash
echo "Construindo editor WebAssembly com suporte UTF-8..."
docker build --no-cache -t editor-wasm .
echo "Iniciando servidor..."
docker run -it -p 8080:8080 editor-wasm
