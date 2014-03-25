#!/bin/sh

if [ ! -e project.txt ]; then
  read -p "Please input your project path: " p_path
  echo $p_path > project.txt
else
  read p_path < project.txt
fi

echo "Pull from origin master"
git pull --rebase origin master
echo "Done!"

echo "Sync Classes"
rsync -avr --delete Classes $p_path
echo "Done!"

echo "Sync Resources"
rsync -avr --delete Resources $p_path
echo "Done!"
