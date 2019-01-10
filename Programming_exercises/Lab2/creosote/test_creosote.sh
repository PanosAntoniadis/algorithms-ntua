#!/bin/bash
g++ -o creosote -Wall -Wextra creosote.cpp

for i in `seq 1 20`;
do
    ./creosote < testcases/input$i.txt | diff - testcases/output$i.txt
done
echo "All ok"
