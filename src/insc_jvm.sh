#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage $0 <filename>"
    exit
fi

DIRNAME=`dirname $0`

INPUT=$1
OUTPUT_J="${INPUT%.*}.j"
OUTPUT_CLASSNAME=`basename "${INPUT%.*}"`
OUTPUT_CLASS_DIR=`dirname "${INPUT%.*}.class"`

${DIRNAME}/insc_jvm.bin ${INPUT} ${OUTPUT_CLASSNAME} > ${OUTPUT_J}
${DIRNAME}/lib/jasmin -d ${OUTPUT_CLASS_DIR} ${OUTPUT_J}
