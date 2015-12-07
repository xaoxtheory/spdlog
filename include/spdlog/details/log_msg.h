//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#include <thread>
#include "../common.h"
#include "./format.h"

namespace spdlog
{
namespace details
{
struct log_msg
{
    log_msg() = default;
    log_msg(level::level_enum l):
        logger_name(),
        level(l),
        raw(),
        formatted() {}
    log_msg(level::level_enum l, int line, std::string file, std::string function):
        logger_name(),
        level(l),
        function_name(function),
        source_file(file),
        source_file_line(line),
        raw(),
        formatted() {}


    log_msg(const log_msg& other) :
        logger_name(other.logger_name),
        level(other.level),
        time(other.time),
        thread_id(other.thread_id),
        function_name(other.function_name),
        source_file(other.source_file),
        source_file_line(other.source_file_line)
    {
        if (other.raw.size())
            raw << fmt::BasicStringRef<char>(other.raw.data(), other.raw.size());
        if (other.formatted.size())
            formatted << fmt::BasicStringRef<char>(other.formatted.data(), other.formatted.size());
    }

    log_msg(log_msg&& other) :
        logger_name(std::move(other.logger_name)),
        level(other.level),
        time(std::move(other.time)),
        thread_id(other.thread_id),
        function_name(other.function_name),
        source_file(other.source_file),
        source_file_line(other.source_file_line),
        raw(std::move(other.raw)),
        formatted(std::move(other.formatted))
    {
        other.clear();
    }

    log_msg& operator=(log_msg&& other)
    {
        if (this == &other)
            return *this;

        logger_name = std::move(other.logger_name);
        level = other.level;
        time = std::move(other.time);
        thread_id = other.thread_id;
        function_name = std::move(other.function_name);
        source_file = std::move(other.source_file);
        source_file_line = other.source_file_line;
        raw = std::move(other.raw);
        formatted = std::move(other.formatted);
        other.clear();
        return *this;
    }

    void clear()
    {
        level = level::off;
        raw.clear();
        formatted.clear();
    }

    std::string logger_name;
    level::level_enum level;
    log_clock::time_point time;
    size_t thread_id;
    std::string function_name;
    std::string source_file;
    int source_file_line;
    fmt::MemoryWriter raw;
    fmt::MemoryWriter formatted;
};
}
}
