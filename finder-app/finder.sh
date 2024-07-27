#!/bin/sh
# ECEA 5305 Assignment 1
# Author: Travis Hunter

# Requirements
# 1. Accepts 2 runtime arguments: the first is the path to a directory on the filesystem; the
#    second is a text string which will be searched within these files
# 2. Exits with return value 1 and print statements if any of the parameters were not specified
# 3. Exits with return value 1 and print statements if FILESDIR does not represent a directory on
#    the filesystem
# 4. Prints a message "The number of files are X and the number of matching lines are Y" where
#    X is the number of files in the directory and all subdirectories and Y is the number of
#    matching lines found in the respective files

# First check that we received 2 parameters to the script
if [ $# != 2 ]; then
	echo "finder.sh expects two arguments"
	echo "Usage: finder.sh [filesystem path] [search string]"
	exit 1;
fi

# Check that the first parameter is a valid path
if [ ! -d $1 ]; then
	echo "$1 does not exist."
	echo "Usage: finder.sh [filesystem path] [search string]"
	exit 1
fi

FILESDIR=$1
SEARCHSTR=$2

# Find the number of files and number of matching lines
NUMFILES=`find $1 -type f | wc -l`
NUMSTR=`grep -r $2 $1 | wc -l`
echo "The number of files are $NUMFILES and the number of matching lines are $NUMSTR"
