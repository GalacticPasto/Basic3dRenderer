@echo off
mkdir build
set compilerflags= -FAsc -Zi /std:clatest
set includeflags=-I"D:\Projects\raylib-5.0_win64_msvc16\include" 
::                  set ^^^^^^^^^ this to your raylib include folder path 
set linkerflags= gdi32.lib msvcrt.lib winmm.lib opengl32.lib shell32.lib raylib.lib user32.lib   /link /libpath:"D:\Projects\raylib-5.0_win64_msvc16\lib" /NODEFAULTLIB:libcmt
::                                                                                                          set      ^^^^ this to your raylib lib folder
pushd build

if exist ..\src\meshData.h del ..\src\meshData.h

cl ..\src\ObjFileParser.c %compilerFlags% %linkerflags% 

ObjFileParser.exe

cl ..\src\Basic3dRenderer.c %compilerflags% %includeflags% %linkerflags%
popd 
