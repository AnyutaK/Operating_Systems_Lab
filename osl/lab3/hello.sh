echo "Enter two numbers"
read a b
echo a is $a and b is $b

c=$((a/b))
c=`expr $a + $b`
echo $c