#!/bin/bash
IFS=$'\n'

rm output.txt

for i in 1 2 3
do 
    for j in 1 2 3
    do
    if [ $i != $j ]
    then
           ./$1 units/$i.json units/$j.json >> output.txt
    fi
    done
done