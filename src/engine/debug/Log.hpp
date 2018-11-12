//
// Created by codewing on 12.11.18.
//

#pragma once

#include <spdlog/spdlog.h>

class Log {

public:
    static void initialize();

    inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return engineLogger; }
    inline static std::shared_ptr<spdlog::logger>& getGameLogger() { return gameLogger; }

private:
    static std::shared_ptr<spdlog::logger> engineLogger;
    static std::shared_ptr<spdlog::logger> gameLogger;
};

#define LOG_ENGINE_TRACE(...)   ::Log::getEngineLogger()->trace(__VA_ARGS__)
#define LOG_ENGINE_INFO(...)    ::Log::getEngineLogger()->info(__VA_ARGS__)
#define LOG_ENGINE_WARN(...)    ::Log::getEngineLogger()->warn(__VA_ARGS__)
#define LOG_ENGINE_ERROR(...)   ::Log::getEngineLogger()->error(__VA_ARGS__)
#define LOG_ENGINE_FATAL(...)   ::Log::getEngineLogger()->fatal(__VA_ARGS__)

#define LOG_GAME_TRACE(...)     ::Log::getGameLogger()->trace(__VA_ARGS__)
#define LOG_GAME_INFO(...)      ::Log::getGameLogger()->info(__VA_ARGS__)
#define LOG_GAME_WARN(...)      ::Log::getGameLogger()->warn(__VA_ARGS__)
#define LOG_GAME_ERROR(...)     ::Log::getGameLogger()->error(__VA_ARGS__)
#define LOG_GAME_FATAL(...)     ::Log::getGameLogger()->fatal(__VA_ARGS__)
