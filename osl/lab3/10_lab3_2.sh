echo "enter folder"
read dir
echo "enter pattern to search"
read pat
if [ -d "$dir" ]; then
    echo "Files containing '$pat' in '$dir':"
    grep -l "$pat" "$dir"/* 
else
    echo "Directory $dir does not exist."
fi