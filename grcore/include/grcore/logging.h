//
// Created by Jedzia on 16.03.2020.
//

#ifndef OPENGLTEMPLATE_LOGGING_H
#define OPENGLTEMPLATE_LOGGING_H

#include <string>
#include <iostream>

namespace core {
    void info();

    //using string_view_t = fmt::basic_string_view<char>;
    using string_view_t = std::string;


    template<typename... Args>
    void depp(/*source_loc loc, level::level_enum lvl,`*/ string_view_t fmt, const Args &... /*args*/)
    {
        static_cast<void>(fmt);
        //static_cast<void>(args)...;
    }

    template<typename... Args>
    void log(/*source_loc loc, level::level_enum lvl,`*/ string_view_t fmt, const Args &... args)
    {
        std::cout << "core::log::fmt: "<< fmt << "\n";
        //bool log_enabled = should_log(lvl);
        //bool traceback_enabled = tracer_.enabled();
        /*if (!log_enabled && !traceback_enabled)
        {
            return;
        }*/
        //SPDLOG_TRY
        {
            //memory_buf_t buf;
            //fmt::format_to(buf, fmt, args...);
            //details::log_msg log_msg(loc, name_, lvl, string_view_t(buf.data(), buf.size()));
            //log_it_(log_msg, log_enabled, traceback_enabled);
        }
        //SPDLOG_LOGGER_CATCH()

        (std::cout << ... << args) << "<- core::log::args"<< '\n';
    }

    template<typename... Args>
    inline void info(string_view_t fmt, const Args &... args)
    {
        //default_logger_raw()->info(fmt, args...);
        log(fmt, args...);
    }

}
#endif //OPENGLTEMPLATE_LOGGING_H
