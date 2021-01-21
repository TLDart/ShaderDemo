#!/bin/bash
if [ `ls | grep "compiled"` == "" ]; then
    mkdir compiled
fi
for fname in `ls *.cpp` 
do 
    g++ "$fname" -g -o "compiled/"`sed -E 's/\.cpp//'  <<<$fname` -lX11 -lglut -lGL -lGLU -lm -lGLEW 
done

./compiled/main 