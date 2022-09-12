@ECHO OFF
SetLocal EnableDelayedExpansion
cd resources/
rc res.rc
cd..
cd src/
SET cSourceFiles=
FOR /R %%f in (*.c) do (
    if "%%~xf"==".c" SET cSourceFiles=!cSourceFiles! %%f
)
cd..
cd resources/
FOR /R %%f in (*.res) do (
    if "%%~xf"==".res" SET cSourceFiles=!cSourceFiles! %%f
)
cd..
cl /O2 /DNDEBUG /DUNICODE /D_UNICODE /I  external/include/  %cSourceFiles%  /DEBUG:NONE /link   /LIBPATH:external/lib /OUT:"release/AbsoluteDM Launcher.exe" 
SET objFiles=
FOR /R %%f in (*.obj) do (
    if "%%~xf"==".obj" SET objFiles=!objFiles! %%f
)
del %objFiles%
cd release/
"AbsoluteDM Launcher"