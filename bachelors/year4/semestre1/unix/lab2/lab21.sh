#!/bin/bash

IFS=''
read -r rege <  "$3"
echo $rege

grep -o -E "$rege" $1 > $2
