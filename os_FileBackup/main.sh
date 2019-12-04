#!/bin/zsh
BACKUP_DIR="$(pwd)"
BACKUP_FOLDER_NAME="MY_BACKUP $(date "+%d.%m.%y %H:%M:%S")"

# ARGUMENT PARSING
backup_list=()
i=1
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
        backup_list+=( "$(pwd)/$1" )
    fi
    shift
done

if [ "${#backup_list[@]}" -eq "0" ]; then backup_list=( "$(find "$(pwd)" -d 1)"); fi

# CREATE BACKUP FOLDER
if [ ! -d "$BACKUP_DIR/$BACKUP_FOLDER_NAME" ]; then mkdir "$BACKUP_DIR/$BACKUP_FOLDER_NAME"; fi

# BACKUPING
for i in $backup_list
do
    cp -rf "$i" "$BACKUP_DIR/$BACKUP_FOLDER_NAME"
done