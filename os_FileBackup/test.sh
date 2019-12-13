IFS=$'\n'
files="$(find . -type f \( -perm -o+w \) -or \( -perm -g+w \) )"
all_files="$(find . -type f)"
echo "$all_files"
for i in $files
do
    echo "$(realpath $i) ; $(gstat -c '%a' $i) ;  $(gstat -c '%U' $i) ; $(gstat -c '%G' $i)"
    #echo "$(realpath $i) ; $(stat -f '%A' $i) ;  $(gstat -c '%U' file1) ; $(gstat -c '%G' file1)"
done