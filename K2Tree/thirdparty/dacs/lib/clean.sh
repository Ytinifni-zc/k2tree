#!/bin/bash

shopt -s extglob
rm -rf !(build.sh|clean.sh|.gitignore|..|.)  
