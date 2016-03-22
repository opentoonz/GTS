#include "tiffio.h"
#include "tif_image_rw.h"

int tif_write_get_i_compression_none( void )
{            return COMPRESSION_NONE;
}
int tif_write_get_i_compression_lzw( void )
{            return COMPRESSION_LZW;
}
int tif_write_get_i_compression_packbits( void )
{            return COMPRESSION_PACKBITS;
}

int tif_write_get_i_compression_faxg4( void )
{            return COMPRESSION_CCITTFAX4;
}

/*
 * 画像の方向(orientation)は、左上を原点基準とし回転するものと考える
 */
/* 縦ゼロ位置が上、横ゼロ位置が左 --> 0度回転した絵 */
int tif_write_get_i_orientation_rot0( void )
{            return ORIENTATION_TOPLEFT;
}

/* 縦ゼロ位置が左、横ゼロ位置が下 --> 90度回転した絵 */
int tif_write_get_i_orientation_rot90( void )
{            return ORIENTATION_LEFTBOT;
}

/* 縦ゼロ位置が下、横ゼロ位置が右 --> 180度回転した絵 */
int tif_write_get_i_orientation_rot180( void )
{            return ORIENTATION_BOTRIGHT;
}

/* 縦ゼロ位置が右、横ゼロ位置が上 --> 270度回転した絵 */
int tif_write_get_i_orientation_rot270( void )
{            return ORIENTATION_RIGHTTOP;
}

/*
 * 左下を原点基準として保存する場合(モノクロ２階調)
 */
/* 縦ゼロ位置が下、横ゼロ位置が左 --> 0度回転した絵 */
int tif_write_get_i_orientation_botleft_rot0( void )
{            return ORIENTATION_BOTLEFT;
}

