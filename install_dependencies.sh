#!/usr/bin/env bash

cd ${OF_ROOT:-$HOME/software/openframeworks}/addons

for repo in https://github.com/turiphro/ofxRPiTouch.git https://github.com/256dpi/ofxMQTT.git; do
    name=${repo##*/}
    name=${name%.*}
    if [ -d "$name" ]; then
        echo "Already installed: $PWD/$name"
    else
        echo "Installing $repo to $PWD/$name"
        git clone $repo
    fi;
done
