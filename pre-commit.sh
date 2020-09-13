#!/bin/bash

ROOT_DIR=`git rev-parse --show-toplevel`
GREP_REGEX='VERSION [0-9]*\.[0-9]*\.[0-9]*'
SED_REGEX='VERSION \([0-9]*\.[0-9]*\)\.[0-9]*'
# `git diff HEAD` shows both staged and unstaged changes

if [[ -z `git diff HEAD` ]]; then
    exit 0
elif [[ -z `grep "$GREP_REGEX" $ROOT_DIR/CMakeLists.txt` ]]; then
    echo "$MSG"
else
	PATCH=$(git describe | cut -d'-' -f2)
	sed -i "s/$SED_REGEX/VERSION \1.$PATCH/" $ROOT_DIR/CMakeLists.txt
fi
