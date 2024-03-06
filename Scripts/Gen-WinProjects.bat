@echo off
pushd %~dp0\..\
call Tools\premake5\premake5.exe vs2022
popd
pause
