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
//#include <grcore/instrumentation.h>
#include <SFML/Graphics/Color.hpp>
#include <grcore/Logging.h>
#include <grgraphics/GrGraphics.h>
#include <grgraphics/warning/SFML_Graphics.h>
#include <memory>
#include <spdlog/sinks/ansicolor_sink.h>

/** @class MyApplication:
 *  Represents the handler for all window actions.
 */
class MyApplication final : public grg::SimpleApplication {
public:

    using MyShape = sf::RectangleShape;
    using V2F = sf::Vector2f;

    MyApplication() : grg::SimpleApplication(), m_shape(MyShape({ 100.F, 50.F })) {
        m_shape.setFillColor(sf::Color::Magenta);
        //Instrumentor::Instance().beginSession(__PRETTY_FUNCTION__);
    }

    void Reset() {
        m_coord.x = 0;
        m_coord.y = 0;
    }

    void OnInit(const grg::Application &application) override {
        m_window = &application.GetWindow();
        //m_MainGameFont = application.GetMainGameFont();
        //const sf::Font& font = application.GetMainGameFont();
        //static_cast<void>(font);
        //static_cast<void>(m_MainGameFont);
        //m_MainGameFont = &application.GetMainGameFont();
        m_backGround = std::make_unique<sf::Text>(__PRETTY_FUNCTION__, application.GetMainGameFont(), 24);
        m_backGround->setPosition({ 100, 100 });
        //std::make_unique<grg::CoordSystem>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}));
        //m_pCoords = std::make_unique<grg::CoordSystem>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}));
        const auto size = application.GetSize();
        m_pCoords = std::make_unique<grg::CoordSystem>(
                sf::FloatRect({0.F, 0.F }, {static_cast<float>(size.x), static_cast<float>(size.y) }),
                application.GetDebugFont());
        m_pCursor = std::make_unique<grg::Cursor>(application.GetWindow(), application.GetDebugFont());
    } // OnInit

    /** Update state.
     *  Refresh the state of your application here. Not guaranteed to run every frame. But can be
     * configured to run more often than in frames to provide a smooth user experience or AI.
     *  @param elapsed The elapsed time between calls to OnUpdate.
     */
    void OnUpdate(sf::Time elapsed) override {
        m_totalTime += elapsed;
        float elapsedSeconds = elapsed.asSeconds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            Reset();
        }

        const float zoomFactor = 1.01F;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::View view = m_window->getView();
            view.zoom(zoomFactor);
            m_window->setView(view);
            spdlog::info("View zoom {}, {}.", view.getSize().x, view.getSize().y);
        } else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                sf::View view = m_window->getView();
                view.zoom(1.0F / zoomFactor);
                m_window->setView(view);
                spdlog::info("View zoom {}, {}.", view.getSize().x, view.getSize().y);
            }
        }

        m_pCursor->Update(elapsed);

        m_backGround->setString(fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}", m_totalTime.asSeconds(), m_coord.x, m_coord.y));

        m_shape.setPosition(m_coord);
        V2F translation {Speed, Speed * 0.5F };
        m_coord += translation * elapsedSeconds;
        m_drawShape = (
            CheckBounds(m_coord, 500, 500, static_cast<int>(-m_shape.getSize().x), static_cast<int>(-m_shape.getSize().y)) == 0);
    } // OnUpdate

    static int CheckBounds(V2F &v, int xMax, int yMax, int xMin = 0, int yMin = 0) {
        int result = 0;
        if(static_cast<int>(v.x) < xMin) {
            v.x = static_cast<float>(xMax);
            result = -1;
        } else if(static_cast<int>(v.x) > xMax) {
            v.x = static_cast<float>(xMin);
            result = 1;
        }

        if(static_cast<int>(v.y) < yMin) {
            v.y = static_cast<float>(yMax);
            result = -2;
        } else if(static_cast<int>(v.y) > yMax) {
            v.y = static_cast<float>(yMin);
            result = 2;
        }

        return result;
    }// CheckBounds

    /** Draw content.
     *  Draw your content to the window every frame.
     *  @param window Provides the RenderTarget::draw(...) endpoint.
     */
    void OnDraw(sf::RenderWindow &window) final {
        // m_pCursor->Update(m_totalTime);

        if(m_drawShape) {
            window.draw(m_shape);
        }

        window.draw(*m_backGround);

        {
            //InstrumentationTimer timer("draw grg::CoordSystem");
            window.draw(*m_pCoords);
            window.draw(*m_pCursor);
            //sf::sleep(sf::milliseconds(1));
        }

        //sf::sleep(sf::milliseconds(1));
    } // OnDraw

private:

    const float Speed = 250.F;
    sf::RenderWindow* m_window;
    V2F m_coord {0, 0 };
    MyShape m_shape;
    std::unique_ptr<grg::CoordSystem> m_pCoords;
    std::unique_ptr<grg::Cursor> m_pCursor;
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
    // use application logger as main logger
    //core::logging::setUpDefaultLogger(spdlog::default_logger(), spdlog::level::debug);

    // easy named logger setup
    spdlog::set_default_logger(core::logging::setUpLogger("MyApplication", spdlog::level::debug)); // or
    //NAMED_DEFAULT_LOGGER("MyApplication");

    auto otherLogger = core::logging::setUpLogger("other");
    otherLogger->info("This is the 'other' logger.");

    spdlog::info("+++ [{}]  called. +++", __PRETTY_FUNCTION__);
    //auto window = grg::createRenderWindow(1280, 16, 9, __FILE_NAME__);
    auto window = grg::createRenderWindow(1280, 16, 9, __FILE__);
    //window.setFramerateLimit(60 * 4);
    //window.setVerticalSyncEnabled(true);

    grg::Application app(window, false);
    app.Run<MyApplication>();

    return 0;
}// main
