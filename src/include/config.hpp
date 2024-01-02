#ifndef CONFIG_HPP
#define CONFIG_HPP

#define LOG_FORMAT "[%H:%M:%S:%f %z] [%n] [%^%l%$] [thread %t] %v"
#define LOG_ENGINE_NAME "origami"
#define LOG_APP_NAME "app"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

#define DEBUG( ... ) printf("DEBUG %s:%i", __FILE__, __LINE__); printf(__VA_ARGS__)

#endif
