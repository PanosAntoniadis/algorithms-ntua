#!/bin/bash
g++ -o credit -Wall -Wextra credit.cpp

for i in `seq 1 20`;
do
    ./credit < testcases/input$i.txt | diff - testcases/output$i.txt  
done
echo "All ok"
