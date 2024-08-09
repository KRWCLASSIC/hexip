@echo off
REM Define paths

set "PROJECT_DIR=%~dp0"
set "BUILD_DIR=%PROJECT_DIR%builds"

REM Create builds directory if it doesn't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

REM Change to the project directory
cd /d "%PROJECT_DIR%"

REM Compile source files into object files
g++ -c main.cpp -I. -o "%BUILD_DIR%\main.o"
g++ -c commands.cpp -I. -o "%BUILD_DIR%\commands.o"
g++ -c writedatatofile.cpp -I. -o "%BUILD_DIR%\writedatatofile.o"
g++ -c writefiletodata.cpp -I. -o "%BUILD_DIR%\writefiletodata.o"
g++ -c hexthrutable.cpp -I. -o "%BUILD_DIR%\hexthrutable.o"
g++ -c tabletohex.cpp -I. -o "%BUILD_DIR%\tabletohex.o"

REM Link object files into the executable
g++ "%BUILD_DIR%\main.o" "%BUILD_DIR%\commands.o" "%BUILD_DIR%\writedatatofile.o" "%BUILD_DIR%\writefiletodata.o" "%BUILD_DIR%\hexthrutable.o" "%BUILD_DIR%\tabletohex.o" -o "%BUILD_DIR%\hexip.exe"

REM Open a new command prompt window in the builds directory
cd builds
start cmd
cd ..
exit