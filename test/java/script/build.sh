#!/bin/bash

SOURCES=`find -name *.java | paste -sd " " -`

mkdir classes
javac -d ./classes $SOURCES
