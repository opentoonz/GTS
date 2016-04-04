#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <FL/fl_ask.H>
#include <climits>
#include "pri.h"
#include "sane_scan.h"

void iip_scan::device_name(char *s) {
    size_t len = strlen(s);

    this->_device_name = (char*)malloc(len + 1);
    if(!this->_device_name) {
        pri_funct_msg_v("malloc error\n");
        return;
    }
    strncpy(this->_device_name, s, len + 1);
}

int iip_scan::open( void )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr("iip_scan::open()");
	}
    sane_init(NULL, NULL);
	return OK;
}

int iip_scan::device_search(void) {
    const SANE_Device **devlist;
    SANE_Status status;

    status = sane_get_devices(&devlist, SANE_FALSE);
    if(status != SANE_STATUS_GOOD) {
        fl_message("iip_scan::device_search() - sane_get_devices() failed with: %s", sane_strstatus(status));
        return NG;
    }
    int num_devices = 0;
    int i;
    for(i=0; devlist[i]; i++) {
        num_devices++;
    }
    if(num_devices == 0) {
        pri_funct_msg_v("SANE: no scanners found.\n");
        return NG;
    }

    // TODO: allow the user to choose the SANE device instead of just using the first one available
    this->_device_name = (char*)malloc(strlen(devlist[0]->name) + 1);
    if(!this->_device_name) {
        pri_funct_msg_v("malloc error\n");
        return NG;
    }
    strncpy(this->_device_name, devlist[0]->name, strlen(devlist[0]->name) + 1);

    return OK;
}

int iip_scan::setup_unit(void) {
    SANE_Status status;

	if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("iip_scan::setup_unit()");
    }

    if(!this->_device_name) {
        if(this->device_search() != OK) {
            return NG;
        }
    }

    int first_run = 1;
    for(;;) {
        status = sane_open(this->_device_name, &this->sane_handle);
        if(status != SANE_STATUS_GOOD) {
            pri_funct_msg_v("iip_scan::setup_unit() - sane_open() failed with: %s\n", sane_strstatus(status));
            if(this->_device_name && first_run) {
                pri_funct_msg_v("trying a new device search\n");
                if(this->device_search() != OK) {
                    return NG;
                }
            } else {
                return NG;
            }
        } else {
            break;
        }
        first_run = 0;
    }

    this->option_get_info();

    return OK;
}

void iip_scan::option_get_info() {
    this->_option_info.tl_x.num = -1;
    this->_option_info.tl_x.desc = NULL;
    this->_option_info.tl_y.num = -1;
    this->_option_info.tl_y.desc = NULL;
    this->_option_info.br_x.num = -1;
    this->_option_info.br_x.desc = NULL;
    this->_option_info.br_y.num = -1;
    this->_option_info.br_y.desc = NULL;
    this->_option_info.resolution.num = -1;
    this->_option_info.resolution.desc = NULL;
    this->_option_info.x_resolution.num = -1;
    this->_option_info.x_resolution.desc = NULL;
    this->_option_info.y_resolution.num = -1;
    this->_option_info.y_resolution.desc = NULL;
    this->_option_info.mode.num = -1;
    this->_option_info.mode.desc = NULL;
    this->_option_info.threshold.num = -1;
    this->_option_info.threshold.desc = NULL;

    const SANE_Option_Descriptor *option;
    SANE_Int i;

    for(i=0; ; i++) {
        option = sane_get_option_descriptor(this->sane_handle, i);
        if(option == NULL) {
            break;
        }
        if(!option->name) {
            continue;
        }

        if(!strcmp(option->name, SANE_NAME_SCAN_TL_X)) {
            this->_option_info.tl_x.num = i;
            this->_option_info.tl_x.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_TL_Y)) {
            this->_option_info.tl_y.num = i;
            this->_option_info.tl_y.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_BR_X)) {
            this->_option_info.br_x.num = i;
            this->_option_info.br_x.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_BR_Y)) {
            this->_option_info.br_y.num = i;
            this->_option_info.br_y.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_RESOLUTION)) {
            this->_option_info.resolution.num = i;
            this->_option_info.resolution.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_X_RESOLUTION)) {
            this->_option_info.x_resolution.num = i;
            this->_option_info.x_resolution.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_Y_RESOLUTION)) {
            this->_option_info.y_resolution.num = i;
            this->_option_info.y_resolution.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_SCAN_MODE)) {
            this->_option_info.mode.num = i;
            this->_option_info.mode.desc = option;
        } else if(!strcmp(option->name, SANE_NAME_THRESHOLD)) {
            this->_option_info.threshold.num = i;
            this->_option_info.threshold.desc = option;
        }
    }
}

void* iip_scan::option_get_value(ScannerOption *option) {
    void *value = NULL;
    SANE_Status status;
    size_t value_size;

    if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("SANE option_get_value() for '%s'", option->desc->name);
        pri_funct_msg_ttvr("type=%d, unit=%d, size=%d, cap=%d, constraint_type=%d", option->desc->type, option->desc->unit, option->desc->size, option->desc->cap, option->desc->constraint_type);
    }

    switch(option->desc->type) {
        case SANE_TYPE_STRING:
            value_size = option->desc->size * sizeof(SANE_Char);
            break;
        case SANE_TYPE_INT:
        case SANE_TYPE_FIXED:
            value_size = option->desc->size * sizeof(SANE_Word);
            break;
        case SANE_TYPE_BOOL:
            value_size = sizeof(SANE_Word);
            break;
    }
    if(value_size) {
        value = malloc(option->desc->size * sizeof(SANE_Word));
        if(value == NULL) {
            pri_funct_msg_v("malloc() failure");
            exit(-1);
        }
    }
    status = sane_control_option(this->sane_handle, option->num, SANE_ACTION_GET_VALUE, value, NULL);
    if(status != SANE_STATUS_GOOD) {
        fl_message("iip_scan::option_get_value() - sane_control_option() failed with: %s", sane_strstatus(status));
    }
    if(option->desc->type == SANE_TYPE_FIXED) {
        *((SANE_Word*)value) = SANE_UNFIX(*((SANE_Fixed*)value));
    }
    return value;
}

void iip_scan::option_set_value(ScannerOption *option, void *value) {
    SANE_Status status;

    if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("SANE option_set_value() for '%s'", option->desc->name);
        pri_funct_msg_ttvr("type=%d, unit=%d, size=%d, cap=%d, constraint_type=%d", option->desc->type, option->desc->unit, option->desc->size, option->desc->cap, option->desc->constraint_type);
    }

    if(option->desc->type == SANE_TYPE_FIXED) {
        *((SANE_Word*)value) = SANE_FIX(*((SANE_Word*)value));
    }
    if(option->desc->constraint_type == SANE_CONSTRAINT_RANGE) {
        if(*((SANE_Word*)value) < option->desc->constraint.range->min) {
            *((SANE_Word*)value) = option->desc->constraint.range->min;
        } else if(*((SANE_Word*)value) > option->desc->constraint.range->max) {
            *((SANE_Word*)value) = option->desc->constraint.range->max;
        }
    }
    status = sane_control_option(this->sane_handle, option->num, SANE_ACTION_SET_VALUE, value, NULL);
    if(status != SANE_STATUS_GOOD) {
        pri_funct_msg_v("iip_scan::option_set_value() - sane_control_option() failed with: %s\n", sane_strstatus(status));
    }
}

int iip_scan::get_physical_param(void) {
	if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("iip_scan::get_physical_param()");
    }

    const SANE_Option_Descriptor *option;
    void *value;
    SANE_Int i;
    double tl_x, tl_y, br_x, br_y;

    // coordinates
    value = this->option_get_value(&this->_option_info.tl_x);
    if(value){
        tl_x = *((SANE_Word*)value);
        free(value);
        this->_coordinate_unit = this->_option_info.tl_x.desc->unit;
    }

    value = this->option_get_value(&this->_option_info.tl_y);
    if(value){
        tl_y = *((SANE_Word*)value);
        free(value);
    }

    value = this->option_get_value(&this->_option_info.br_x);
    if(value){
        br_x = *((SANE_Word*)value);
        free(value);
    }

    value = this->option_get_value(&this->_option_info.br_y);
    if(value){
        br_y = *((SANE_Word*)value);
        free(value);
    }

	if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("tl_x=%g, tl_y=%g, br_x=%g, br_y=%g", tl_x, tl_y, br_x, br_y);
    }

    // resolution
    if(this->_option_info.resolution.num != -1) {
        value = this->option_get_value(&this->_option_info.resolution);
        if(value){
            this->_d_x_native_resolution = this->_d_y_native_resolution = *((SANE_Word*)value);
            free(value);
        }
    }

    if(this->_option_info.x_resolution.num != -1) {
        value = this->option_get_value(&this->_option_info.x_resolution);
        if(value){
            this->_d_x_native_resolution = *((SANE_Word*)value);
            free(value);
        }
    }

    if(this->_option_info.y_resolution.num != -1) {
        value = this->option_get_value(&this->_option_info.y_resolution);
        if(value){
            this->_d_y_native_resolution = *((SANE_Word*)value);
            free(value);
        }
    }

    this->_d_physical_height = br_y - tl_y;
    this->_d_physical_width = br_x - tl_x;

    // convert the coordinates to cm
    switch(this->_coordinate_unit) {
        case SANE_UNIT_PIXEL:
            this->_d_physical_height = this->_d_physical_height / this->_d_y_native_resolution * 2.54;
            this->_d_physical_width = this->_d_physical_width / this->_d_x_native_resolution * 2.54;
            break;
        case SANE_UNIT_MM:
            this->_d_physical_height /= 10;
            this->_d_physical_width /= 10;
            break;
    }
    return OK;

    // get other options
    if(this->_option_info.threshold.num != -1) {
        value = this->option_get_value(&this->_option_info.threshold);
        if(value){
            this->_d_threshold = *((SANE_Word*)value);
            free(value);
        }
    }

}

double iip_scan::gts_coord_to_sane(double x, double res) {
    // x is in cm
    switch(this->_coordinate_unit) {
        case SANE_UNIT_MM:
            return x * 10;
        case SANE_UNIT_PIXEL:
            return x * 0.393701 * res;
    }
}

int iip_scan::setup_action(void) {
	if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("iip_scan::setup_action()");
    }

    const SANE_Option_Descriptor *option;
    void *value;
    SANE_Int i;
    SANE_String_Const mode;

	switch (this->_e_pixeltype) {
        case E_PIXELTYPE_BW:
            mode = SANE_VALUE_SCAN_MODE_LINEART;
            break;
        case E_PIXELTYPE_GRAYSCALE:
            mode = SANE_VALUE_SCAN_MODE_GRAY;
            break;
        case E_PIXELTYPE_RGB:
            mode = SANE_VALUE_SCAN_MODE_COLOR;
            break;
    }

    // set mode
    this->option_set_value(&this->_option_info.mode, (void*)mode);

    // set resolution
    if(this->_option_info.x_resolution.num != -1 && this->_option_info.y_resolution.num != -1) {
        this->option_set_value(&this->_option_info.x_resolution, &this->_d_x_resolution);
        this->option_set_value(&this->_option_info.y_resolution, &this->_d_y_resolution);
    } else {
        this->option_set_value(&this->_option_info.resolution, &_d_x_resolution);
    }

    // set coordinates
    SANE_Word tl_x, tl_y, br_x, br_y;
    br_y = this->gts_coord_to_sane(this->_d_bottom, this->_d_y_resolution);
    tl_y = this->gts_coord_to_sane(this->_d_top, this->_d_y_resolution);
    br_x = this->gts_coord_to_sane(this->_d_right, this->_d_x_resolution);
    tl_x = this->gts_coord_to_sane(this->_d_left, this->_d_x_resolution);

	if (ON == this->get_i_mv_sw()) {
        pri_funct_msg_ttvr("tl_x=%g, tl_y=%g, br_x=%g, br_y=%g", tl_x, tl_y, br_x, br_y);
    }

    this->option_set_value(&this->_option_info.br_y, &br_y);
    this->option_set_value(&this->_option_info.tl_y, &tl_y);
    this->option_set_value(&this->_option_info.br_x, &br_x);
    this->option_set_value(&this->_option_info.tl_x, &tl_x);

    // set other options
    SANE_Word word_value;

    if(this->_option_info.threshold.num != -1) {
        word_value = this->_d_threshold;
        this->option_set_value(&this->_option_info.threshold, &word_value);
    }

    return OK;
}

int iip_scan::print_all(void) {
	pri_funct_msg_vr("native_resolution x %.16g y %.16g", this->_d_x_native_resolution, this->_d_y_native_resolution);
	pri_funct_msg_vr("physical_area     x %.16g y %.16g", this->_d_physical_width, this->_d_physical_height);

	return OK;
}

void iip_scan::adjust_resolution(ScannerOption *option, double *res) {
    int i, len;
    SANE_Word current_value;
    SANE_Word previous_value = 0;

    if(option->num == -1) {
        option = &this->_option_info.resolution;
    }
    switch(option->desc->constraint_type) {
        case SANE_CONSTRAINT_WORD_LIST:
            len = option->desc->constraint.word_list[0];
            for(i=1; i<=len; i++) {
                current_value = option->desc->constraint.word_list[i];
                if(option->desc->type == SANE_TYPE_FIXED) {
                    current_value = SANE_UNFIX(current_value);
                }

                if(i == 1 && *res < current_value) {
                    *res = current_value;
                    return;
                } else if(i == len && *res > current_value) {
                    *res = current_value;
                    return;
                } else if(*res > previous_value && *res < current_value) {
                    if((*res - previous_value) < ((current_value - previous_value) / 2)) {
                        *res = previous_value;
                    } else {
                        *res = current_value;
                    }
                    return;
                }
                previous_value = current_value;
            }
            break;
        case SANE_CONSTRAINT_RANGE:
            pri_funct_msg_v("Error: resolutions with SANE_CONSTRAINT_RANGE are not supported yet.\n");
            break;
    }
}

void iip_scan::d_x_resolution(double res) {
    this->_d_x_resolution = res;
    this->adjust_resolution(&this->_option_info.x_resolution, &this->_d_x_resolution);
}

void iip_scan::d_y_resolution(double res) {
    this->_d_y_resolution = res;
    this->adjust_resolution(&this->_option_info.y_resolution, &this->_d_y_resolution);
}

int iip_scan::read(void) {
	iip_canvas *clp_canvas;
    SANE_Status status;

	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr("iip_scan::read()");
        pri_funct_msg_ttvr("_d_right=%g, _d_left=%g, _d_x_resolution=%g", this->_d_right, this->_d_left, this->_d_x_resolution);
        pri_funct_msg_ttvr("_d_bottom=%g, _d_top=%g, _d_y_resolution=%g", this->_d_bottom, this->_d_top, this->_d_y_resolution);
	}

	clp_canvas = &(this->_cl_iip_canvas);

	clp_canvas->set_i_mv_sw(this->get_i_mv_sw());
	clp_canvas->set_i_pv_sw(this->get_i_pv_sw());
	clp_canvas->set_i_cv_sw(this->get_i_cv_sw());

    switch(this->_e_pixeltype) {
        case E_PIXELTYPE_BW:
            clp_canvas->cl_ch_info.set_e_ch_num_type(E_CH_NUM_BITBW);
            clp_canvas->set_l_channels(1);
            break;
        case E_PIXELTYPE_GRAYSCALE:
            clp_canvas->cl_ch_info.set_e_ch_num_type(E_CH_NUM_UCHAR);
            clp_canvas->set_l_channels(1);
            break;
        case E_PIXELTYPE_RGB:
            clp_canvas->cl_ch_info.set_e_ch_num_type(E_CH_NUM_UCHAR);
            clp_canvas->set_l_channels(3);
            break;
    }

    SANE_Parameters param;
    static size_t buffer_size = 30 * 1024; // arbitrary value, but must be a multiple of 3 for RGB scans
    static SANE_Byte *buffer;
    SANE_Int read_len; // actually read bytes
    void *canvas;

    buffer = (SANE_Byte*)malloc(buffer_size);
    if(!buffer) {
        pri_funct_msg_v("malloc error\n");
        return NG;
    }

    status = sane_start(this->sane_handle);
    if(status != SANE_STATUS_GOOD) {
        fl_message("iip_scan::read() - sane_start() failed with: %s", sane_strstatus(status));
        return NG;
    }
    do {
        status = sane_get_parameters(this->sane_handle, &param);
        if(status != SANE_STATUS_GOOD) {
            fl_message("iip_scan::read() - sane_get_parameters() failed with: %s", sane_strstatus(status));
            return NG;
        }
        if (ON == this->get_i_mv_sw()) {
            pri_funct_msg_ttvr("param.format = %d", param.format);
            pri_funct_msg_ttvr("param.bytes_per_line = %d", param.bytes_per_line);
            pri_funct_msg_ttvr("param.pixels_per_line = %d", param.pixels_per_line);
            pri_funct_msg_ttvr("param.lines = %d", param.lines);
            pri_funct_msg_ttvr("param.depth = %d", param.depth);
        }
        if(!(param.format == SANE_FRAME_GRAY || param.format == SANE_FRAME_RGB)) {
            // TODO: support the rest
            pri_funct_msg_v("Error: unsupported SANE frame format %d.\n", param.format);
            sane_cancel(this->sane_handle);
            return NG;
        }
        if(param.lines < 0) {
            // TODO: support it
            pri_funct_msg_v("Error: unsupported SANE frame with unknown number of total lines.\n");
            sane_cancel(this->sane_handle);
            return NG;
        }

        // allocate the canvas
        clp_canvas->set_l_width(param.pixels_per_line);
        clp_canvas->set_l_height(param.lines);
        if (OK != clp_canvas->mem_alloc_canvas()) {
            pri_funct_err_bttvr("Error: clp_canvas->mem_alloc_canvas() returns NG.");
            return NG;
        }
        canvas = clp_canvas->get_vp_canvas();

        // read the scanned data
        SANE_Int offset = 0;
        SANE_Int line_offset = 0;
        SANE_Int x, y, written, byte_out_pos, bit_out_pos, byte_in_pos, bit_in_pos, bit_in_is_set;
        SANE_Int read_len_pixels; // actually read pixels (read_len multiplied by 8 for B/W, divided by 3 for RGB)

        for(;;) {
            status = sane_read(this->sane_handle, buffer, buffer_size, &read_len);
            if(status != SANE_STATUS_GOOD) {
                if(status != SANE_STATUS_EOF) {
                    fl_message("iip_scan::read() - sane_read() failed with: %s", sane_strstatus(status));
                    sane_cancel(this->sane_handle);
                    return NG;
                }
                break;
            }

            // write it to the canvas
            written = 0;
            switch(this->_e_pixeltype) {
                case E_PIXELTYPE_BW:
                    read_len_pixels = read_len * CHAR_BIT;
                    break;
                case E_PIXELTYPE_GRAYSCALE:
                    read_len_pixels = read_len;
                    break;
                case E_PIXELTYPE_RGB:
                    read_len_pixels = read_len / 3;
                    break;
            }
            // we need to write the scanned lines from bottom to top
            for(y = param.lines - (int)(offset / param.pixels_per_line) - 1; y>=0; y--) {
                for(x=0; x<param.pixels_per_line; x++) {
                    if(line_offset) {
                        line_offset--;
                        // skip previously written pixels on this line
                        continue;
                    }

                    if(read_len_pixels) {
                        switch(this->_e_pixeltype) {
                            case E_PIXELTYPE_BW:
                                // time for bit twiddling
                                byte_out_pos = (y * param.pixels_per_line + x) / CHAR_BIT;
                                bit_out_pos = (y * param.pixels_per_line + x) % CHAR_BIT;
                                byte_in_pos = written / CHAR_BIT;
                                bit_in_pos = written % CHAR_BIT;
                                // we need to flip the value because we get a negative image from the scanner
                                bit_in_is_set = 1 - ((buffer[byte_in_pos] >> bit_in_pos) & 1);
                                ((SANE_Byte*)canvas)[byte_out_pos] ^= (-bit_in_is_set ^ ((SANE_Byte*)canvas)[byte_out_pos]) & (1 << bit_out_pos);
                                break;
                            case E_PIXELTYPE_GRAYSCALE:
                                ((SANE_Byte*)canvas)[y * param.pixels_per_line + x] = buffer[written];
                                break;
                            case E_PIXELTYPE_RGB:
                                memcpy((SANE_Byte*)canvas + y * param.pixels_per_line * 3 + x * 3, buffer + written * 3, 3);
                                break;
                        }
                        written++;
                        read_len_pixels--;
                        offset++;
                    } else {
                        goto DONE_WRITING;
                    }
                }
            }
DONE_WRITING:
            // number of pixels written on an incomplete line
            line_offset = x % param.pixels_per_line;
        }
    } while(!param.last_frame);

	return OK;
}

int iip_scan::close( void )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "iip_scan::close()" );
	}
    if(this->sane_handle) {
        sane_close(this->sane_handle);
    }
    sane_exit();
	return OK;
}

