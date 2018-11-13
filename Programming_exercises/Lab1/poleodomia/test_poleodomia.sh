#!/usr/bin/env bash

for i in $(seq 1 20);
do
    ./poleodomia < $1/input$i.txt | python tester_poleodomia.py $1/output$i.txt $i
done
echo "All done!";
