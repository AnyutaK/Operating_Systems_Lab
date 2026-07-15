echo "Modifying files"

for file in *
do
    if [ -f "$file" ]; then
        sed -i 's/^ex:/Example:/g; s/\ Example:/ Example:/g' "$file"
        echo "modified $file"
    fi
done

echo "Modification done"