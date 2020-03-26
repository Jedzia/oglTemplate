/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the simple_window.cpp class.
 * \file       simple_window.cpp
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/
#include <SFML/Graphics/Color.hpp>
#include <memory>
#include <grcore/instrumentation.h>
#include <grgraphics/grgraphics.h>
#include <grcore/warning/FMT_format_log.h>
#include <grcore/logging.h>
//#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <grcore/grcore.h>
//#include <grcore/resource.h>

/** @class MyApplication:
 *  Represents the handler for all window actions.
 */
class MyApplication final : public grg::SimpleApplication {
  public:
    using MyShape = sf::RectangleShape;
    using v2f = sf::Vector2f;

    MyApplication() : grg::SimpleApplication(), m_shape(MyShape({ 100.F, 50.F })) {
        m_shape.setFillColor(sf::Color::Magenta);
        //Instrumentor::Instance().beginSession(__PRETTY_FUNCTION__);
    }

    /*void OnEvent(const sf::Event &event) override {
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::R)
                Reset();
        }
       }*/
    void Reset() {
        m_coord.x = 0;
        m_coord.y = 0;
    }

    void OnInit(const grg::Application &application) override {
        //m_MainGameFont = application.getMainGameFont();
        //const sf::Font& font = application.getMainGameFont();
        //static_cast<void>(font);
        //static_cast<void>(m_MainGameFont);
        //m_MainGameFont = &application.getMainGameFont();
        m_backGround = std::make_unique<sf::Text>(__PRETTY_FUNCTION__, application.getMainGameFont(), 24);
        m_backGround->setPosition({ 100, 100 });
        //std::make_unique<grg::CoordSystem>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}));
        //p_coords = std::make_unique<grg::CoordSystem>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}));
        const auto size = application.getSize();
        p_coords = std::make_unique<grg::CoordSystem>(sf::FloatRect({ 0.F, 0.F }, { static_cast<float>(size.x), static_cast<float>(size.y) }), application.getDebugFont());
    }

    /** Update state.
     *  Refresh the state of your application here. Not guaranteed to run every frame. But can be
     * configured to run more often than in frames to provide a smooth user experience or AI.
     *  @param elapsed The elapsed time between calls to OnUpdate.
     */
    void OnUpdate(sf::Time elapsed) override {
        m_totalTime += elapsed;
        float elapsedSeconds = elapsed.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            Reset();
        }

        m_backGround->setString(fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}", m_totalTime.asSeconds(), m_coord.x, m_coord.y));

        m_shape.setPosition(m_coord);
        v2f translation{ Speed, Speed * 0.5F };
        m_coord += translation * elapsedSeconds;
        m_drawShape = (checkBounds(m_coord, 500, 500, static_cast<int>(-m_shape.getSize().x), static_cast<int>(-m_shape.getSize().y)) == 0);
    }

    static int checkBounds(v2f &v, int x_max, int y_max, int x_min = 0, int y_min = 0) {
        int result = 0;
        if (static_cast<int>(v.x) < x_min) {
            v.x = static_cast<float>(x_max);
            result = -1;
        } else if (static_cast<int>(v.x) > x_max) {
            v.x = static_cast<float>(x_min);
            result = 1;
        }

        if (static_cast<int>(v.y) < y_min) {
            v.y = static_cast<float>(y_max);
            result = -2;
        } else if (static_cast<int>(v.y) > y_max) {
            v.y = static_cast<float>(y_min);
            result = 2;
        }

        return result;
    }// checkBounds

    /** Draw content.
     *  Draw your content to the window every frame.
     *  @param window Provides the RenderTarget::draw(...) endpoint.
     */
    void OnDraw(sf::RenderWindow &window) final {
        if (m_drawShape) {
            window.draw(m_shape);
        }

        window.draw(*m_backGround);

        {
            //InstrumentationTimer timer("draw grg::CoordSystem");
            window.draw(*p_coords);
            //sf::sleep(sf::milliseconds(1));
        }

        sf::sleep(sf::milliseconds(10));
    }

  private:
    const float Speed = 250.F;
    v2f m_coord{ 0, 0 };
    MyShape m_shape;
    std::unique_ptr<grg::CoordSystem> p_coords;
    bool m_drawShape = false;
    //const sf::Font * m_MainGameFont = nullptr;
    std::unique_ptr<sf::Text> m_backGround;
    sf::Time m_totalTime;
};

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    //logSomething();
    core::bla();
    //locale();

    //spdlog::default_logger()
    spdlog::set_level(spdlog::level::debug);
    //spdlog::set(spdlog::level::debug);
    core::logging::set_level(spdlog::level::debug);
    spdlog::debug("+++ [{}]  called. +++", __PRETTY_FUNCTION__);

    //auto console = spdlog::stdout_color_mt("console");
    //console.set_color_mode(spdlog::color_mode::always);
    //console->warn("Testing");

    //auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    //auto console = std::make_shared<spdlog::logger>("console", sink);
    //console->warn("Testing");

    //auto window = grg::createRenderWindow(1280, 16, 9, __FILE_NAME__);
    auto window = grg::createRenderWindow(1280, 16, 9, __FILE__);
    //window.setFramerateLimit(60 * 4);
    window.setVerticalSyncEnabled(true);

    grg::Application app(window);
    app.Run<MyApplication>();

    return 0;
}// main
