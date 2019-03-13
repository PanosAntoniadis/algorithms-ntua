#!/bin/bash
g++ -o submarine -Wall -Wextra submarine.cpp

for i in `seq 1 20`;
do
    ./submarine < $1/input$i.txt | diff - $1/output$i.txt
done
echo "All ok"
