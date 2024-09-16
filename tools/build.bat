@echo off
REM Define paths

set "PROJECT_DIR=%~dp0..\"
set "BUILD_DIR=%PROJECT_DIR%builds"

REM Create builds directory if it doesn't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

REM Change to the project directory
cd /d "%PROJECT_DIR%"

REM Compile source files into object files
g++ -c main.cpp -I. -o "%BUILD_DIR%\tmp\main.o"
g++ -c commands.cpp -I. -o "%BUILD_DIR%\tmp\commands.o"
g++ -c writedatatofile.cpp -I. -o "%BUILD_DIR%\tmp\writedatatofile.o"
g++ -c writefiletodata.cpp -I. -o "%BUILD_DIR%\tmp\writefiletodata.o"
g++ -c hexthrutable.cpp -I. -o "%BUILD_DIR%\tmp\hexthrutable.o"
g++ -c tabletohex.cpp -I. -o "%BUILD_DIR%\tmp\tabletohex.o"

REM Link object files into the executable
g++ "%BUILD_DIR%\tmp\main.o" "%BUILD_DIR%\tmp\commands.o" "%BUILD_DIR%\tmp\writedatatofile.o" "%BUILD_DIR%\tmp\writefiletodata.o" "%BUILD_DIR%\tmp\hexthrutable.o" "%BUILD_DIR%\tmp\tabletohex.o" -o "%BUILD_DIR%\hexip.exe"
exit