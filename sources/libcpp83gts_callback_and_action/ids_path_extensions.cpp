#include <algorithm> // std::find(-)
#include "ids_path_extensions.h"

ids::path::extensions::extensions()
{}
const std::string ids::path::extensions::str_from_num( const int num )
{
	if (static_cast<int>(this->dotex_.size()) <= num) {
		return std::string();
	}

	return this->dotex_.at(num);
}
const int ids::path::extensions::num_from_str( const std::string& ext )
{
	auto it = std::find(this->dotex_.begin() ,this->dotex_.end() ,ext);
	if ( it == this->dotex_.end() ) {
		return -1;
	}
	return static_cast<int>(std::distance(this->dotex_.begin(), it));
}
void ids::path::extensions::set_filter(
	const std::string& name ,const std::string& dotex
)
{
	this->names_.push_back( name );
	this->dotex_.push_back( dotex );
}
const std::string ids::path::extensions::get_native_filters( void )
{
	std::string str;

	/* Exsamples
		"Text\t*.txt\n"
		"C Files\t*.{cxx,h,c}"
	*/
	for (int ii=0 ;ii<static_cast<int>(this->dotex_.size()) ;++ii) {
		str += this->names_.at(ii);
		str += "\t*";
		str += this->dotex_.at(ii);
		str += "\n";
	}
	/* 拡張子が2個以上のときは全部をまとめたFilterも追加しとく */
	if (2 <= this->dotex_.size()) {
		str += "Image Files\t*.{";
		for(int ii=0;ii<static_cast<int>(this->dotex_.size());++ii){
			if (0 < ii) {
				str += ',';
			}
			if (this->dotex_.at(ii).at(0) == '.') {
				str += this->dotex_.at(ii).substr(1);
			}
			else {
				str += this->dotex_.at(ii);
			}
		}
		str += "}";
	}
	return str;
}
const std::string ids::path::extensions::get_fltk_filter( const int num )
{
	std::string str;
	if (num < 0 || static_cast<int>(this->dotex_.size()) <= num) {
		return str;
	}
	str += this->names_.at(num);
	str += "(*";
	str += this->dotex_.at(num);
	str += ")";
	return str;
}
