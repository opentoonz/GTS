#ifndef iip_crop_and_downsample_h
#define iip_crop_and_downsample_h

#include <vector>

/*
	親を元画像
	子を切抜き&縮小画像
	として、子を表示するために使うクラス
*/
class iip_crop_and_downsample {
public:
	iip_crop_and_downsample()
		:pa_w_(0) ,pa_h_(0) ,pa_ch_(0) ,pa_by_(0)
		,pa_xo_(0) ,pa_yo_(0) ,pa_xs_(0) ,pa_ys_(0)
		,max_w_(0) ,max_h_(0) ,max_ch_(0) ,max_by_(0)
		,xs_(0) ,ys_(0)
		,x_subpixel_division_(0)
		,y_subpixel_division_(0)
		,subpixel_min_div_(4)
		,subpixel_max_div_(16) /* 積算の最大値の関係でmax必須 */
		,parent_data_(nullptr)
	{
	}
	~iip_crop_and_downsample()
	{
	}

	/* メモリの無駄を防ぐため、最初に最大量を確保する
		max_w ,max_hは表示モニターの最大幅高さを指定する
		application立ち上がり時に実行
	*/
	bool reserve_max_memory(
		const int max_w
		,const int max_h
		,const int max_ch=3
		,const int max_by=2
	);

	/* 実行毎にCrop元と結果画像のサイズを設定する
		xs,ysはmax_w_,max_h_値と同じか小さい値
		エラーはtrueを返す --> エラー処理
		成功ならfalseを返す
		表示するエリア変更する都度実行
	*/
	bool set_mapping(
		void *parent_data
		,const int pa_w , const int pa_h
		,const int pa_ch ,const int pa_by /* parent_dataの大きさ */
		,const int pa_xo ,const int pa_yo
		,const int pa_xs ,const int pa_ys /* parentからの切取範囲 */
		,const int xs ,const int ys/* 結果大きさ ch,byは親と同じ */
	);

	/* 処理実行 */
	void exec( void );

	std::vector<char> child_out;

private:
	int	pa_w_ , pa_h_ , pa_ch_ , pa_by_ /* 親の画像サイズ */
		, pa_xo_ , pa_yo_ , pa_xs_ , pa_ys_; /* Cropする範囲 */
	int	max_w_ , max_h_ , max_ch_ , max_by_ /* 子の画像最大サイズ */
		, xs_ , ys_; /* CropしたあとDownsampleしたいサイズ */

	/* antialiasのための処理用パラメータ */
	int	x_subpixel_division_
		,y_subpixel_division_
		,subpixel_min_div_
		,subpixel_max_div_;
	void *parent_data_;

	std::vector<int> array_x_;
	std::vector<int> array_y_;
	std::vector<int> array_sl_;
};

#endif /* !iip_crop_and_downsample_h */
