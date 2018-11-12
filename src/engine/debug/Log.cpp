//
// Created by codewing on 12.11.18.
//

#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::engineLogger;
std::shared_ptr<spdlog::logger> Log::gameLogger;

void Log::initialize() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    engineLogger = spdlog::stdout_color_mt("ENGINE");
    engineLogger->set_level(spdlog::level::trace);

    gameLogger = spdlog::stdout_color_mt("GAME");
    gameLogger->set_level(spdlog::level::trace);
}
