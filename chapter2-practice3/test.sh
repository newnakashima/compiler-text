#!/bin/bash
input1="a + b * c"
input2="(a + b) * c + d"
input3="a + b * c * (d + e)"
input4="a * b * c + d + e"
test1=$(./porland "$input1")
test2=$(./porland "$input2")
test3=$(./porland "$input3")
test4=$(./porland "$input4")
expected1="abc * +"
expected2="ab + c * d +"
expected3="abc * de + * +"
expected4="ab * c * d + e +"
echo "----- test start -----"
echo "input:    $input1"
echo "result:   $test1"
echo "expected: $expected1"
echo 
echo "input:    $input2"
echo "result:   $test2"
echo "expected: $expected2"
echo
echo "input:    $input3"
echo "result:   $test3"
echo "expected: $expected3"
echo
echo "input:    $input4"
echo "result:   $test4"
echo "expected: $expected4"
echo "----- test end -----"
