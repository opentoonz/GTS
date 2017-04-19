# [GTS](https://opentoonz.github.io/e/index.html)  ([日本語](./README_ja.md))

## What is GTS?

GTS is a scanning tool developed by Studio Ghibli.

It's specialized in hand-drawn animation frames.

## Specification

GTS's uses TWAIN on Windows and SANE on other operating systems, so you need scanner drivers that support these APIs in order to run it.

Interface is in English and scanned images are saved as TIFF.

## Requirements

Please refer to the [OpenToonz site](https://opentoonz.github.io/e/index.html).

## Installation(Windows)

[Download](https://github.com/opentoonz/GTS/releases) and unzip the most recent GTS-x.y.z.zip file.

## How to Execute(Windows)

Execute "./gts" in unziped folder.

## How to Build Locally(Windows)

1. Environment for development

 Microsoft Visual C++ 2013 (tested on a Windows 7 Enterprise SP1)

2. Get source code

 Get the source code from Github:
 ```sh
 $ git clone https://github.com/opentoonz/GTS.git
 ```

3. Get third party libraries

 third party libraries unarchived in:
 - `GTS/thirdparty/fltk/fltk-1.3.4-1/`
 - `GTS/thirdparty/libtiff/tiff-4.0.3/`

4. How to build

 The Windows application is compiled as 32-bit because the reference TWAIN driver used during development was only available in 32-bit.
 After building *fltk* and *tiff* with Visual C++, following their own instructions, go to `GTS/sources/` and run the batch file `one_step_build_vc2013.bat` from a console (you might need to change the `vcvarsall.bat` path if you're not on a 64-bit Windows).

5. Preparation for Execute

 Nothing

6. How to Execute

 In `GTS/x86_release/` you'll find the executable `gts.exe`. Run it.

## How to Build Locally(Linux)

1. Environment for development

 Tested simply on a Ubuntu 16.04-desktop 64bits(on a VMware Workstation 12.1.1 Player(on a Windows 7 Enterprise SP1))

2. Get source code

 Same as Windows.

3. Get third party libraries

 ```sh
 $ sudo apt install autoconf
 $ sudo apt install libtool
 $ sudo apt install autoconf-archive
 $ sudo apt install libtiff5-dev
 $ sudo apt install libfltk1.3-dev
 $ sudo apt install libsane-dev
 ```

4. How to build

 ```sh
 $ rm m4/ax_check_glu.m4
 $ ./autogen.sh && ./configure && make
 ```
 The last(link) of make is an error, and then re-run by adding `-lGLU -lGL` in the run command line.

 If you're a developer and you need a debug build, do it like this:
 ```sh
 $ rm m4/ax_check_glu.m4
 $ ./autogen.sh && CFLAGS="-O2 -ggdb -march=native" CXXFLAGS="$CFLAGS" ./configure && make -j8
 ```

5. Preparation for Execute

 Change *_dir* to "/home" in `sources/main/gts_initial_configuration.txt` before installation.
 Copy the 2 .txt files in `sources/main/` to `~/.GTS/`.

6. How to Execute

 ```sh
 # run it with
 ./gts
 ```

 If you're a developer and you need a debug build, do it like this:
 ```sh
 # now you can use gdb:
 gdb --args ./gts -bv
 ```

## How to Build Locally(Max OS X)

1. Environment for development

 Mac OS X 10.x

2. Get source code

 Same as Windows.

3. Get third party libraries

 ```sh
 $ brew install automake
 $ brew install autoconf-archive
 $ sudo port install fltk-devel #not in homebrew
 ```

4. How to build

 ```sh
 $ rm m4/ax_check_glu.m4 #it seems broken?
 $ ./autogen.sh && ./configure && make
 ```

5. Preparation for Execute

 Same as linux.

6. How to Execute

 ```sh
 # run it with
 ./gts
 ```

## License

- Files outside of the `thirdparty` directory are based on the New BSD License.
  - [New BSD License](./LICENSE.txt).
- For files in the `thirdparty` directory:
  - Please consult with the licenses in the appropriate READMEs or source codes.

