#!/bin/sh

if [ ! -e project.txt ]; then
  read -p "Please input your project path: " p_path
  echo $p_path > project.txt
else
  read p_path < project.txt
fi

classes="$p_path/Classes"

echo "Copy Classes"
cp -rf $classes Classes
echo "Done!"

resources="$p_path/Resources"

echo "Copy Resources"
cp -rf $resources Resources
echo "Done!"

git status
echo "Add stage"
git add .
echo "Done!"

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
