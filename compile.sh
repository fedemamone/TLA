#!/bin/bash

# check if the number of arguments are correct
if [ "$#" -ne 2 ]; then
    echo "Must specify the source and destination files as parameters"
    exit 1
fi

# check if the source file exists
FILE_SOURCE="$1"
if [ ! ${FILE_SOURCE: -5} == ".dino" ]; then
    echo "The source file must have .dino extension"
    exit 1
fi

if [ ! -e "${FILE_SOURCE}" ]; then
    echo "Source file ${FILE_SOURCE} doesn't exists"
    exit 1
fi

# check if the destination file exists, if so, remove it and create it again
FILE_DESTINATION="$2"
if [ ! ${FILE_DESTINATION: -2} == ".c" ]; then
    echo "The destination file must have .c extension"
    exit 1
fi

if [ -e "$FILE_DESTINATION" ]; then
    rm ${FILE_DESTINATION}
fi
touch ${FILE_DESTINATION}

FILE_DESTINATION_REAL_PATH=$(pwd)/${FILE_DESTINATION}
FILE_SOURCE_REAL_PATH=$(pwd)/${FILE_SOURCE}

# generate the code
cd src/generador
./generador < ${FILE_SOURCE_REAL_PATH} > ${FILE_DESTINATION_REAL_PATH}
cd ../..