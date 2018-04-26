rem
rem Compile 32Bits, because EPSON_TWAIN Driver is 32bits DLL
rem ------------------------
title Microsoft Visual Studio 2017 C/C++ x86 /MD
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
rem ------------------------
for %%a in (
 libc12pri
 libc14image_rw_base
 libc16image_rw_tif
 libc18image_rw_tga
 lib_util
 libcpp31calcu_precision
 libcpp51iip_canvas
 libcpp52iip_rw
 libcpp53iip_precision
 libcpp55iip_scan
 libcpp56iip_opengl
 libcpp64iip_rot90
 libcpp69iip_scale_by_subpixel
 libcpp71iip_trace_by_hsv
 libcpp72iip_erase_dot_noise
 libcpp83gts_callback_and_action
 main
) do (
 echo ------ %%a ------
 pushd %%a
 nmake /f Makefile.vc all
 if errorlevel 1 goto err
 popd
)
rem ------------------------
goto end
:err
echo ------------ Error ------------
popd
:end
