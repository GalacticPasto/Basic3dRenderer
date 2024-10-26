@echo off
set includepath="C:\Program Files\vcpkg\installed\x64-windows\include"
set libpath="C:\Program Files\vcpkg\installed\x64-windows\lib"
set compilerFlags= -Wall -Werror 
::clang gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib ..\src\Basic3dRenderer.c -I%includepath% /link /libpath:%libpath%
pushd build

if exist ..\src\meshData.h del ..\src\meshData.h

clang ..\src\ObjFileParser.c -o ObjFileParser.exe 

ObjFileParser.exe

::cl gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib ..\src\Basic3dRenderer.c -I%includepath% /link /libpath:%libpath%
clang ..\src\Basic3dRenderer.c -o Basic3dRenderer.exe %compilerFlags% -L%libpath% -lraylib.lib -I%includepath% 

popd

