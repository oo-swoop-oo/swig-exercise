#!/bin/bash

PACKAGE="-package com.domain.exercise"

swig -java -c++ $PACKAGE exercise.i

gcc -c \
    -fPIC \
    src/exercise.cpp \
    exercise_wrap.cxx \
    lib/cJSON.c \
    -I/usr/lib/jvm/default-java/include \
    -I/usr/lib/jvm/default-java/include/linux \
    -lcurl \
    -fexceptions

 gcc -shared \
    -fPIC \
    exercise.o \
    exercise_wrap.o \
    cJSON.o \
    -lcurl \
    -o libexercise.so

# ld -G exercise.o exercise_wrap.o cJSON.o -o libexercise.so
