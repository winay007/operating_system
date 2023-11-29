#!/bin/bash  
# Function to perform addition 
addition() {     
	result=$(($1 + $2))     
	echo "Result: $result" 
}  

# Function to perform subtraction 
subtraction() {     
	result=$(($1 - $2))     
	echo "Result: $result"
}  

# Function to perform multiplication 
multiplication() {     
	result=$(($1 * $2))     
	echo "Result: $result" 
}  

# Function to perform division 
division() {     
	if [ $2 -ne 0 ]; then        
  		result=$(($1 / $2))        
  		echo "Result: $result"     
	else         
  		echo "Error: Division by zero is not allowed"     
	fi 
 }  
  
# Main script 
echo "Arithmetic Operations" 
echo "1. Addition" 
echo "2. Subtraction" 
echo "3. Multiplication" 
echo "4. Division"  
# Read the operation choice from the user 
echo -n "Enter your choice (1/2/3/4): " 
read choice  
case $choice in     
 1)         
	echo "Enter the first number: "         
	read num1         
	echo "Enter the second number: "         
	read num2         
	addition $num1 $num2         
	;;    
 2)         
 	echo "Enter the first number: "         
 	read num1         
 	echo "Enter the second number: "         
 	read num2         
 	subtraction $num1 $num2         
 	;;     
  3)         
 	echo "Enter the first number: "         
	read num1        
 	echo "Enter the second number: "         
  	read num2         
  	multiplication $num1 $num2         
  	;;     
  4)         
  	echo "Enter the dividend: "         
 	read num1        
 	echo "Enter the divisor: "         
   	read num2         
   	division $num1 $num2         
   	;;     
   *)         
   	echo "Invalid choice"         
   	;; 
 esac 
 
 
 
 
 
 
 
 
 