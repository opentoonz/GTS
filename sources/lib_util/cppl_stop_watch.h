#ifndef cppl_stop_watch_h
#define cppl_stop_watch_h

#include <chrono>

namespace cppl {

class stop_watch { /* 処理時間計測クラス */
public:
	/* 計測スタート(時刻を保存) */
	void start(void);

	/* 経過時間を返す */
	std::chrono::milliseconds stop_ms(void);
private:
	std::chrono::system_clock::time_point start_;
};

} // cppl

#endif /* !cppl_stop_watch_h */
/*
# How to use.
cppl::stop_watch stwa; stwa.start();
...
std::cout << stwa.stop_ms().count() << "milisecond\n";
*/
