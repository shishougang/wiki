#!/bin/sh
git add .
if [[ $# -eq 1 ]]; then
    git commit -am "$1"
else
    git commit -am "update"
fi
git push
