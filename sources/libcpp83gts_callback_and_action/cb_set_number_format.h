#ifndef cb_set_number_format_h
#define cb_set_number_format_h

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Output.H>

class cb_set_number_format {
public:
	cb_set_number_format()
	:o_(nullptr)
	{}

	void cb_dialog_set_number_format(
		Fl_Double_Window* flwin
		,Fl_Output* flout
	);

	void cb_separator(void);
	void cb_digits(void);
	void cb_ok(void);
private:
	Fl_Output* o_;
};

#endif /* !cb_set_number_format_h */
