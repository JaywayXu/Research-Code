#/bin/bash
if [[ -f $1 &&  ! -z $1 ]]
then 
    if [[ -f $3 && ! -z $3 ]]
    then
        if [[ -f $2 && ! -z $2 ]]
        then 
            cat $1 >> $3
            cat $2 >> $3
            cat $3
        else
            cat $1 >> $3
            cat $3
        fi
    else
        if [[ -f $2 && ! -z $2 ]]
        then
            echo "there is no file named $3, will input to the mydoc.txt"
            cat $1 >> "./mydoc.txt"
            cat $2 >> "./mydoc.txt"
            cat "./mydoc.txt"
        else
            echo "there is no files named $2 and $3"
            cat $1
        fi
    fi
else
    echo "there is no file named $1, please restart the shell!"
fi

