echo "Recursively renaming .txt files to .text "

find . -type f -name "*.txt" | while read file; do
    mv "$file" "${file%.txt}.text"
done

echo "Renaming done"