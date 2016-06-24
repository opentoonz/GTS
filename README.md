# GTS  ([English](./README_en.md))

## これは何？

紙に描かれた動画を、パソコンと TWAINドライバーソフトで動作するスキャナーを使って、「連番」でスキャンし、ファイルに保存するソフトウェアです。

画像の２値化も行います。

## 仕様

TWAIN規格によるスキャナーアクセス。

メニュー表記は英語のみ。

保存する画像はTIFFです。

## インストール

Windows版実行プログラムのみ。

https://github.com/opentoonz/GTS/releases から、最新版の GTS-x.y.z.zip ファイルをダウンロードし、解凍してください。

解凍してできたフォルダーを任意の場所に移動して使用します。

## 実行方法

Windows版実行プログラムのみ。

フォルダー内にて、各ファイルはそのままにして、".\gts" を実行します。

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

 32-bitアプリケーションとしてビルドします。

 先に、外部ライブラリを、32-bitでビルドします。

 `GTS/sources/` へ移動し、本体ビルドバッチファイル `one_step_build_vc2013.bat` を実行します。

5. 動作準備

 なし

6. 動作確認

 `GTS/x86_release/` にある、`gts.exe` を実行して動作を確かめてください。

## ビルド方法(linux)

1. 環境を準備

 Ubuntu 16.04-desktop 64bits (on VMware Workstation 12.1.1 Player(on Windows 7 Enterprise SP1)) を用意します。

 この環境で動作確認をしており、他の環境については未確認です。

2. ソースコードを準備

 git で clone してソースコードを手元に持ってきます。

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

5. 動作準備

 任意のディレクトリを用意し、そこに以下のファイルをコピーします。
 - `sources/main/_gts-scan_area.txt`
 - `gts`
 - `sources/main/gts_install_setup.txt`

 `sources/main/gts_install_setup.txt`ファイルの中の`browser_directory_path`行の値を`"/home"`に変更します。

6. 動作確認

 用意したディレクトリに移動し`./gts` を実行します。

## ビルド方法(Max OS X)

1. 環境を準備

 Mac OS X 10.x

2. ソースコードを準備

 git で clone してソースコードを手元に持ってきます。

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

 Linuxと同じ

## ライセンス

[New BSD License](https://github.com/opentoonz/GTS/blob/master/LICENSE.txt)
