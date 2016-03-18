#include <cstdlib>	/* atoi() */
#include <cstring>	/* strlen() */
#include <cctype>	/* isdigit() */
#include <sstream>	/* std::istringstream */
#include "gtsfbro05list_level.h"
#include "gts_gui.h"

namespace {
 int framenumber_from_filename_( const std::string&file_name ) {
	/*
		 v
		0987654321 --> 10 charactor以上
		A.0001.tif
	*/
	if (
		(9 >= file_name.size())
		|| ( '.' != file_name.at(       file_name.size() - 4 ) )
		|| (0 == isdigit( file_name.at( file_name.size() - 5 ) ))
		|| (0 == isdigit( file_name.at( file_name.size() - 6 ) ))
		|| (0 == isdigit( file_name.at( file_name.size() - 7 ) ))
		|| (0 == isdigit( file_name.at( file_name.size() - 8 ) ))
		|| ( '.' != file_name.at(       file_name.size() - 9 ) )
	) { return -1; }
	std::istringstream ist(file_name.substr(file_name.size() - 8 ,4));
	int num=0;
	ist >> num;
	return num;
 }
 /*
	動作	拡張部分を外しlevel名にする
		A_full.0001.tif --> A
		A.0001.tif --> A
 */
 const std::string levelname_from_filename_(
	const std::string&file_name
	,const E_DIR_OR_FILE_TYPE file_type
	,const std::string&file_full_part//=this->ccp_mark_not_tracing_rgb()
 ) {
	/* 拡張部分のサイズ
		 v    v
		543210987654321
		A_full.0001.tif	--> A
		 v
		0987654321
		A.0001.tif	--> A
	*/
	std::string::size_type length = 9;
	if (E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE == file_type) {
		length += file_full_part.size();
	}
	/* ファイル名の長さとの確認 */
	if (length >= file_name.size()) { return std::string(); }

	/* level名部分 */
	return file_name.substr( 0 ,file_name.size()-length );
 }
 void string_to_array_(
	const std::string&name_str
	,const unsigned array_size
	,char *array_level
 ) {
	const int sz = name_str.size() < array_size
			?name_str.size() :array_size-1;
	strncpy( array_level ,name_str.c_str() ,sz );
	array_level[sz] = '\0';
 }
}

void gtsfbro05list_level::add_same_dir_or_level_(
	const int file_start, const int level_tgt
	,const std::string&name
) {
	ST_DIR_OR_LEVEL_INFO	*stp_lev = this->_stp_dir_or_level;
	ST_DIR_OR_FILE_INFO	*stp_fil = this->stp_dir_or_file();

	for (int ii = file_start; ii < this->i_dir_or_file_used(); ++ii) {
		/* すでにチェックしたなら次へ */
		if (ON == stp_fil[ii].is_chk) { continue; }

		/* Dirなら次へ */
		if (E_DIR_OR_FILE_IS_DIR == stp_fil[ii].e_type) {
			continue;
		}

		/* ファイル番号が付いていないなら次へ */
		int frame_number = framenumber_from_filename_(
			stp_fil[ii].cp_name
		);
		if (frame_number < 0) { continue; }

		/* 同じlevelの画像でなければ次へ */
		if (levelname_from_filename_(
			stp_fil[ii].cp_name
			,stp_fil[ii].e_type
			,this->ccp_mark_not_tracing_rgb()
 		) != name) {
			continue;
		}
		//---------------------------------------------------
		/* rgb full画像かどうかのカウンター */
		if (E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE
		== stp_fil[ii].e_type) {
			++stp_lev[level_tgt].i_not_traceing_rgb_count;
		} else
		if (E_DIR_OR_FILE_IS_NUM_IMAGE
		== stp_fil[ii].e_type) {
			++stp_lev[level_tgt].i_count;
		}

		/* 番号の最大と最小の設定 */
		if (frame_number < stp_lev[level_tgt].i_start_num) {
			stp_lev[level_tgt].i_start_num = frame_number;
		}
		if (stp_lev[level_tgt].i_end_num < frame_number) {
			stp_lev[level_tgt].i_end_num = frame_number;
		}

		/* データを取ったのでチェックする */
		stp_fil[ii].is_chk = ON;
	}
}
//--------------------------------------------------------------------
void gtsfbro05list_level::_make_dir_or_level( void )
{
	ST_DIR_OR_LEVEL_INFO *stp_lev = this->_stp_dir_or_level;
	ST_DIR_OR_FILE_INFO  *stp_fil = this->stp_dir_or_file();

	for (int ii = 0; ii < this->i_dir_or_file_used(); ++ii) {
		if (ON == stp_fil[ii].is_chk) { continue; }

		int i_lev = 0;

		/* Down Dir List */
		if (E_DIR_OR_FILE_IS_DIR == stp_fil[ii].e_type) {
			i_lev = this->_i_dir_or_level_used;
			      ++this->_i_dir_or_level_used;
			//stp_lev[i_lev].cp_name = stp_fil[ii].cp_name;
			strcpy(
				stp_lev[i_lev].name
				,stp_fil[ii].cp_name
			);
			stp_lev[i_lev].e_type = stp_fil[ii].e_type;
			stp_lev[i_lev].i_start_num = 0;
			stp_lev[i_lev].i_end_num = 0;
			stp_lev[i_lev].i_count = 0;
			stp_lev[i_lev].i_not_traceing_rgb_count = 0;
		}
		/* 番号をもつtifファイル */
		else {
			int i_file_num = framenumber_from_filename_(
				stp_fil[ii].cp_name);
			//if (i_file_num < 0) { continue; }

			i_lev = this->_i_dir_or_level_used;
			      ++this->_i_dir_or_level_used;

 			string_to_array_(
				levelname_from_filename_(
					stp_fil[ii].cp_name
					,stp_fil[ii].e_type
					,this->ccp_mark_not_tracing_rgb()
				)
				,PTBL_PATH_MAX ,stp_lev[i_lev].name
			);

			//stp_lev[i_lev].cp_name = stp_fil[ii].cp_name;
			stp_lev[i_lev].e_type = stp_fil[ii].e_type;
			stp_lev[i_lev].i_start_num = i_file_num;
			stp_lev[i_lev].i_end_num = i_file_num;
			if (E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE
			== stp_lev[i_lev].e_type) {
			 ++stp_lev[i_lev].i_not_traceing_rgb_count;
			} else
			if (E_DIR_OR_FILE_IS_NUM_IMAGE
			== stp_lev[i_lev].e_type) {
			 ++stp_lev[i_lev].i_count;
			}

			this->add_same_dir_or_level_(
				ii+1, i_lev ,stp_lev[i_lev].name
			);
		}

		stp_fil[ii].is_chk = ON;
	}
}
void gtsfbro05list_level::_draw_dir_or_level_list( void )
{
	ST_DIR_OR_LEVEL_INFO	*stp_lev;
	int	ii;
	char	ca_buf[PTBL_PATH_MAX];

	stp_lev = this->_stp_dir_or_level;

	for (ii = 0; ii < this->_i_dir_or_level_used; ++ii) {
		/* Down Dir List */
		if (E_DIR_OR_FILE_IS_DIR == stp_lev[ii].e_type) {
			snprintf(ca_buf, PTBL_PATH_MAX,
				"%s%s",
				this->ccp_dir_mark(),
				stp_lev[ii].name );
		}
		/* image(.tif) File List */
		else {
			/* ファイル名(stp_lev[ii].cp_name)から
				Level名(name)を生成する */

			if (stp_lev[ii].i_not_traceing_rgb_count <= 0) {
				if (stp_lev[ii].i_count <= 0) {
					/* ここに来ることはあり得ない */
					snprintf(ca_buf,PTBL_PATH_MAX,
						"bug %s",
						stp_lev[ii].name );
				} else {
				snprintf(ca_buf,PTBL_PATH_MAX,
					"%d      %s",
					stp_lev[ii].i_count,
					stp_lev[ii].name );
				}
			} else {
				snprintf(ca_buf,PTBL_PATH_MAX,
					"%d(%d)  %s",
				stp_lev[ii].i_count,
				stp_lev[ii].i_not_traceing_rgb_count,
				stp_lev[ii].name );
			}
		}
		cl_gts_gui.selbro_level_list->insert(
		 cl_gts_gui.selbro_level_list->size()+1, ca_buf);
	}

	/* 表示を１行目からに戻す */
	if (0 < this->_i_dir_or_level_used) {
		cl_gts_gui.selbro_level_list->topline(1);
	}
}
