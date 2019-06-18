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
const char* bad_aspect_ratio_h
	= u8"縦横比の高の値はゼロより大きい値が必要です";
const char* bad_aspect_ratio_w
	= u8"縦横比の幅の値はゼロより大きい値が必要です";
const char* click_h_or_w_button
	= u8"縦横比によるサイズ指定をするときは固定する幅か高どちらかのボタンを選択してください";
const char* not_inside_then_limit
	= u8"範囲をはみ出しているため制限します";
const char* not_inside_then_limit_cancel
	= u8"キャンセル";
const char* not_inside_then_limit_size
	= u8"大きさをカット";
const char* not_inside_then_limit_dpi
	= u8"DPIを上げる";
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
const char* need_only_1_filepath
	= u8"複数のファイルを指定しています、一つだけ選択してください";
const char* loading_config_error
	= u8"設定ファイルを読込むのにエラーが起きました";
const char* need_ext_txt
	= u8"拡張子\".txt\"であるファイルを選んでください";
const char* use_save_config_as
	= u8"「設定 別名で保存...」で保存してください";
const char* ask_overwrite
	= u8"\"%s\"\n上書きしますか?";
const char* ask_save
	= u8"\"%s\"\n保存しますか?";
} // config

namespace image {
const char* open
	= u8"画像を一枚ファイルから表示";
const char* save_as
	= u8"画像を処理せず一枚別名でファイルへ保存";
const char* save_as_can_not_when_crop
	= u8"最大スキャン(範囲編集)では保存できません。確認スキャンするか画像ファイルを開いてください";
const char* no_image
	= u8"画像がありません(スキャンするかファイルを開いてください)";
const char* need_extension
	= u8"拡張子がありません";
const char* effects_error
	= u8"処理でエラーがありました";
const char* save_error
	= u8"ファイル保存するときエラーが起きました\n\"%s\"";
} // image

namespace number {
const char* need_to_set_number
	= u8"「連番セット」ボタンを押して連番をセットしてください";
} // number

namespace scan_and_save {
const char* select_folder
	= u8"連番スキャン画像を保存するフォルダーを選択する";
const char* not_scan_number
	= u8"「連番スキャン」で[連番セット]してください";
const char* need_scan_save_name
	= u8"連番スキャンのファイル名を指定してください";
const char* select_number
	= u8"「実行番号」を選択してください";
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
	= u8"ファイル保存でエラーが起こりました";
} // scan_and_save

namespace trace_batch {
const char* add_config
	= u8"複数の設定ファイルを選択する";
const char* too_many_selected
	= u8"一つだけ選択してください(%d個選ばれています)";
} // trace_batch

namespace trace_files {
const char* open_images
	= u8"連番画像ファイルとして(そのうち一枚)選択する";
const char* select_folder
	= u8"連番二値化画像を保存するフォルダーを選択する";
const char* not_trace_number
	= u8"「連番ファイル2値化」で[連番セット]してください";
const char* need_trace_open_name
	= u8"開くべき連番ファイル名がありません";
const char* need_trace_save_name
	= u8"保存する連番ファイル名がありません";
const char* check_open_folder_and_filename
	= u8"開くべきフォルダー名とファイル名を確認してください";
const char* check_save_folder_and_filename
	= u8"保存するフォルダー名とファイル名を確認してください";
const char* select_number
	= u8"「実行番号」を選択してください";
const char* filename_without_head_or_number
	= u8"ファイル頭名あるいは番号がありません\n\'%s\'";
const char* empty_rename_filename
	= u8"ファイルパスエラー\ninn\"%s\"\nout\"%s\"";
const char* number_is_out_of_range
	= u8"エラー\n%s\nから\n%s\nへの数値シフトだと連番が\n %s\nとなります。\n0から9999までの範囲になるように指定してください";
const char* no_head_in_filepath
	= u8"ファイル頭名がありません";
const char* bad_extension_in_filepath
	= u8"非対応の拡張子です(%s)";
const char* not_number_file
	= u8"連番ファイルではありません\n\"%s\"";
const char* ask_do_trace
	= u8"2値化処理する";
const char* ask_do_not_trace
	= u8"2値化処理しない";
const char* ask_and_erase_dot_noise
	= u8"、ドットノイズ除去処理する";
const char* ask_rename
	= u8"リネーム実行します\n\"%s\"\nを\n\"%s\"\nに\n番号リスト\"%s\"";
const char* ask_renumber
	= u8"リナンバー実行します\n\"%s\"\nを\n\"%s\"\nに\n番号リスト\"%s\"";
const char* input_new_level_name
	= u8"新しいファイル(頭)名を入力してください";
const char* input_new_start_number
	= u8"連番の開始番号を指定してください";
} // trace_files

namespace fl_gl_image_view {
const char* need_image_head_name
	= u8"ファイル頭名がありません";
const char* need_extension_of_image
	= u8"必要な拡張子ではありません(.tga/.tif/.txt)";
} // fl_gl_image_view

namespace quit {
const char* ask_quit
	= u8"本当に終了しますか？(必要な保存をしたか確認してください)";
} // quit

} // gts_str
