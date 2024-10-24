@echo off
set includepath="C:\Program Files\vcpkg\installed\x64-windows\include"
set libpath="C:\Program Files\vcpkg\installed\x64-windows\lib"
pushd build
::cl -FC -Zi /std:c++latest gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib ..\src\Try.cpp -I%includepath% /link /libpath:%libpath%
cl -FC -Zi /std:clatest gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib ..\src\3dGraphicsEngine.c -I%includepath% /link /libpath:%libpath%
popd
