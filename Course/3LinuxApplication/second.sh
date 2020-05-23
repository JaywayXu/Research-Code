#!/bin/bash
while true
do
	echo "input the grade(input q to quit):"
	read grade
    if [ "q" = $grade ]
    then exit
	elif [ 60 -gt $grade ]
	then echo "Faild!"
    elif [ 70 -gt $grade ]
    then echo "Passed!"
    elif [ 80 -gt $grade ]
    then echo "Medium!"
    elif [ 90 -gt $grade ]
    then echo "Good!"
    elif [ 100 -ge $grade ]
    then echo "Excellent!"
    else echo "please input the current var!"
	fi
done
