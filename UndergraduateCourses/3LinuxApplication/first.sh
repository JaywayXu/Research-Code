#!/bin/bash
while true
do
    echo "input the var:"
    read x
    case $x in
    P|p)
    	curPath=$(readlink -f $(dirname $0))
    	echo "The current path is: $curPath"
    	;;
    S|s)
    	curName=$(basename $0)
    	echo "The current path file name is: $curName"
        ;;
    D|d)
        curDateTime=`date +'%Y-%m-%d %H:%M:%S'`
        echo "The current date and time is: $curDateTime"
        ;;
    L|l)
        path=`cd $(dirname $0);pwd -P`
        echo "the current path is: $path"
        echo "the listing of files is:"
        for i in `ls`
        do
                echo $i
        done
        ;;
    W|w)
        echo "The user is: $USER"
        ;;
    Q|q)
        exit
        ;;
    *)
        echo "Please input the currect var!"
    esac
done
