# [GTS](https://opentoonz.github.io/index.html)  ([English](./README.md))

## これは何？

「紙」に描かれた動画を、パソコンとスキャナーを使って、「連番」でスキャンし、ファイルに保存するソフトウェアです。

画像の「２値化」も行うことができます。

株式会社スタジオジブリにて開発し、ジブリ作品の制作に長年使われてきました。

## 仕様

TWAIN規格(Windows)/SANE規格(Linux,Mac OS X)によるスキャナーアクセス。

メニュー表記は英語のみ。

保存する画像はTIFFです。

## 推奨環境

[OpenToonzのサイト](https://opentoonz.github.io/index.html)を参照してください。

## インストール(Windows)

最新版の GTS-x.y.z.zip ファイルを[ダウンロード](https://github.com/opentoonz/GTS/releases)し、解凍してください。

## 実行方法(Windows)

解凍したフォルダー内にて、".\gts" を実行します。

## ビルド方法(Windows)

1. 環境を準備

 Windows 7 Enterprise SP1 と Microsoft Visual C++ 2013 を用意します。

 この環境で動作確認をしており、他の環境については未確認です。

2. ソースコードを準備

 git で clone してソースコードを手元に持ってきます。
 
 ```sh
 $ git clone https://github.com/opentoonz/GTS.git
 ```

3. 外部ライブラリを準備

 ソースコードを以下の場所にフォルダー構成そのままに置きます。
 - `GTS/thirdparty/fltk/fltk-1.3.3/`
 - `GTS/thirdparty/libtiff/tiff-4.0.3/`

4. ビルドする

 TWAINドライバーが32-bitのため、32-bitアプリケーションとしてビルドします。

 先に、外部ライブラリを、32-bitでビルドします。

 `GTS/sources/` へ移動し、本体ビルドバッチファイル `one_step_build_vc2013.bat` を実行します(64ビットWindowsでない場合、`vcvarsall.bat`のパスを変更する必要があるかもしれません)。

5. 動作準備

 なし

6. 動作確認

 `GTS/x86_release/` にある、`gts.exe` を実行して動作を確かめてください。

## ビルド方法(Linux)

1. 環境を準備

 Ubuntu 16.04-desktop 64bits (on VMware Workstation 12.1.1 Player(on Windows 7 Enterprise SP1)) を用意します。

 この環境で簡単な動作確認をしており、他の環境については未確認です。

2. ソースコードを準備

 Windowsと同じ

3. 外部ライブラリを準備

 ```sh
 $ sudo apt install autoconf
 $ sudo apt install libtool
 $ sudo apt install autoconf-archive
 $ sudo apt install libtiff5-dev
 $ sudo apt install libfltk1.3-dev
 $ sudo apt install libsane-dev
 ```

4. ビルドする

 ```sh
 $ rm m4/ax_check_glu.m4
 $ ./autogen.sh && ./configure && make
 ```
 makeの最後のlinkがエラーとなるので、その実行コマンドラインに`-lGLU -lGL`を付加して再実行します。

 デバッグビルドをしたいときは以下のようにします。
 ```sh
 $ rm m4/ax_check_glu.m4
 $ ./autogen.sh && CFLAGS="-O2 -ggdb -march=native" CXXFLAGS="$CFLAGS" ./configure && make -j8
 ```

5. 動作準備

 `source/main/gts_install_setup.txt`ファイルの中の`browser_directory_path`行の値を`"/home"`に変更します。
 以下のファイル、
 - `sources/main/_gts-scan_area.txt`
 - `sources/main/gts_install_setup.txt`

 を`~/.GTS`にコピーします。

6. 動作確認

 `./gts` を実行します。

 デバッグビルドをしたときは以下のように実行します。
 ```sh
 # now you can use gdb:
 gdb --args ./gts -bv
 ```

## ビルド方法(Max OS X)

1. 環境を準備

 Mac OS X 10.x

2. ソースコードを準備

 Windowsと同じ

3. 外部ライブラリを準備

 ```sh
 $ brew install automake
 $ brew install autoconf-archive
 $ sudo port install fltk-devel #not in homebrew
 ```

4. ビルドする

 ```sh
 $ rm m4/ax_check_glu.m4 #it seems broken?
 $ ./autogen.sh && ./configure && make
 ```

5. 動作準備

 Linuxと同じ

6. 動作確認

 `./gts` を実行します。

## ライセンス

[New BSD License](https://github.com/opentoonz/GTS/blob/master/LICENSE.txt)
