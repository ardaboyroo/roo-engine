#include "Log.hpp"

#include <memory>

namespace roo
{
    std::shared_ptr<spdlog::logger> s_EngineLogger;
    std::shared_ptr<spdlog::logger> s_ClientLogger;

    void Log::roo_log_info(const std::string& s)    { s_EngineLogger->info(s);      }
    void Log::roo_log_warn(const std::string& s)    { s_EngineLogger->warn(s);      }
    void Log::roo_log_error(const std::string& s)   { s_EngineLogger->error(s);     }
    void Log::roo_log_fatal(const std::string& s)   { s_EngineLogger->critical(s);  }

    void Log::App_log_info(const std::string& s)    { s_ClientLogger->info(s);      }
    void Log::App_log_warn(const std::string& s)    { s_ClientLogger->warn(s);      }
    void Log::App_log_error(const std::string& s)   { s_ClientLogger->error(s);     }
    void Log::App_log_fatal(const std::string& s)   { s_ClientLogger->critical(s);  }

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] [%n]%$: %v");
        s_EngineLogger = spdlog::stdout_color_mt("ROO");
        s_EngineLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}