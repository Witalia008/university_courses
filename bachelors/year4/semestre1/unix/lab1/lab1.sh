#!/bin/bash
IFS=''
if [[ $# = 2 ]]; then
    echo "Enter name of file:"
    read -r filename
    find $1/* -type f -name "$2*" -printf "%s %f\0" | sort -nz -r | tr '\0' '\n'  > $filename
fi
