# !/bin/bash

echo "Enter a string: "
read s

n=${#s}
for((i=$n-1;i>=0;i--))
do
    rev="$rev${s:$i:1}"
done

echo "Reversed string: $rev"