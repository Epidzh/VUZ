#!/bin/zsh
IFS=$'\n'
BACKUP_DIR="$(pwd)"
BACKUP_FOLDER_NAME="MY_BACKUP$(date "+%d.%m.%y_%H:%M:%S")"
prev_backup_dir_list=()
COMPARE_MODE=1
ROTATE_TIME_IN_SECONDS=604800 # ротация каждые 7 дней (= 604800s)

# ARGUMENT PARSING
backup_list=()
while [ -n "$1" ]
do
    if [ "$1" = "-d" ]
    then
        shift
        if [ -n "$1" ]
        then
            BACKUP_DIR="$1"
            echo "destination=$BACKUP_DIR"
        else
            echo "ERROR! Where is destination????"
            exit
        fi
    else
        if [[ -d "$1" || -f "$1" || -d "$(pwd)/$1" || -f "$(pwd)/$1" ]]
        then
            backup_list+=("$(realpath $1)")
        else
            echo "$1 doesn't exist!"
            exit
        fi
    fi
    shift
done

if [ "${#backup_list[@]}" -eq "0" ]
then
    echo "done!)"
    exit
fi

# INIT BACKUP FOLDER AND COMPARE MODE
prev_backup_dir_list=()
find "$BACKUP_DIR" -d 1 -name "MY_BACKUP??.??.??_??:??:??" -type d -atime +"$ROTATE_TIME_IN_SECONDS"s | while read line
do
    prev_backup_dir_list+=( "$line" )
done
if [ "${#prev_backup_dir_list[@]}" -eq "0" ]
then
    COMPARE_MODE=0
fi
if [ ! -d "$BACKUP_DIR/$BACKUP_FOLDER_NAME" ]; then mkdir "$BACKUP_DIR/$BACKUP_FOLDER_NAME"; fi
touch "$BACKUP_DIR/$BACKUP_FOLDER_NAME/BACKUP_INFO"

# BACKUPING
for i in $backup_list
do
    date=$(stat -f %m "$i")
    echo "$i@$date" >> "$BACKUP_DIR/$BACKUP_FOLDER_NAME/BACKUP_INFO"
    echo "$i"
    zip "$BACKUP_DIR/$BACKUP_FOLDER_NAME/backup.zip" "$i"
done

# ROTATION
if [ $COMPARE_MODE -eq 1 ]
then
    echo "delete old backups:\n$prev_backup_dir_list"
    for i in $prev_backup_dir_list; do
        rm -rf "$i"
    done
fi

unset IFS
open "$BACKUP_DIR/$BACKUP_FOLDER_NAME"