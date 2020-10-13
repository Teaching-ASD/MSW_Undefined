#!/bin/bash
valgrind --tool=callgrind ./a.out units/1.json units/2.json &> valgrind.txt