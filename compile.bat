@echo off

cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE "-DCMAKE_C_COMPILER:FILEPATH=gcc.exe" "-DCMAKE_CXX_COMPILER:FILEPATH=g++.exe" -Bbuild -G "MinGW Makefiles"
if not "%errorlevel%"=="0" (
    echo "build the makefile failed"
    exit /b 1
) else (
    echo Info: build the makefile success
)

cd build
make
if not "%errorlevel%"=="0" (
    echo "compile the project failed"
    exit /b 1
) else (
    echo Info: compile the project success
)

move Tanker.exe ../
cd ..
Tanker.exe
