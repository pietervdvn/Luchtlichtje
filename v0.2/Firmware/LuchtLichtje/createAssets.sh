#! /bin/bash

append_file () {
    file=$1
    NAME=`echo $2 | sed "s/\..*$//"`
  	echo "$file --> $NAME"
  	echo -n "String $NAME = \"" >> "../Assets.ino"
  	cat $file | sed 's/\\/\\\\/g' | sed 's/"/\\"/g' | sed -z 's/\n/\\n/g'  >> "../Assets.ino"
  	echo "\";" >> "../Assets.ino"
  	echo >> "../Assets.ino"
  	
}

# Note: the order of inclusion is sorted by Ascii of the filename.
# Assets should be imported first
# THus: we need an UPPERCASE A to get started
cd assets
echo "// All assets are saved here" > "../Assets.ino"

for file in *
do
  if [[ $file != "landing.html" ]]
  then
	  append_file $file $file
	fi
done 

echo "#if PEDESTRIAN_LIGHT" >> "../Assets.ino"
	echo -n "String landing = \"" >> "../Assets.ino"
	cat landing.html | grep -v "<!-- bicycle only -->" | sed 's/\\/\\\\/g' | sed 's/"/\\"/g' | sed -z 's/\n/\\n/g'  >> "../Assets.ino"
	echo "\";" >> "../Assets.ino"
	echo >> "../Assets.ino"
echo "#else"	>> "../Assets.ino"
append_file "landing.html" "landing"
echo "#endif"	>> "../Assets.ino"
