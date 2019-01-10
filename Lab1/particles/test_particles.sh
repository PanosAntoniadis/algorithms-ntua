#!/usr/bin/env bash

for i in $(seq 1 26);
do
    ./particles < $1/input$i.txt | python tester_particles.py $1/output$i.txt $i
done
echo "All done!";
