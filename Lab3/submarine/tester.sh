#!/bin/bash
g++ -o submarine -Wall -Wextra submarine.cpp

for i in `seq 1 20`;
do
    ./submarine < testcases/input$i.txt | diff - testcases/output$i.txt
done
echo "All ok"
