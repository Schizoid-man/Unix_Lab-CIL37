#!/bin/bash

space_usage=$(df -h / | awk 'NR==2 {print $5}' | sed 's/%//')
echo "System Space usage: $space_usage%"
if [ "$space_usage" -gt 80 ];
then 
	echo "Low System Space"
	echo "Files larger than 1GB"
	find / -type f -size +1G -exec ls -lh {} \; 2>/dev/null
	if [ $? -ne 0 ];
	then
		echo "No files larger than 1GB found / insufficient permissions"
	fi
else
	echo "System Space Usage is under control"
fi
