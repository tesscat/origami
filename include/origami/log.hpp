#ifndef ORIGAMI_LOG_HPP
#define ORIGAMI_LOG_HPP

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <memory>

namespace origami {
namespace log {
// void info(std::string info);
// void warn(std::string warn);
// void err(std::string err);
#define INFO( ... ) spdlog::info(__VA_ARGS__)
#define WARN( ... ) spdlog::warn(__VA_ARGS__)
#define ERR( ... ) spdlog::error(__VA_ARGS__)
}
}  // namespace origami

#endif
