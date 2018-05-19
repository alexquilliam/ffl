#include <chrono>

#include <utils.hpp>

long get_time_ms() {
	auto current_time = std::chrono::system_clock::now();
	auto current_time_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(current_time);
	auto epoch = current_time_ms.time_since_epoch();
	long current_time_long = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

	return current_time_long;
}
