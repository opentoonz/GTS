#include <string>
#include <iomanip> // std;;setw()
#include <sstream> // std::ostringstream
#include "cb_input_number_format.h"
#include "gts_gui.h"

namespace {

void set_sample_(void)
{
	std::string sep(cl_gts_gui.choice_input_num_form_separator->text());
	if (sep.at(1) == ' ') {
		sep.clear();
	}
	else {
		sep = sep.at(1);
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
	,Fl_Widget* flwgt
	,Fl_Output* flout
)
{
	/* window開く */
	cl_gts_gui.window_input_number_format->show();
	cl_gts_gui.window_input_number_format->position(
		 flwin->x() +flwgt->x() -10
		,flwin->y() +flwgt->y() -160
	);

	/* OKの時の設定をするため記憶しとく */
	this->o_ = flout;

	/* 書式のDefault設定 */
	std::string sep("\'.\'");
	int dig = 4;

	/* 指定があればの書式を設定 */
	std::string num_form( flout->value() );
	if ( !num_form.empty() && 1 <= num_form.size() ) {
		if (isdigit( num_form.at(0) )) {
			sep = "\' \'";
			dig = num_form.size();
		}
		else {
			sep  = "\'";
			sep += num_form.at(0);
			sep += "\'";
			dig = num_form.size()-1;
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
}

void cb_input_number_format::cb_cancel(void)
{
	cl_gts_gui.window_input_number_format->hide();
}
