//
// Created by Jedzia on 17.03.2020.
//

#include <grgraphics/grgraphics.h>
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#  pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#  pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif

#include <fmt/format.h>
#include <spdlog/spdlog.h>
namespace grg {

    void update(sf::Time elapsed) {
        std::string msg = fmt::format("update() Time is {}ms", elapsed.asMilliseconds());
        //spdlog::info(msg);

    }

}