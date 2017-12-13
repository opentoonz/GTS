#include "util_stop_watch.h"

namespace util {

void stop_watch::start(void) {
	this->start_ = std::chrono::system_clock::now();
}

std::chrono::milliseconds stop_watch::stop_ms(void) {
	return	std::chrono::duration_cast<
		std::chrono::milliseconds>(
		std::chrono::system_clock::now() - this->start_
	);
}

} // util
