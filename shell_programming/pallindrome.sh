# !/bin/bash

echo "Enter a string: "
read s

j=$((${#s}-1))
i=0
while [[ $i < $j ]]                
do
    if [[ "${s:$i:1}" == "${s:$j:1}" ]]; then
        echo "" 
    else
        echo "Not pallindrome"
        exit 
    fi
    i=$((i+1))
    j=$((j-1))
done
    
echo "Pallindrome"