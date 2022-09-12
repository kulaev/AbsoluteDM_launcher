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
cd debug/
cl   /DUNICODE /D_UNICODE /Zi /EHsc /nologo /I  external/include/  %cSourceFiles% /DEBUG:FULL  /link   /LIBPATH:external/lib  /OUT:"AbsoluteDM LauncherDEBUG.exe"