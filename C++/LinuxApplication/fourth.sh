#!/bin/bash
curDateTime=`date +'%Y-%m-%d %H:%M:%S'`
echo "The current date and time is: $curDateTime"
a=`who -q | awk -F '#' '{print $1}'`
for i in $a
do
    write $i
done