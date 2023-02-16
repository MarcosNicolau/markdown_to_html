#!/bin/bash

#---------------------------------------------------------------
#	A SCRIPT TO CONVERT MARKDOWN TO HTML CODE
#---------------------------------------------------------------

# A file is required, make sure it is provided before running the program
if [ -z $1 ]; then 
    echo "You must provide a file in order to generate html."
    echo "Pass --help or -h for more information about command"
    exit 1
fi

# Display help
Help()
{
    echo "Usage: markdown [OPTIONS] <FILE_TO_PARSE>"
    echo 
    echo "OPTIONS:"
    echo "-o    File name of the generated html (defaults to the name of the provided FILE)"
    echo "-c    CSS file to change use a custom style instead of default"
    echo "-t    HTML title, displayed in browser tab (defaults to file name)"
}

if [ $1 == "help" ]; 
  then Help
  exit
fi

# Initialize variables
FILE=""
OUTPUT_FILE_NAME="";
TITLE="";
STYLE_FILE="";
DEFAULT_STYLE_FILE="/home/marcos/Documents/programming/others/pandoc.css"


#Read options
while getopts ":oct" opt; do
  case $opt in
    o)
      OUTPUT_FILE_NAME=$OPTARG
      echo 1
      ;;
    c)
      STYLE_FILE=$OPTARG
      echo 2
      ;;
    t)
      TITLE=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done


echo $OUTPUT_FILE_NAME
echo $TITLE


# A regular expression is used to remove file extension
FILE_NAME_NO_EXT=${FILE%.*}
# Then with basename the path is deleted
FILE_NAME=`basename $FILE_NAME_NO_EXT`

# Default options if not provided

if [ -z $OUTPUT_FILE_NAME ]; then OUTPUT_FILE_NAME=$FILE_NAME.html
fi

if [ -z $STYLE_FILE]; then STYLE_FILE=$DEFAULT_STYLE_FILE
fi

if [ -z $TITLE ]; then TITLE=$FILE_NAME
fi


# Generate the html
# pandoc -s -c $STYLE_FILE $1 -f markdown -t html -o $OUTPUT_FILE_NAME --metadata title=$TITLE