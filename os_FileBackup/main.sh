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
prev_backup_dir_list=()
find "$BACKUP_DIR" -d 1 -name "MY_BACKUP??.??.??_??:??:??" -type d | while read line
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
    cp -rf "$i" "$BACKUP_DIR/$BACKUP_FOLDER_NAME"
done

equal_backup_to_remove=()
old_backup_to_remove=()
if [ $COMPARE_MODE -eq 1 ]
then
    for i in $prev_backup_dir_list
    do
        info_file="$i/BACKUP_INFO"
        equal_count=0
        old_count=0
        for j in $backup_list
        do
            date=$(stat -f %m "$j")
            while IFS= read -r line; do
                filename="$(echo $line | rev | cut -d"@" -f2- | rev)"
                time=$(echo $line | rev | awk -F@ '{print $1}' | rev)
                if [[ "$j" = "$filename" && "$time" = "$date" ]]; then
                    ((equal_count+=1))    
                elif [[ "$j" = "$filename" && "$time" -lt "$date" ]]; then
                    ((old_count+=1))
                fi
            done < "$info_file"
        done
        if [ "$equal_count" -eq "${#backup_list[@]}" ]; then
            equal_backup_to_remove+=( "$i" )
        elif [ "$old_count" -eq "${#backup_list[@]}" ]; then
            old_backup_to_remove+=( "$i" )
        fi
    done
    if [ "${#equal_backup_to_remove[@]}" -gt "0" ]; then
        echo "There are some backups with equal content: $equal_backup_to_remove"
        read '?Delete them? [y/n]: ' choice
        if [ "$choice" = "y" ]
        then
            #backup_list=("${(@f)$(find "$BACKUP_DIR" -d 1)}")
            for i in $equal_backup_to_remove; do
                rm -r "$i"
            done
        fi
    fi

    if [ "${#old_backup_to_remove[@]}" -gt "0" ]; then
        echo "There are some backups with old content: $old_backup_to_remove"
        read '?Delete them? [y/n]: ' choice
        if [ "$choice" = "y" ]
        then
            #backup_list=("${(@f)$(find "$BACKUP_DIR" -d 1)}")
            for i in $old_backup_to_remove; do
                rm -r "$i"
            done
        fi
    fi
fi