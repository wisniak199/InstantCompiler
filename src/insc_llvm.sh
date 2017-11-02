#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage $0 <filename>"
    exit
fi

DIRNAME=`dirname $0`
LLVM_DIR="/home/wisniak199/mrjp/llvm-3.7.0/"

INPUT=$1
OUTPUT_LL="${INPUT%.*}.ll"

${DIRNAME}/insc_llvm.bin ${INPUT} > ${OUTPUT_LL}
${LLVM_DIR}/bin/llvm-as ${OUTPUT_LL}
