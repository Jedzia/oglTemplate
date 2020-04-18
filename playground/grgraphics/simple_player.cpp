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
#include <grcore/DataAcquisition.h>
#include <grcore/Logging.h>
#include <grcore/Telemetry.h>
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

    MyApplication() : grg::SimpleApplication(), m_shape(MyShape({100.F, 50.F})) {
        m_shape.setFillColor(sf::Color::Magenta);
        //Instrumentor::Instance().BeginSession(__PRETTY_FUNCTION__);
    }

    void Reset() {
        m_coord.x = 0;
        m_coord.y = 0;

        //m_window->getView().getSize()
        //m_player.SetPlayerPosition({100,100});

        // player at: tiles mid position
        //m_player.SetPlayerPosition(m_tileMap.GetSize() / 2.0F);

        // player at: screen mid position
        m_player.SetPlayerPosition(m_window->getView().getSize() / 2.0F);

        // player at: specific tile position
        //m_player.SetPlayerPosition(m_tileMap.GetTilePosition(1,1));
    }

    void OnInit(const grg::Application &application) override {
        m_window = &application.GetWindow();
        //m_view = m_window->getView();
        m_camera = std::make_unique<grg::Camera>(m_player, *m_window);
        //m_MainGameFont = application.GetMainGameFont();
        //const sf::Font& font = application.GetMainGameFont();
        //static_cast<void>(font);
        //static_cast<void>(m_MainGameFont);
        //m_MainGameFont = &application.GetMainGameFont();
        m_infoText = std::make_unique<sf::Text>(__PRETTY_FUNCTION__, application.GetMainGameFont(), 24);
        m_infoText->setPosition({100, 100});
        //std::make_unique<grg::CoordSystem>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}));
        //m_pCoords = std::make_unique<grg::CoordSystem>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}));
        const auto size = application.GetSize();
        m_pCoords = std::make_unique<grg::CoordSystem>(
                sf::FloatRect({0.F, 0.F}, {static_cast<float>(size.x), static_cast<float>(size.y)}),
                application.GetDebugFont());
        m_pCursor = std::make_unique<grg::Cursor>(application.GetWindow(), application.GetDebugFont());
        m_pCursor->SetPlayer(&m_player);
        m_pCursor->SetCamera(m_camera.get());

        // define the level with an array of tile indices
        const unsigned int level[] =
        {
            0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
            1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
            0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
            0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
            0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
            2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
        };

        const char* tileSetFilename = "graphics-vertex-array-tilemap-tileset.png";
        const char* playerFilename = "Esquire.png";

        // create the tilemap from the level definition
        if(!m_tileMap.Load(tileSetFilename, sf::Vector2u(32, 32), level, 16, 8, 4.0F)) {
            spdlog::error("[{}] ERROR loading tile-map resource (id={}).", __PRETTY_FUNCTION__, tileSetFilename);
            //throw std::runtime_error("FUCK YOU");
        }

        if(!m_player.Load(playerFilename, sf::Vector2u(32, 32), level, 16, 8, 4.0F)) {
            spdlog::error("[{}] ERROR loading player resource (id={}).", __PRETTY_FUNCTION__, tileSetFilename);
        }

        //m_player.setPosition(V2F{300.F, 300.F});

        //m_tileMap.Load()
        Reset();
    } // OnInit

    void OnEvent(sf::Event event) override {
        // Only switch when pressed down. A key release is necessary to fire again.
        if(event.key.code == sf::Keyboard::Num1) {
            if(m_keyNum1Released && event.type == sf::Event::KeyPressed) {
                m_drawTiles = !m_drawTiles;
                m_keyNum1Released = false;
            } else {
                if(event.type == sf::Event::KeyReleased) {
                    m_keyNum1Released = true;
                }
            }
        }
    }

    /** Update state.
     *  Refresh the state of your application here. Not guaranteed to run every frame. But can be
     * configured to run more often than in frames to provide a smooth user experience or AI.
     *  @param elapsed The elapsed time between calls to OnUpdate.
     */
    void OnUpdate(sf::Time elapsed) override {
        m_pCoords->OnUpdate(elapsed);
        m_totalTime += elapsed;
        const float elapsedSeconds = elapsed.asSeconds();

        /*if(m_keyNum1Released && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            m_drawTiles = !m_drawTiles;
            m_keyNum1Released = false;
            spdlog::info("Num1 pressed");
           } else {
            m_keyNum1Released = true;
            spdlog::info("Num1 released");
           }*/

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            Reset();
        }

        // former scrolling calculations, now in Player.
        // ToDo: cleanup. maybe use it as a camera delay
        {
            //bool viewChanged = false;
            constexpr float speedUp = 2.0F;
            constexpr float keyAcceleration = 500.0F * speedUp;
            bool moveKeyPressed = false;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // m_view.move(-1.0F * 1000 * elapsedSeconds, 0.0F);
                m_xVelocity -= speedUp * keyAcceleration * elapsedSeconds;
                //spdlog::info("m_xVelocity={}.", m_xVelocity);
                //viewChanged = true;
                moveKeyPressed = true;
            } else {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    //m_view.move(1.0F * 1000 * elapsedSeconds, 0.0F);
                    m_xVelocity += speedUp * keyAcceleration * elapsedSeconds;
                    //spdlog::info("m_xVelocity={}.", m_xVelocity);
                    //viewChanged = true;
                    moveKeyPressed = true;
                }
            }

            const float absVelocity = std::abs(m_xVelocity);
            float speedRamp = 1.0F - elapsedSeconds * speedUp;
            //if(absVelocity + 1.0F < lastAbsVelocity) {
            if(!moveKeyPressed) {
                //} else {
                constexpr float slowDown = 1.4F * speedUp;
                speedRamp = 1.0F - elapsedSeconds * slowDown;
                constexpr float hysteresisEdge = 50.0F * slowDown; // lower edge when friction
                // starts to
                // decrease velocity abrupt.
                if(absVelocity < hysteresisEdge) {
                    speedRamp = 1.0F -
                                ((elapsedSeconds * slowDown * 1.0F) +
                                 (0.01F * ((hysteresisEdge / 10.0F) - (absVelocity / (hysteresisEdge / 5.0F)))));
                    //if(absVelocity < (hysteresisEdge / 100.0F)) {
                    if(absVelocity < (0.5F)) {
                        // stop all movement at 1% of the hysteresis low point.
                        m_xVelocity = 0;
                    }
                }
            }

            m_player.Update(elapsed);

            m_lastAbsVelocity = absVelocity;
            m_xVelocity *= speedRamp;
            //m_csvFile.WriteData(m_xVelocity);
            grcore::writeTelemetryData(static_cast<double>(m_xVelocity));

            { // handle Graph
              //m_view.move(m_xVelocity * elapsedSeconds, 0.0F);

                /*// Here a camera should do its work
                   m_view.setCenter(m_player.GetPlayerPosition() + V2F {0.0F, 0.0F});

                   if(viewChanged || m_window->getView().getTransform() != m_view.getTransform()) {
                    m_window->setView(m_view);
                   }*/

                m_camera->UpdateView(elapsed);
            }

            m_infoText->setString(
                    fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f}, speedRamp: {:.3f}",
                            m_totalTime.asSeconds(),
                            m_coord.x, m_coord.y, m_xVelocity, speedRamp));
        }

        m_pCursor->Update(elapsed);
        m_shape.setPosition(m_coord);
        V2F translation {Speed, Speed * 0.5F};
        m_coord += translation * elapsedSeconds;
        m_drawShape = (
            CheckBounds(m_coord, 500, 500, static_cast<int>(-m_shape.getSize().x),
                    static_cast<int>(-m_shape.getSize().y)) == 0);
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
        if(m_drawTiles) {
            window.draw(m_tileMap);
        }

        if(m_drawShape) {
            window.draw(m_shape);
        }

        if(m_drawPlayer) {
            window.draw(m_player);
        }

        {
            //InstrumentationTimer timer("draw grg::CoordSystem");
            window.draw(*m_pCoords);
            window.draw(*m_pCursor);
            //sf::sleep(sf::milliseconds(1));
        }

        auto oldView = window.getView();
        window.setView(window.getDefaultView());
        window.draw(*m_infoText);
        window.setView(oldView);
        //sf::sleep(sf::milliseconds(1));
    } // OnDraw

private:

    //const sf::Font * m_MainGameFont = nullptr;
    //sf::View m_view;
    MyShape m_shape;
    V2F m_coord {0, 0};
    bool m_drawPlayer = true;
    bool m_drawShape = false;
    bool m_drawTiles = true;
    bool m_keyNum1Released = true;
    const float Speed = 250.F;
    float m_lastAbsVelocity = 0;
    float m_xVelocity = 0;
    grcore::CsvFile<';'> m_csvFile {"data.csv"};
    grg::Player m_player;
    grg::TileMap m_tileMap;
    sf::RenderWindow* m_window;
    sf::Time m_totalTime;
    std::unique_ptr<grg::Camera> m_camera;
    std::unique_ptr<grg::CoordSystem> m_pCoords;
    std::unique_ptr<grg::Cursor> m_pCursor;
    std::unique_ptr<sf::Text> m_infoText;
};

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    // use application logger as main logger
    //core::logging::setUpDefaultLogger(spdlog::default_logger(), spdlog::level::debug);

    // easy named logger setup
    spdlog::set_default_logger(grcore::logging::setUpDefaultLogger("OpenGLTemplate", spdlog::level::debug)); // or
    //NAMED_DEFAULT_LOGGER("MyApplication");

    // shit, this affects the loglevel of the main logger
    auto otherLogger = grcore::logging::setUpLogger("other");
    otherLogger->info("This is the 'other' logger.");

    //spdlog::set_level(spdlog::level::trace);

    spdlog::info("+++ [{}]  called. +++", __PRETTY_FUNCTION__);
    spdlog::info("LogLevel: INFO");
    spdlog::warn("LogLevel: WARN");
    spdlog::debug("LogLevel: DEBUG");
    spdlog::trace("LogLevel: TRACE");
    //auto window = grg::createRenderWindow(1280, 16, 9, __FILE_NAME__);
    auto window = grg::createRenderWindow(1280, 16, 9, __FILE__);
    //window.setFramerateLimit(60 * 4);
    //window.setVerticalSyncEnabled(true);

    grg::Application app(window, false);
    app.Run<MyApplication>();

    return 0;
}// main
