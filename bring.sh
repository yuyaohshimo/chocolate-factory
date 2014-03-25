#!/bin/sh

if [ ! -e project.txt ]; then
  read -p "Please input your project path: " p_path
  echo $p_path > project.txt
else
  read p_path < project.txt
fi

classes="$p_path/Classes"

echo "Sync Classes"
rsync -avr --delete $classes .
echo "Done!"

resources="$p_path/Resources"

echo "Sync Resources"
rsync -avr --delete $resources .
echo "Done!"

git status
echo "Add stage"
git add --all .
echo "Done!"
git status

echo "Commit"
read -p "Please input commit message: " c_msg
git commit -m "$c_msg"
echo "Done!"

echo "Pull origin master"
git pull --rebase origin master
echo "Done!"

echo "Push origin master"
git push origin master
echo "Done!"
