# !/bin/bash

factorial(){
	#accessing first arguement
	args=$1
	if((args<=2)); then
		echo $args
	else
		f=$(factorial $((args-1)))	
		echo $((f*args))
	fi
}		


echo "Enter the value of n: "
read n
if((n==1)); then
	echo 1
else 
	factorial $n
fi
