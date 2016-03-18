#include <stdlib.h>	/* atoi() */
#include <ctype.h>
#include <assert.h>
#include "gts_master.h"
#include "gts_gui.h"

char *gts_master::_get_next_num( char *cp_str, int *ip_num )
{
	int	ii, jj;
	char	ca1024_tmp[1024];

	assert( NULL != cp_str );
	assert( NULL != ip_num );

	/* next is nothing(end) */
	if ('\0' == cp_str[0]) { return NULL; }

	/* search digit(0...9) */
	for (ii = 0; '\0' != cp_str[ii]; ++ii) {
		if (1024 <= ii) { return NULL; }
		if (isdigit(cp_str[ii])) { break; }
	}
	if ('\0' == cp_str[ii]) { return NULL; }

	/* copy digit(0...9) and search not digit(0...9) */
	for (jj = 0; '\0' != cp_str[ii]; ++ii, ++jj) {
		if (1024 <= ii) { return NULL; }
		if (!isdigit(cp_str[ii])) { break; }
		ca1024_tmp[jj] = cp_str[ii];
	}
	assert(0 < jj);

	/* get number from digit */
	ca1024_tmp[jj] = '\0';
	*ip_num = atoi(ca1024_tmp);

	/* search digit(0...9) */
	for (; '\0' != cp_str[ii]; ++ii) {
		if (1024 <= ii) { return NULL; }
		if (isdigit(cp_str[ii])) { break; }
	}

	/* Need ('\0' == cp_str[ii]) */
	return &cp_str[ii];
}

/*--------------------------------------------------------*/

void gts_master::cb_fnum_edit_insert( void )
{
	int	ii,jj, i_num;
	char	*cp_tmp,
		ca8_tmp[8];

	cp_tmp = (char *)cl_gts_gui.norinp_fnum_insert->value();

	while (NULL != (cp_tmp = this->_get_next_num(cp_tmp, &i_num))) {
		for (ii=1, jj=0; ii <= cl_gts_gui.selbro_fnum_list->size();
		++ii) {
			jj = atoi( cl_gts_gui.selbro_fnum_list->text(ii) );
			if (jj == i_num) { break; }
			if (i_num < jj) { break; }
		}
		if (jj == i_num) { continue; }
		sprintf(ca8_tmp, "%04d", i_num );
		cl_gts_gui.selbro_fnum_list->insert( ii, ca8_tmp);
		cl_gts_gui.selbro_fnum_list->middleline( ii );
	}
}
