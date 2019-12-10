#!/bin/zsh
BACKUP_DIR="$(pwd)"
BACKUP_FOLDER_NAME="MY_BACKUP$(date "+%d.%m.%y_%H:%M:%S")"
prev_backup_dir_list=()
COMPARE_MODE=1

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
    read '?No arguments! Backup all objects? [y/n]: ' choice
    if [ "$choice" = "y" ]
    then
        #backup_list=("${(@f)$(find "$BACKUP_DIR" -d 1)}")
        find "$BACKUP_DIR" -d 1 | while read line; do
            backup_list+=( "$line" )
        done
    else
        exit
    fi
fi

# INIT BACKUP FOLDER AND COMPARE MODE
if [ ! -d "$BACKUP_DIR/$BACKUP_FOLDER_NAME" ]; then mkdir "$BACKUP_DIR/$BACKUP_FOLDER_NAME"; fi
touch "$BACKUP_DIR/$BACKUP_FOLDER_NAME/BACKUP_INFO"
prev_backup_dir_list=()
find "$BACKUP_DIR" -d 1 -name "MY_BACKUP??.??.??_??:??:??" -type d | while read line
do
    prev_backup_dir_list+=( "$line" )
done
if [ "${#prev_backup_dir_list[@]}" -eq "1" ]
then
    COMPARE_MODE=0
fi

# BACKUPING
for i in $backup_list
do
    cp -rf "$i" "$BACKUP_DIR/$BACKUP_FOLDER_NAME"
    echo "$i $(stat -f %m $i)" >> "$BACKUP_DIR/$BACKUP_FOLDER_NAME/BACKUP_INFO"
done

# COMPARE PHASE (if file in old backup is not find -> ask to delete this file; if all files in old backup updates in new backup -> ask to delete them)
if [ $COMPARE_MODE -eq 1 ]
then
    for i in $prev_backup_dir_list
    do
        
    done
fi