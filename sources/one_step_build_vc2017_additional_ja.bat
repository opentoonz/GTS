rem
rem Compile 32Bits, because EPSON_TWAIN Driver is 32bits DLL
rem ------------------------
title Microsoft Visual Studio 2017 C/C++ x86 /MD
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
rem ------------------------
rem japanease version
rem
pushd libcpp83gts_callback_and_action
nmake /f Makefile_ja.vc all
if errorlevel 1 goto err
popd
pushd main
nmake /f Makefile.vc gts.exe inst_ja
if errorlevel 1 goto err
popd
rem ------------------------
goto end
:err
echo ------------ Error ------------
popd
:end
