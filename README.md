#	GTS - Gts does Trace after Scan

## これは何？

紙に描かれた動画を、Windows PC と TWAIN ドライバーソフトで動作するスキャナーを使って、「連番」でスキャンし、ファイルに保存するソフトウェアです。
画像の２値化も行います。

## 動作条件

Windows 32-bit アプリケーションです（64-bit OS でも動作します）。
メニュー表記は英語のみ。保存する画像はTIFFです。

## インストール

https://github.com/opentoonz/GTS/releases から、最新版の gts.zip ファイルをダウンロードし、解凍してください。

## 開発者向け

### ソースコードから実行プログラムを生成するには

1. 環境を準備

  Windows 7 Enterprise SP1 と Microsoft Visual C++ 2013 を用意します。
  この環境で動作確認をしており、他の環境については未確認です。

2. ソースコードを準備

  git で clone してソースコードを手元に持ってきます。
  
  ```sh
  $ git clone https://github.com/opentoonz/GTS.git
  ```

3. ビルドに必要なライブラリを用意し、それぞれ以下にセットしビルドしておきます。

  - `GTS/sdk/fltk/fltk-1.3.3/`
  - `GTS/sdk/libtiff/tiff-4.0.3/`
  - `GTS/sdk/twain/twain-2.3/twain.h`

4. ビルドする

  `GTS\opensource\gts\main\sources` へ移動し、ビルドバッチファイル `one_step_build_vc2013.bat` を実行します。

5. 動作確認

  `GTS\opensource\gts\main\x86_release\` にある、`gts.exe` を実行して動作を確かめてください。

### ライセンス

[New BSD License](https://github.com/opentoonz/GTS/blob/master/LICENSE.txt)
