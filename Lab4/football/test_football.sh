#!/bin/bash
g++ -o football -Wall -Wextra football.cpp

for i in `seq 1 14`;
do
    ./football < $1/input$i.txt | diff - $1/output$i.txt
done
echo "All ok"
