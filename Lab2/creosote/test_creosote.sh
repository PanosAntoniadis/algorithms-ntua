#!/bin/bash
g++ -o creosote -Wall -Wextra creosote.cpp

for i in `seq 1 20`;
do
    ./creosote < $1/input$i.txt | diff - $1/output$i.txt
done
echo "All ok"
