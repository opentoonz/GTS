#include <stdlib.h>	/* atoi() */
#include <ctype.h>
#include <assert.h>
#include "gts_master.h"
#include "gts_gui.h"

namespace {
 const char *next_num_( const char* str ,int* rsz ,int* frame_num )
 {
	int	ii = 0 ,jj = 0;
	char	buffer[1024];

	assert( NULL != str );
	assert( NULL != rsz );	/* remainssize */
	assert( NULL != frame_num );

	if ( (*rsz) <= 0 ) {
		return nullptr;
	}

	/* 10進数字('0'〜'9')の文字位置(ii)を探す */
	for ( ;'\0' != str[ii] && 0 < (*rsz) ;++ii ,--(*rsz)) {
		if (isdigit(str[ii])) { break; }
	}

	/* 続いて、10進数字('0'〜'9')以外の文字位置(ii)を探す
	   かつ、10進数字('0'〜'9')の文字を抜出す */
	for ( ;'\0' != str[ii] && 0 < (*rsz) ;++ii ,--(*rsz)) {
		if (!isdigit(str[ii])) { break; }
		buffer[jj++] = str[ii];
	}

	/* 数値を得る */
	if ( 0 < jj ) {
		buffer[jj] = '\0';
		*frame_num = atoi( buffer );
	}

	/* 続けて、次の10進数字('0'〜'9')の文字位置(ii)を探す */
	for ( ;'\0' != str[ii] && 0 < (*rsz) ;++ii ,--(*rsz)) {
		if (isdigit(str[ii])) {
			return &str[ii]; /* 数値位置発見 */
		}
	}

	/* 現位置で数値を得たが、次の数値文字がない場合 */
	if ( 0 < jj ) {
		return &str[ii-1];
		/* 最後の数値位置(nullptr以外を返すための無意味な値) */
	}

	/* 次の10進数字('0'〜'9')の文字位置(ii)はない */
	return nullptr;
 }
}

/*--------------------------------------------------------*/

void gts_master::cb_fnum_edit_insert( void )
{
	const char* str;/* 複数数値含文字列の数値始まり位置へのpointer */
	int	rsz;	/* 残り文字数(Remain SiZe) */
	int	frame_num;
	int	ii ,jj;
	char	ca8_tmp[8];

	/* "1" ,"0001" ,"1 2 3" ,"0001 0002 0003" ,etc. */
	str = cl_gts_gui.norinp_fnum_insert->value();
	rsz = cl_gts_gui.norinp_fnum_insert->size();

	while (NULL != (str = next_num_( str ,&rsz ,&frame_num ))) {
		/* frame number listから、insertする
		(frame_numと同じかより大きいframe(jj)の)位置(ii)を得る */
		for (ii=1; ii<=cl_gts_gui.selbro_fnum_list->size(); ++ii) {
			jj = atoi( cl_gts_gui.selbro_fnum_list->text(ii) );
			if (frame_num <= jj) { break; }
		}
		/* すでにあるフレームは飛ばして次へ */
		if (jj == frame_num) { continue; }
		/* insert&Scroll for viewing */
		sprintf( ca8_tmp ,"%04d" ,frame_num );
		cl_gts_gui.selbro_fnum_list->insert( ii ,ca8_tmp );
		cl_gts_gui.selbro_fnum_list->middleline( ii );
	}
}
