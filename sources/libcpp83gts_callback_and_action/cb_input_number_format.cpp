#include <string>
#include <iomanip> // std;;setw()
#include <sstream> // std::ostringstream
#include "ids_path_level_from_files.h"
#include "cb_input_number_format.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {

void set_sample_(void)
{
	std::string sep;
	const int idx = cl_gts_gui.choice_input_num_form_separator->value();
	if (0 < idx) { // "idx == 0" is Nothing
	 sep = ids::path::get_separator_codes_for_level_from_files()[idx-1];
	}
		
	std::ostringstream ost;
	ost
	<< sep
	<<  std::setfill('0') << std::setw(
 static_cast<int>(cl_gts_gui.counte_input_num_form_num_of_digits->value())
	) << 0
	;
	cl_gts_gui.output_input_num_form_sample->value( ost.str().c_str() );
}

}//namespace

void cb_input_number_format::cb_dialog_input_number_format(
	Fl_Double_Window* flwin
	,Fl_Output* flout
)
{
	/* window開く */
	cl_gts_gui.window_input_number_format->show();
	cl_gts_gui.window_input_number_format->position(
		 flwin->x() +flout->x() -10
		,flwin->y() +flout->y() -160
	);

	/* OKの時の設定をするため記憶しとく */
	this->o_ = flout;

	std::string codes(
		ids::path::get_separator_codes_for_level_from_files() );
	const char** names =
		ids::path::get_separator_names_for_level_from_files();

	/* 書式のDefault設定 */
	std::string sep(names[0]); //Dot
	int dig = 4;

	/* 指定があればの書式を設定 */
	std::string num_form( flout->value() );
	if ( !num_form.empty() && 1 <= num_form.size() ) {
		if (isdigit( num_form.at(0) )) {/* 区切り文字ではない */
			sep = "Nothing";
			dig = num_form.size();
		}
		else {			/* 区切り文字かも(数文字以外) */
			std::string::size_type st =
				codes.find( num_form.at(0) );
			if (st != std::string::npos) {/* 規定の区切り文字 */
				sep = names[st];
				dig = num_form.size()-1;
			}
		}
	}

	/* セパレータの設定 */
	int idx =
	cl_gts_gui.choice_input_num_form_separator->find_index(sep.c_str());
	if (idx == -1) {/* 見つからない場合はなしに設定 */
		idx = 0;
	}
	cl_gts_gui.choice_input_num_form_separator->value(idx);

	/* 数値の桁数設定 */
	cl_gts_gui.counte_input_num_form_num_of_digits->value(dig);

	set_sample_();
}

void cb_input_number_format::cb_separator(void)
{
	set_sample_();
}

void cb_input_number_format::cb_digits(void)
{
	set_sample_();
}

void cb_input_number_format::cb_ok(void)
{
	this->o_->value( cl_gts_gui.output_input_num_form_sample->value() );
	cl_gts_gui.window_input_number_format->hide();

	cl_gts_master.cl_scan_and_save.cb_check_existing_saved_file();
	cl_gts_master.cl_trace_files.cb_check_existing_saved_file();
}

