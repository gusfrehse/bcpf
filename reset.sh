#!/bin/bash


read -p "Continue? (y/n) " choice
case "$choice" in
    y|Y )
        echo Resetting...
        cp template.cpp prog.cpp
        rm test.txt
        touch test.txt
        echo Done.;;
    * ) 
        echo Cancelled.
        exit;;
esac

