#!/bin/zsh
BACKUP_DIR="$(pwd)"
BACKUP_FOLDER_NAME="MY_BACKUP$(date "+%d.%m.%y%H:%M:%S")"
FULL_BACKUP_MODE=0
prev_backup_dir_list=()

# ARGUMENT PARSING
backup_list=()
i=1
while [ -n "$1" ]
do
    if [ "$1" = "--full" ]
        then
            FULL_BACKUP_MODE=1
            backup_list=()
            break
    elif [ "$1" = "-d" ]
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

if [ "${#backup_list[@]}" -eq "0" ]
then
    echo "nothing to backup!"
    exit
fi

# INIT BACKUP FOLDER
if [ ! -d "$BACKUP_DIR/$BACKUP_FOLDER_NAME" ]; then mkdir "$BACKUP_DIR/$BACKUP_FOLDER_NAME"; fi
if [ FULL_BACKUP_MODE -eq 1 ]
    echo "FULL_BACKUP" > "$BACKUP_DIR/$BACKUP_FOLDER_NAME/README.md"
else
    echo "PARTLY_BACKUP" > "$BACKUP_DIR/$BACKUP_FOLDER_NAME/README.md"
    prev_backup_dir_list=( "$(find "$BACKUP_DIR" -d 1)" )
    if [ "${#prev_backup_dir_list[@]}" -eq "1" ]
    then
        echo "NOTHING TO COMPARE!"
        rm -rf "$BACKUP_DIR"
        exit
    fi
fi

# BACKUPING
for i in $backup_list
do
    if [ FULL_BACKUP_MODE -eq 1 ]
        cp -rf "$i" "$BACKUP_DIR/$BACKUP_FOLDER_NAME"
        echo "$i" >> "$BACKUP_DIR/$BACKUP_FOLDER_NAME/README.md $(stat -f %m $i)"
    else
        for j in prev_backup_dir_list
        do
            if [ -d "$j/$i" && "$(stat -f %m $i)" -ne "$(stat -f %m $j/$i)" ]
            then
                cp -rf "$i" "$BACKUP_DIR/$BACKUP_FOLDER_NAME"
                echo "$i" >> "$BACKUP_DIR/$BACKUP_FOLDER_NAME/README.md $(stat -f %m $i)"
            fi
        done
    fi
done