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

classes="$p_path/Classes"

echo "Copy Classes"
cp -rf Classes $classes
echo "Done!"

resources="$p_path/Resources"

echo "Copy Resources"
cp -rf Resources $resources
echo "Done!"
