#pragma once

#include "elmtpch.h"
#include "spdlog/spdlog.h"

namespace Elements {

class Log {
 public:
  static void init();

  inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {
    return coreLogger;
  }
  inline static std::shared_ptr<spdlog::logger>& getClientLogger() {
    return clientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> coreLogger;
  static std::shared_ptr<spdlog::logger> clientLogger;
};

}  // namespace Elements

// Core log macros
#define ELMT_CORE_TRACE(...) \
  ::Elements::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ELMT_CORE_INFO(...) ::Elements::Log::getCoreLogger()->info(__VA_ARGS__)
#define ELMT_CORE_WARN(...) ::Elements::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ELMT_CORE_ERROR(...) \
  ::Elements::Log::getCoreLogger()->error(__VA_ARGS__)
#define ELMT_CORE_CRITICAL(...) \
  ::Elements::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ELMT_TRACE(...) ::Elements::Log::getClientLogger()->trace(__VA_ARGS__)
#define ELMT_INFO(...) ::Elements::Log::getClientLogger()->info(__VA_ARGS__)
#define ELMT_WARN(...) ::Elements::Log::getClientLogger()->warn(__VA_ARGS__)
#define ELMT_ERROR(...) ::Elements::Log::getClientLogger()->error(__VA_ARGS__)
#define ELMT_CRITICAL(...) \
  ::Elements::Log::getClientLogger()->critical(__VA_ARGS__)