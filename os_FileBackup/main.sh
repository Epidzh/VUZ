#!/bin/zsh
BACKUP_DIR="$(pwd)"
BACKUP_FOLDER_NAME="MY_BACKUP$(date "+%d.%m.%y%H:%M:%S")"
prev_backup_dir_list=()
COMPARE_MODE=1

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
    echo "$1"
    echo "$backup_list"
    shift
done

if [ "${#backup_list[@]}" -eq "0" ]
then
    read -p 'No arguments! Backup all objects? [y/n]: ' choice
    if [ "$choice" = "y" ]
    then
        backup_list=( "$(find "$BACKUP_DIR" -d 1)" )
    else
        exit
    fi
fi

# INIT BACKUP FOLDER AND COMPARE MODE
if [ ! -d "$BACKUP_DIR/$BACKUP_FOLDER_NAME" ]; then mkdir "$BACKUP_DIR/$BACKUP_FOLDER_NAME"; fi
touch "$BACKUP_DIR/$BACKUP_FOLDER_NAME/BACKUP_INFO"
prev_backup_dir_list=( "$(find "$BACKUP_DIR" -d 1)" )
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

# COMPARE PHASE
# if [ $COMPARE_MODE -eq 1 ]
# then
    
# fi