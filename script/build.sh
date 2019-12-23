#!/bin/bash

swig -javascript -node -c++ exercise.i
node-gyp configure
node-gyp build
