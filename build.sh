#!/bin/bash
docker build -t editor-wasm .
docker run -it -p 8080:8080 editor-wasm
