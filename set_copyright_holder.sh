#!/bin/sh

if [ "X$*" = "X" ] ; then
	echo Please specify a new copyright holder as:
  echo $0 John and Jane Doe
	exit 1
else
	#echo $*
	if git ls-files 1> /dev/null ; then
		sed -i 's/<copyright holders>/'"$*"'/' $(git ls-files 2> /dev/null) 2> /dev/null
	else
		exit 1
	fi
fi

exit 0
