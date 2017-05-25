#include <iostream>
#include <iomanip>
#include <cassert>

namespace {
/*
w	x方向の幅
h	y方向の幅
shift	次の参照へのシフト量(画像チャンネル数,画像幅)
y_array	h-1個以上のメモリ確保必須
*/
void calcu_bresenham_(
	const int w , const int h , const int shift , int *y_array
)
{
	assert(0 <= w); /* wは0以上 */
	assert(0 <= h); /* hは0以上 */
	assert(0 <= shift); /* shiftは0以上 */

	/* y方向に傾いている
	                        +---+
	-   h +      *          |inc|
	|     |     *           |inc|
	|     |    *            |inc|
	|     |   *             | 0 |
	h OUT +   *             |inc|
	|     |  *              |inc|
	|     | *               |inc|
	|     |*                |inc|
	-   0 *---+---+---+	+---+
	      0           w
	      |---w--|
                  IN
	*/
	/* x方向に傾いている
	                        +-----+
	-   h +        *        |inc  |
	|     |       *         |inc  |
	|     |      *          |inc  |
	|     |     *           |inc*x|
	h OUT +   *             |inc  |
	|     |  *              |inc  |
	|     | *               |inc  |
	|     |*                |inc  |
	-   0 *---+---+---+	+-----+
	      0           w
	      |----w---|
                  IN
	*/
	int dx2_bu = 0;
	const int len = h - 1;
	for (int yy = 0; yy < len; ++yy) {
		/*const int dx2 = static_cast<int>(rint(
			static_cast<double>(yy+1) * w / h
		));*/
		const int dx2 = (yy+1) * w / h;
		y_array[yy] = 0; /* 初期化 */
		for (int ii = dx2_bu ;ii < dx2 ;++ii) {
			y_array[yy] += shift; /* 積算 */
		}
#ifdef DEBUG_CALCU_BRESENHAM
std::cout
<< "yy=" << std::setw(2) << yy
<< " x1=" << std::setw(2) << dx2
<< " x2=" << std::setw(2) << dx2_bu
<< std::endl;
#endif // !DEBUG_CALCU_BRESENHAM
		dx2_bu = dx2; /* 比較のため一つ前を覚えておく */
	}
}
} // namespace

#ifdef DEBUG_CALCU_BRESENHAM

#include <vector>
int main( const int argc , const char** argv)
{
	if (argc != 4) {
		std::cout << argv[0] << " w h shift" << std::endl;
		return 1;
	}

	const int w	= atoi(argv[1]);
	const int h	= atoi(argv[2]);
	const int shift	= atoi(argv[3]);
	std::vector<int> y_array;
	y_array.resize( h - 1 ); /* hより一つ少ない数のバッファー */

	calcu_bresenham_( w , h , shift , y_array.data() );

	int ya=0;
	std::cout << "      0123456789012345678901234567890"<< std::endl;
	for (int ii = 0 ; ii < y_array.size() ; ++ii) {
		std::cout
			<< std::setw(2) << ii
			<< ":" << std::setw(2) << y_array.at(ii)
			<< ":"
		;
		ya += y_array.at(ii);
		for (int jj=0 ;jj<ya ;++jj) {std::cout << " ";}
		std::cout << "*" << std::endl;
	}
	std::cout << "      0123456789012345678901234567890"<< std::endl;

	return 0;
}
#endif // !DEBUG_CALCU_BRESENHAM
