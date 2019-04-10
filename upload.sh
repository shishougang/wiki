#!/bin/sh
git add --all .
if [ $# -eq 1 ]; then
    git commit -am "$1"
else
    git commit -am "update"
fi
git push
