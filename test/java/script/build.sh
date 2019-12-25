#!/bin/bash

SOURCES=`find -name *.java | paste -sd " " -`

mkdir -p classes
javac -d ./classes $SOURCES
