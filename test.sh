#!/bin/bash

for i in {1..1000}
do
  echo "asdsadasd asd,as fdasd " >> testfiles/$i".txt"
done

echo "Files are created in testfiles"
echo "Files are being removed"

`./rm_files /home/caglar/Codes/c/rm_files/testfiles/ txt`
