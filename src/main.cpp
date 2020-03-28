/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the main.cpp class.
 * \file       main.cpp
 * \date       2020-03-14
 * \author     Jedzia.
 *
 * modified    2020-03-14, Jedzia
 */
/*---------------------------------------------------------*/
//#define USE_SPDLOG 1
#include "precompiled.h"
//
//#include <boost/locale/info.hpp>
//#include <boost/locale.hpp>
#include <ctime>
//#include <grcore/grcore.h>
//#include <grgraphics/grgraphics.h>
#include <iostream>
//#include <locale>

/*
   #include <SFML/Graphics.hpp>
   #include <SFML/System/Clock.hpp>
   #include <SFML/System/Thread.hpp>
   #include <fmt/format.h>
   #include <iostream>
 */

#if USE_DOC_OPTS
static const char USAGE[] =
    R"(Naval Fate.

    Usage:
      naval_fate ship new <name>...
      naval_fate ship <name> move <x> <y> [--speed=<kn>]
      naval_fate ship shoot <x> <y>
      naval_fate mine (set|remove) <x> <y> [--moored | --drifting]
      naval_fate (-h | --help)
      naval_fate --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --speed=<kn>  Speed in knots [default: 10].
      --moored      Moored (anchored) mine.
      --drifting    Drifting mine.
)";

/** Brief description of $(fclass), handle_main_arguments
 *  Detailed description.
 *  @param argc TODO
 *  @param argv TODO
 *  @return TODO
 */
int handle_main_arguments(int argc, const char* * argv) {
    std::map<std::string, docopt::value> args =
        docopt::docopt(USAGE,
                { argv + 1, argv + argc },
                true,                   // show help if requested
                "Naval Fate 2.0");      // version string

    for(auto const &arg : args) {
        std::cout << arg.first << arg.second << std::endl;
    }
    return 0;
}

#endif // if USE_DOC_OPTS

/** Brief description of $(fclass), logSomething
 *  Detailed description.
 *
 */
void logSomething() {
//#if USE_SPDLOG
    //Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");
//#endif
    core::info();
    core::log("Erstes", "Zweites", "Drittes");
    fmt::print("Hello, from {}\n", "{fmt}");
    grg::bla();
}

/** Brief description of $(fclass), locale
 *  Detailed description.
 *
 */
void locale() {
    //using namespace boost::locale;
    using namespace std;
    //generator gen;
    //auto loc = gen("");
    // Create system default locale

    //locale::global(loc);
    // Make it system global

//    cout.imbue(loc);
    // Set as default locale for output

    /*cout << boost::locale::format("Today {1,date} at {1,time} we had run our first localization
       example") % time(0)
         << endl;

       cout << "This is how we show numbers in this locale " << boost::locale::as::number << 103.34
          << endl;
       cout << "This is how we show currency in this locale " << boost::locale::as::currency <<
          103.34 << endl;
       cout << "This is typical date in the locale " << boost::locale::as::date << std::time(0) <<
          endl;
       cout << "This is typical time in the locale " << boost::locale::as::time << std::time(0) <<
          endl;
       cout << "This is upper case " << boost::locale::to_upper("Hello World!") << endl;
       cout << "This is lower case " << boost::locale::to_lower("Hello World!") << endl;
       cout << "This is title case " << boost::locale::to_title("Hello World!") << endl;
       cout << "This is fold case " << boost::locale::fold_case("Hello World!") << endl;*/
}

/** @class MyCircleShape:
 *  Dummy stub for testing sf::CircleShape lifetime.
 */
class MyCircleShape : public sf::CircleShape {
public:

//#pragma clang diagnostic push
    explicit MyCircleShape(float radius = 0, std::size_t pointCount = 30) : CircleShape(radius, pointCount) {
        spdlog::warn("Constructor [{}]", __PRETTY_FUNCTION__);
    }
//#pragma clang diagnostic pop

    ~MyCircleShape() override {
        spdlog::warn("~DESTRUCTOR [{}]", __PRETTY_FUNCTION__);
    }
};

/** @class MyApplication:
 *  Represents the handler for all window actions.
 */
class MyApplication final : public grg::SimpleApplication {
public:

    MyApplication() : grg::SimpleApplication(), shape(MyCircleShape(100.f)) {
        shape.setFillColor(sf::Color::Green);
    }

    /*void OnEvent(const sf::Event &event) override {
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::R)
                Reset();
        }
       }*/
    void Reset() {
        x = 0;
        y = 0;
    }

    /** Update state.
     *  Refresh the state of your application here. Not guaranteed to run every frame. But can be
     * configured to run more often than in frames to provide a smooth user experience or AI.
     *  @param elapsed The elapsed time between calls to OnUpdate.
     */
    void OnUpdate(sf::Time elapsed) override {
        float elapsedSeconds = elapsed.asSeconds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            Reset();
        }

        shape.setPosition(x, y);
        x += Speed * elapsedSeconds;
        y += Speed * 0.5f * elapsedSeconds;
        if(x > 500) {
            x = 0;
        }

        if(y > 500) {
            y = 0;
        }
    } // OnUpdate

    /** Draw content.
     *  Draw your content to the window every frame.
     *  @param window Provides the RenderTarget::draw(...) endpoint.
     */
    void OnDraw(sf::RenderWindow &window) final {
        window.draw(shape);
    }

private:

    const float Speed = 250.f;
    float x = 0, y = 0;
    MyCircleShape shape;
};

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    logSomething();
    core::bla();
    locale();

    auto window = grg::createRenderWindow(1280, 16, 9);
    //window.setFramerateLimit(60 * 4);

    grg::Application app(window, false, 120);
    app.Run<MyApplication>();

    return 0;
}         // main
