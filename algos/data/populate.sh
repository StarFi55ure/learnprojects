#!/usr/bin/zsh 

if [[ ! -e download_done ]]; then
    wget -c http://algs4.cs.princeton.edu/code/algs4-data.zip
    touch download_done
fi

