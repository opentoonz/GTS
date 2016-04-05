# Description

GTS is image scanning software specialized in hand-drawn animation frames. It uses TWAIN on Windows and SANE on other operating systems, so you need scanner drivers that support these APIs.

The Windows application is compiled as 32-bit because the reference TWAIN driver used during development was only available in 32 bits.

GTS's interface is in English and scanned images are saved as TIFF.

# Installation

## Windows binary

Download and unzip the most recent GTS-x.y.z.zip file from https://github.com/opentoonz/GTS/releases.

## From source

Get the source code from Github:
```sh
$ git clone https://github.com/opentoonz/GTS.git
```

### Requirements

#### Windows

* Microsoft Visual C++ 2013 (tested on a Windows 7 Enterprise SP1)
* third party libraries unarchived in:
 * `GTS/thirdparty/fltk/fltk-1.3.3/`
 * `GTS/thirdparty/libtiff/tiff-4.0.3/`

#### Linux, OS X, etc.

* fltk-1.x with OpenGL support
* tiff-4.x
* sane-backends-1.x

### Build

#### Windows

After building *fltk* and *tiff* with Visual C++, following their own instructions, go to `GTS/sources/` and run the batch file `one_step_build_vc2013.bat` from a console (you might need to change the `vcvarsall.bat` path if you're not on a 64-bit Windows).
  
In `GTS/x86_release/` you'll find the executable `gts.exe`. Run it.

#### Linux, OS X, etc.

```sh
./autogen.sh && ./configure && make
```

If you're a developer and you need a debug build, do it like this:
```sh
./autogen.sh && CFLAGS="-O2 -ggdb -march=native" CXXFLAGS="$CFLAGS" ./configure && make -j8
```

Now you can use gdb:
```sh
gdb --args ./gts -bv
```

Note for distribution packagers: change *browser_directory_path* to "." in `sources/main/gts_install_setup.txt` before installation.

If you're not using a proper package manager, do the change yourself and copy the 2 .txt files in `sources/main/` to `~/.GTS/`.

# License

[New BSD License] (blob/master/LICENSE.txt)

