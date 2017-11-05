#!/bin/bash
set -e

if [ "$#" -ne 1 ]; then
    echo "Usage $0 <filename>"
    exit
fi

DIRNAME=`dirname $0`
LLVM_DIR="/home/students/inf/PUBLIC/MRJP/llvm37/"

INPUT=$1
OUTPUT_LL="${INPUT%.*}.ll"

${DIRNAME}/insc_llvm.bin ${INPUT} > ${OUTPUT_LL}
${LLVM_DIR}/bin/llvm-as ${OUTPUT_LL}
