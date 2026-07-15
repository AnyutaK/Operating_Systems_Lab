echo "enter the file or directory name"
read name
if [ -f "$name" ]; then
	echo "$name is a refular file";
elif [ -d "$name" ]; then
	echo "$name is a directory";
else 
	echo "$name is not valid ";
	exit 1
fi