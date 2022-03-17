#!/bin/bash

export count=0
echo a | for i in {1,2,3};do echo $count;count=$((count+1));export count;done
echo $count

echo "-------"

count=0
seq 1 3 | while read i;do echo $i $count;count=$((count+1));done
echo $count
