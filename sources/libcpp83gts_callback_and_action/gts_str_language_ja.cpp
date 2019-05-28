#include "gts_str_language.h"

namespace gts_str {

namespace area_and_rot90 {
const char* offset_cm_x_big
	= u8"最大範囲の右をはみ出したので左に寄せました";
const char* offset_cm_x_small
	= u8"最大範囲の左をはみ出したので右に寄せました";
const char* offset_cm_y_big
	= u8"最大範囲の下をはみ出したので上に寄せました";
const char* offset_cm_y_small
	= u8"最大範囲の上をはみ出したので下に寄せました";
const char* size_cm_w_big
	= u8"最大範囲の右をはみ出したので切り取りました";
const char* size_cm_w_small
	= u8"幅がマイナス値なのでゼロにリセットします";
const char* size_cm_h_big
	= u8"最大範囲の下をはみ出したので切り取りました";
const char* size_cm_h_small
	= u8"高さがマイナス値なのでゼロにリセットします";
const char* dpi_out_of_range
	= u8"DPIは%gから%gの範囲で指定してください";
const char* crop_again
	= u8"最大スキャンをし直してください";
const char* need_only_1_filepath
	= u8"複数のファイルを指定しています、一つだけ選択してください";
const char* bad_aspect_ratio_h
	= u8"縦横比の高の値はゼロより大きい値が必要です";
const char* bad_aspect_ratio_w
	= u8"縦横比の幅の値はゼロより大きい値が必要です";
const char* click_h_or_w_button
	= u8"縦横比によるサイズ指定をするときは固定する幅か高どちらかのボタンを選択してください";
} // area_and_rot90

namespace change_view {
const char* not_change
	= u8"最大スキャン時は切替えできません";
const char* no_image
	= u8"画像がありません";
const char* no_rgb_image
	= u8"24ビットカラー画像が必要です";
const char* view_setup_error
	= u8"表示エラー";
} // change_view

namespace config {
const char* open
	= u8"設定をファイルから再現";
const char* open_only_area_and_rot90
	= u8"範囲と方向の設定をファイルから再現";
const char* open_only_pixel_type_and_bright
	= u8"画像タイプと明るさの設定をファイルから再現";
const char* open_only_trace_params
	= u8"二値化調整の設定をファイルから再現";
const char* save_as
	= u8"設定を別名でファイルに保存";
const char* loading_config_error
	= u8"設定ファイルを読込むのにエラーが起きました";
const char* need_ext_txt
	= u8"拡張子\".txt\"であるファイルを選んでください";
} // config

namespace image {
const char* open
	= u8"画像を一枚ファイルから表示";
const char* save_as
	= u8"画像を処理せず一枚別名でファイルへ保存";
const char* save_as_can_not_when_crop
	= u8"最大スキャン(範囲編集)では保存できません。確認スキャンするか画像ファイルを開いてください";
const char* no_image
	= u8"Please Any Scan or Open.";
const char* need_extension
	= u8"Need Extension.";
const char* effects_error
	= u8"Effects Error";
const char* save_error
	= u8"Save \"%s\" Error";
} // image

namespace number {
const char* need_to_set_number
	= u8"「連番セット」ボタンを押して連番をセットしてください";
} // number

namespace scan_and_save {
const char* select_folder
	= u8"連番スキャン画像を保存するフォルダーを選択する";
const char* not_scan_number
	= u8"連番スキャンで連番セットしてください";
const char* need_scan_save_name
	= u8"連番のファイル名を指定してください";
const char* select_number
	= u8"連番を選択してください";
const char* bad_number
	= u8"開始番号が間違っています";
const char* bad_scan_number
	= u8"連番指定に問題があります";
const char* scan_error
	= u8"スキャンでエラーが起こりました";
const char* rot_and_trace_and_enoise_error
	= u8"処理でエラーが起こりました";
const char* redraw_error
	= u8"画像の再表示でエラーが起こりました";
const char* can_not_get_save_path
	= u8"指定番号でファイルパスを得ることができません";
const char* can_not_save
	= u8"連番ファイル保存でエラーが起こりました";
} // scan_and_save

namespace trace_batch {
const char* add_config
	= u8"複数の設定ファイルを選択する";
} // trace_batch

namespace trace_files {
const char* open
	= u8"連番画像ファイルとして(そのうち一枚)選択する";
const char* select_folder
	= u8"連番二値化画像を保存するフォルダーを選択する";
} // trace_files

} // gts_str
