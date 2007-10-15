#!/bin/bash
#set -x

SCRIPT_DIRNAME=$(dirname $0)
CLASS_NAME=$1
REGEXP=s/%%class_name%%/$CLASS_NAME/g

cp $SCRIPT_DIRNAME/template.cpp $1.cpp
cp $SCRIPT_DIRNAME/template.h $1.h

for i in $(ls -1 $1.*); do
	$(sed -i $REGEXP $i)
done
