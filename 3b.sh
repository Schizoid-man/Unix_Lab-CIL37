#!/bin/bash

file_name="example.txt"
if [ -e "$file_name" ];
then
	echo "File name '$file_name' exists"
	mv "$file_name" "old_${file_name}"
	echo "Existing file name renamed to 'old_${file_name}'"

	touch "$file_name"
else
	echo "File '$file_name' doesnt exist. New empty file created"
	touch "$file_name"
fi
echo "Script execution completed"

