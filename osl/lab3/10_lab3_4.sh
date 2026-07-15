echo "enter basic salary:"
read basics
echo "enter TA:"
read ta
gross_salary=$(echo "$basics + $ta + 0.10 * $basics" | bc)
echo "Gross Salary: $gross_salary"
