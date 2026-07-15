#Write a shell script which deletes all the even numbered lines in a text file.

echo "Enter the filename:"
read file

if [ ! -f "$file" ]; then
    echo "Error: File not found."
    exit 1
fi

sed -i '2~2 d' "$file"

echo "Even numbered lines deleted successfully "  