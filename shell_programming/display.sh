#!/bin/bash

read -p "Enter your name: " name
echo "Welcome $name"
read -p "Enter number 1: " num1
read -p "Enter number 2: " num2  
echo "Addition of entered numbers: $(($num1 + $num2))" 