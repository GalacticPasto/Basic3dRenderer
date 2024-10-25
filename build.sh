#!/bin/bash

set echo on 
if [ -f "src/meshData.h" ]; then 
    rm -rf src/meshData.h    
fi 
if [ -f "build/ObjFileParser" ]; then 
    rm -rf build/ObjFileParser    
fi 
if [ -f "build/Basic3dRenderer" ]; then 
    rm -rf build/Basic3dRenderer    
fi 

includeFlags="/home/galacticpast/Documents/raylib/src" 
linkerFlags="/home/galacticpast/Documents/raylib/src"

echo "parsing ObjFile"
gcc src/ObjFileParser.c -g -o build/ObjFileParser 

./build/ObjFileParser

echo "compiling BasicRenderer"
gcc src/Basic3dRenderer.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g -o build/Basic3dRenderer -I$includeFlags -L$linkerFlags 
