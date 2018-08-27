#!/bin/bash
function func(){
	#echo $1
	path=`ls $1`
	for f in $path
	do
	if [ -d $f ]
	then
	cur=`pwd`
	str="$cur/$f"
	echo $str
	func "$str"
	#echo $f
	else 
	echo $f
	fi
	done
}

#echo $a
func *
