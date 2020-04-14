@echo off

xcopy /s %~dp0\dll\Release %~dp0\Build\bin\x64\Release
xcopy /s %~dp0\dll\Debug %~dp0\Build\bin\x64\Debug

call premake5.exe --file="premake5.lua" vs2019
call SimonSings.sln

echo.
echo Setup complete.
echo.

