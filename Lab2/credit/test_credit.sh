#!/bin/bash
g++ -o credit -Wall -Wextra credit.cpp

for i in `seq 1 20`;
do
    ./credit < $1/input$i.txt | diff - $1/output$i.txt  
done
echo "All ok"
