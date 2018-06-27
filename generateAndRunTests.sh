#!/bin/bash

cd ./tests

for filename in *.dino; do
    cd ..
    ./compile.sh ./tests/${filename} "./tests/${filename}.c"
    gcc "./tests/${filename}.c" -o "./tests/${filename::-5}"
    ./tests/${filename::-5}
    echo
    cd ./tests
done