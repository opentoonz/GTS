# [GTS](https://opentoonz.github.io/e/index.html)  ([日本語](./README_ja.md))

## What is GTS?

GTS is a scanning tool developed by Studio Ghibli.

It's specialized in hand-drawn animation frames.

## Specification

GTS uses TWAIN on Windows and SANE on other operating systems, so you need scanner drivers that support these APIs in order to run it.

The interface is in English and scanned images are saved as TIFF/Targa.

## Requirements

Please refer to the [OpenToonz site](https://opentoonz.github.io/e/index.html).

## Installation (Windows)

[Download](https://github.com/opentoonz/GTS/releases) and unzip the most recent GTS-x.y.z.zip file.

## How to Execute (Windows)

Execute "./gts" in the unzipped folder.

## How to Build Locally (Windows)

1. Environment for development

 Microsoft Visual C++ 2017 (tested on a Windows 7 Enterprise SP1)

2. Get source code

 Get the source code from Github:
 ```sh
 $ git clone https://github.com/opentoonz/GTS.git
 ```

3. Get third party libraries

 - Unzip third party libraries on the spot.
   - `GTS/thirdparty/fltk/fltk-1.3.4-2.zip`
   - `GTS/thirdparty/glew/glew-2.1.0.zip`
   - `GTS/thirdparty/libtiff/tiff-4.0.9.zip`

 - How to build fltk
   - Open `GTS/thirdparty/fltk/fltk-1.3.4-2/ide/VisualC2010/fltk.sln` at Visual Studio 2017
   - Set to `Release` about `Solution Configuration`
   - Set to `Win32` about `Solution Platform`
   - Set to `/MD` about `Runtime Library`
   - Execute Solution Build
 - How to build glew
   - Open `GTS/thirdparty/glew/glew-2.1.0/build/vc12/glew.sln` at Visual Studio 2017
   - Set to `Release` about `Solution Configuration`
   - Set to `Win32` about `Solution Platform`
   - Set to `/MD` about `Runtime Library`
   - Execute Solution Build
 - How to build libtiff
   - vc2017(32bit) Command Prompt 
 ```sh
 $ cd GTS/thirdparty/libtiff/tiff-4.0.9/
 $ nmake /f Makefile.vc lib
 ```

4. How to build

 The Windows application is compiled as 32-bit because the reference TWAIN driver used during development was only available in 32-bit.
 After building *fltk* and *tiff* with Visual C++, following their own instructions, go to `GTS/sources/` and run the batch file `one_step_build_vc2017.bat` from a console.

5. Preparation for Execute

 Nothing

6. How to Execute

 In `GTS/build/bin_x86/` you'll find the executable `gts.exe`. Run it.

## How to Build Locally (Linux)

1. Environment for development

 Tested simply on a Ubuntu 16.04-desktop 64bits(on a VMware Workstation 12.5.9 Player(on a Windows 7 Enterprise SP1))

2. Get source code

 Same as Windows.

3. Get third party libraries

 ```sh
 $ sudo apt install autoconf libtool autoconf-archive libtiff5-dev libfltk1.3-dev libglew-dev libsane-dev libglu1-mesa-dev
 ```

4. How to build

 ```sh
 $ ./autogen.sh && ./configure && make
 ```

 If you're a developer and you need a debug build, do it like this:
 ```sh
 $ ./autogen.sh && CFLAGS="-O2 -ggdb -march=native" CXXFLAGS="$CFLAGS" ./configure && make -j8
 # now you can use gdb:
 $ gdb --args ./gts -bv
 ```

5. Configuration file

After installing the package with "make install", copy "/usr/local/share/GTS/gts\_initial\_configuration.txt"
to "~/.GTS/" and open it from the main menu (File -> Open Config).
Change some settings, then save your configuration with File -> Save config.

It will be loaded automatically the next time you open the program.

6. How to Execute

 ```sh
 ./gts
 ```

## How to Build Locally (macOS)

1. Environment for development

 Mac OS X 10.x

2. Get source code

 Same as Windows.

3. Get third party libraries

 ```sh
 $ brew install automake autoconf-archive libtool pkgconfig libtiff sane-backends
 $ sudo port install fltk-devel #not in homebrew
 ```

4. How to build

 ```sh
 $ ./autogen.sh && ./configure && make
 ```

5. Preparation for Execute

 Same as Linux.

6. How to Execute

 ```sh
 ./gts
 ```

## License

- Files outside of the `thirdparty` directory are based on the New BSD License.
  - [New BSD License](./LICENSE.txt).
- For files in the `thirdparty` directory:
  - Please consult with the licenses in the appropriate READMEs or source codes.

