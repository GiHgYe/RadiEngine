#pragma once
#include "log/log_system.h"



#define LOG_HELPER(LOG_LEVEL, ...) \
	LogSystem::global_logger.log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(LogSystem::LogLevel::debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogSystem::LogLevel::info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogSystem::LogLevel::warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogSystem::LogLevel::error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogSystem::LogLevel::fatal, __VA_ARGS__);

#define ThereadSleep(_ms) std::this_thread::sleep_for(std::chrono::milliseconds(_ms));


#define __CHECK_GL_ERROR__ { \
        auto gl_error_code=glGetError();\
        if(gl_error_code!=GL_NO_ERROR){\
            LOG_ERROR("gl_error_code: {}",gl_error_code);\
        }\
    }

