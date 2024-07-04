#!/bin/env bash
# ECEA 5305 Assignment 1
# Author: Travis Hunter

# Requirements
# 1. Accepts two arguments: the first is the full path to a file
#    and the second is a test string which will be written within
#    within the file
# 2. Exits with value 1 and print statements if any of the arguments
#    are not specified
# 3. Creates a new file with name and path specified, with contents
#    from the second argument

# Check that the number of arguments is exactly 2
if [ $# != 2 ]; then
	echo "writer.sh expects two arguments"
	echo "Usage: writer.sh [path to file] [contents to write]"
	exit 1
fi

# get the directory to put the file in.
DIRNAME=$(dirname $1)
# create the directory if it doesn't exist
mkdir -p $DIRNAME
if [ ! -d $DIRNAME ]; then
	echo "Unable to create directory $DIRNAME"
	exit 1
fi

# Now write the contents to the file, overwriting anything
# if it already exists
echo $2 > $1

