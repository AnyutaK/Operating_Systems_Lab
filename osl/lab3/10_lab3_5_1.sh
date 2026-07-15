#Write a program to copy all the files (having file extension input by the user) in the
#current folder to the new folder input by the user Example: user enter .text TEXT then all
#files with .text should be moved to TEXT folder. This should be done only at single
#level. i.e if the current folder contains a folder name ABC which has .txt files then
#these files should not be copied to TEXT.
#Write a shell script to modify all occurrences of “ex:” with “Example:” in all the filespresent
#in current folder only if “ex:” occurs at the start of the line or after a period (.). Example:
#if a file contains a line: “ex: this is first occurrence so should be re- placed” and “second
#ex: should not be replaced as it occurs in the middle of the sen-tence.”

echo "Enter the file extension:"
read ext
echo "Enter the destination folder:"
read newloc
mkdir -p "$newloc"
cp *"$ext" "$newloc"

echo "Copied files to $newloc"


