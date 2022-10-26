//
// Created by dryerem19 on 10/26/22.
//

#pragma once
#include <spdlog/spdlog.h>

namespace KitEngine::Core
{
    class Log
    {
    public:
        Log() = default;
        ~Log() = default;

        template<typename... Args>
        inline static void Trace(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            spdlog::trace(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline static void Debug(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            spdlog::debug(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline static void Info(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            spdlog::info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline static void Warning(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            spdlog::warn(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline static void Error(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            spdlog::error(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline static void Critical(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            spdlog::critical(fmt, std::forward<Args>(args)...);
        }
    };
}