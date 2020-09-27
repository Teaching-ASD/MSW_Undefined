#!/bin/bash
IFS=$'\n'
FILE=output.txt


if test -f "$FILE"
then
rm $FILE
fi


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
DIFF=$(diff output.txt good.txt)

if [ "$DIFF" != "" ]
then
echo "Tests not passed!"
exit 1
else
exit 0
fi
