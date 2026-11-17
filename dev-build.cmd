@echo off
rem Non-interactive version of build.bat: toolchain, XDK symbols (first time), then the game code.
setlocal
cd /d "%~dp0"
set "VSDIR=C:\Program Files\Microsoft Visual Studio\18\Community"
call "%VSDIR%\Common7\Tools\VsDevCmd.bat" -arch=amd64 -host_arch=amd64 >nul
set "VSCMAKE=%VSDIR%\Common7\IDE\CommonExtensions\Microsoft\CMake"
set "PATH=%VSCMAKE%\CMake\bin;%VSCMAKE%\Ninja;%VSDIR%\VC\Tools\Llvm\x64\bin;%PATH%"
clang++ --version | findstr /i version
echo [1] configure
cmake --preset release || exit /b 1
findstr /b /l /c:"[symbols]" config\game.toml >nul 2>nul && goto :game
echo [2] xbe_symbols
cmake --build out\build\release --target xbe_symbols || exit /b 2
set /p SDK=<out\build\release\sdk_dir.txt
out\build\release\xbe_symbols.exe assets\default.xbe "%SDK%\xdk" --library ObiWan.dll --out config\game.toml || exit /b 3
:game
if "%1"=="symbols" exit /b 0
echo [3] game code
cmake --build out\build\release || exit /b 4
rem The runtime rebuilds game code on start when the DLL is older than the exe (a runtime-only change relinks just
rem the exe), and it would build from whichever config sorts first: keep the DLL newer.
copy /b out\build\release\ObiWan.dll +,, out\build\release\ObiWan.dll >nul
echo BUILD OK
