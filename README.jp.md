# GTS  ([English](./README.md))

## これは何？

紙に描かれた動画を、パソコンと TWAINドライバーソフトで動作するスキャナーを使って、「連番」でスキャンし、ファイルに保存するソフトウェアです。
画像の２値化も行います。

## 動作仕様

TWAIN規格によるスキャナーアクセス。
メニュー表記は英語のみ。
保存する画像はTIFF/TGAの2種類です。

## インストール

https://github.com/opentoonz/GTS/releases から、最新版の GTS-x.y.z.zip ファイルをダウンロードし、解凍してください。

## ビルド方法(Windows)

1. 環境を準備

  Windows 7 Enterprise SP1 と Microsoft Visual C++ 2013 を用意します。
  この環境で動作確認をしており、他の環境については未確認です。


2. ソースコードを準備

  git で clone してソースコードを手元に持ってきます。
  
  ```sh
  $ git clone https://github.com/opentoonz/GTS.git
  ```

3. ビルドに必要なライブラリを用意し、それぞれ以下にセットします。

  - `GTS/thirdparty/fltk/fltk-1.3.3/`
  - `GTS/thirdparty/libtiff/tiff-4.0.3/`

4. ビルドする

  Windows 32-bit アプリケーションです（64-bit OS 上でも動作します）。
  ビルドに必要なライブラリを32-bitビルドします。

  `GTS/sources/` へ移動し、ビルドバッチファイル `one_step_build_vc2013.bat` を実行します。


5. 動作確認

  `GTS/x86_release/` にある、`gts.exe` を実行して動作を確かめてください。

./gts

## ビルド方法(linux)
  Ubuntu 16.04-desktop 64bits (on vmware 12.1.1 Player)

## ビルド方法(Max OS X)
  Mac OS X 10.x

brew install automake
brew install autoconf-archive
rm m4/ax_check_glu.m4 #it seems broken?
sudo port install fltk-devel #not in homebrew
./autogen.sh && ./configure && make

## ライセンス

[New BSD License](https://github.com/opentoonz/GTS/blob/master/LICENSE.txt)
