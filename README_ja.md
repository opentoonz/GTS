# [GTS](https://opentoonz.github.io/index.html)  ([English](./README.md))

## これは何？

「紙」に描かれた動画を、パソコンとスキャナーを使って、「連番」でスキャンし、ファイルに保存するソフトウェアです。

画像の「２値化」も行うことができます。

株式会社スタジオジブリにて開発し、ジブリ作品の制作に長年使われてきました。

## 仕様

TWAIN規格(Windows)/SANE規格(Linux,macOS)によるスキャナーアクセス。

メニュー表記は英語のみ。

保存する画像はTarga/TIFFです。

## 推奨環境

[OpenToonzのサイト](https://opentoonz.github.io/index.html)を参照してください。

## インストール(Windows)

最新版の GTS-x.y.z.zip ファイルを[ダウンロード](https://github.com/opentoonz/GTS/releases)し、解凍してください。

## 実行方法(Windows)

解凍したフォルダー内にて、"gts.exe" を実行します。

## ビルド方法(Windows)

1. 環境を準備

 Windows 7 Enterprise SP1 と Microsoft Visual C++ 2017 を用意します。

 この環境で動作確認をしており、他の環境については未確認です。

2. ソースコードを準備

 git で clone してソースコードを手元に持ってきます。
 
 ```sh
 $ git clone https://github.com/opentoonz/GTS.git
 ```

3. 外部ライブラリを準備

 - ソースコードをその場で展開します
   - `GTS/thirdparty/fltk/fltk-1.3.4-2.zip`
   - `GTS/thirdparty/glew/glew-2.1.0.zip`
   - `GTS/thirdparty/libtiff/tiff-4.0.9.zip`

 - fltkのビルド方法
   - Visual Studio 2017で`GTS/thirdparty/fltk/fltk-1.3.4-2/ide/VisualC2010/fltk.sln`を開く
   - `ソリューション構成`を`Release`にする
   - `ソリューションプラットフォーム`を`Win32`にする(default)
   - `ランタイムライブラリ`を`/MD`にする(default)
   - ソリューションビルドを実行する
 - glewのビルド方法
   - Visual Studio 2017で`GTS/thirdparty/glew/glew-2.1.0/build/vc12/glew.sln`を開く
   - `ソリューション構成`を`Release`にする
   - `ソリューションプラットフォーム`を`Win32`にする(default)
   - `ランタイムライブラリ`を`/MD`にする
   - ソリューションビルドを実行する
 - libtiffのビルド方法
   - vc2017(32bit)用コマンドプロンプトにて以下を実行する
 ```sh
 $ cd GTS/thirdparty/libtiff/tiff-4.0.9/
 $ nmake /f Makefile.vc lib
 ```

4. ビルドする

 TWAINドライバーが32-bitのため、32-bitアプリケーションとしてビルドします。

 先に、外部ライブラリを、32-bitでビルドします。

 `GTS/sources/` へ移動し、本体ビルドバッチファイル `one_step_build_vc2017.bat` を実行します

5. 動作準備

 なし

6. 動作確認

 `GTS/build/bin_x86/` にある、`gts.exe` を実行して動作を確かめてください。

## ビルド方法(Linux)

1. 環境を準備

 Ubuntu 16.04-desktop 64bits (on VMware Workstation 12.5.9 Player(on Windows 7 Enterprise SP1)) を用意します。

 この環境で簡単な動作確認をしており、他の環境については未確認です。

2. ソースコードを準備

 Windowsと同じ

3. 外部ライブラリを準備

 ```sh
 $ sudo apt install autoconf libtool autoconf-archive libtiff5-dev libfltk1.3-dev libglew-dev libsane-dev libglu1-mesa-dev
 ```

4. ビルドする

 ```sh
 $ ./autogen.sh && ./configure && make
 ```
 makeの最後のlinkがエラーとなるので、その実行コマンドラインに`-lpthread -lGLEW`を付加して再実行します。

 デバッグビルドをしたいときは以下のようにします。
 ```sh
 $ ./autogen.sh && CFLAGS="-O2 -ggdb -march=native" CXXFLAGS="$CFLAGS" ./configure && make -j8
 ```

5. 動作準備

 `source/main/gts_initial_configuration.txt`ファイルの中の`*_dir*`行の値を`"/home"`に変更します。
 以下のファイル、
 - `sources/main/gts_initial_configuration.txt`

 を`~/.GTS`にコピーします。

6. 動作確認

 `./gts` を実行します。

 デバッグビルドをしたときは以下のように実行します。
 ```sh
 # now you can use gdb:
 gdb --args ./gts -bv
 ```

## ビルド方法(maxOS)

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
 $ ./autogen.sh && ./configure && make
 ```

5. 動作準備

 Linuxと同じ

6. 動作確認

 `./gts` を実行します。

## ライセンス

- thirdparty ディレクトリ以外のファイル
  - [New BSD License](./LICENSE.txt)
- thirdparty ディレクトリ内のファイル
  - 各ディレクトリ内の README やソースコードに記載されたライセンスに従ってください

