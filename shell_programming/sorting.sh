# !/bin/bash

echo -n "Enter the Total numbers :"
read n
echo "Enter numbers :"
i=0


while [ $i -lt $n ]
do

	read a[$i]
	i=`expr $i + 1`
done

echo "Entered array of values: "
echo ${a[*]}

#sorting in ascending order

for((i=0;i<$n;i++))
do
	flag=0
	for((j = 0;j < $n-$i-1;j++))
	do
		if [[ ${a[$j]} -gt ${a[$j+1]} ]]  
		then
			temp=${a[$j]}
			a[$j]=${a[$j+1]}
	 		a[$j+1]=$temp
			flag=1
		fi 
	done
	if [[ $flag -eq 0 ]] 
	then 
		break
	fi
done

echo "Array after sorting using bubble sort: "
echo ${a[*]}