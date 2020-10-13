#!/bin/bash
IFS=$'\n'

rm valgrind.txt

valgrind --tool=callgrind ./a.out units/1.json units/2.json &> valgrind.txt