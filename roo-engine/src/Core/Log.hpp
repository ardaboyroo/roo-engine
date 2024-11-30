#pragma once

#include <string>

namespace roo
{
    namespace Log
    {
        // TODO: Hide roo-engine macros.
        void roo_log_trace(const std::string& s);
        void roo_log_info(const std::string& s);
        void roo_log_warn(const std::string& s);
        void roo_log_error(const std::string& s);
        void roo_log_fatal(const std::string& s);

        void App_log_info(const std::string& s);
        void App_log_warn(const std::string& s);
        void App_log_error(const std::string& s);
        void App_log_fatal(const std::string& s);

        void Init();
    }
}

// Engine log macros
#define ROO_LOG_INFO(x)     roo::Log::roo_log_info(x)
#define ROO_LOG_WARN(x)     roo::Log::roo_log_warn(x)
#define ROO_LOG_ERROR(x)    roo::Log::roo_log_error(x)
#define ROO_LOG_FATAL(x)    roo::Log::roo_log_fatal(x)

// Client log macros
#define LOG_INFO(x)         roo::Log::App_log_info(x)
#define LOG_WARN(x)         roo::Log::App_log_info(x)
#define LOG_ERROR(x)        roo::Log::App_log_info(x)
#define LOG_FATAL(x)        roo::Log::App_log_info(x)