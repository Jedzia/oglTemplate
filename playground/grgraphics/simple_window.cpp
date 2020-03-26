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
#include <grgraphics/grgraphics.h>

/** @class MyApplication:
 *  Represents the handler for all window actions.
 */
class MyApplication final : public grg::SimpleApplication {
public:

    typedef sf::RectangleShape MyShape;
    typedef sf::Vector2f V2F;

    MyApplication() : grg::SimpleApplication(), m_shape(MyShape({100.f, 50.f})) {
        m_shape.setFillColor(sf::Color::Magenta);
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

        m_shape.setPosition(m_coord);
        V2F translation {Speed, Speed * 0.5f};
        m_coord += translation * elapsedSeconds;
        m_drawShape = !CheckBounds(m_coord, 500, 500,
                static_cast<int>(-m_shape.getSize().x), static_cast<int>(-m_shape.getSize().y));
    }

    static int CheckBounds(sf::Vector2<float> &v, int xMax, int yMax, int xMin = 0, int yMin = 0) {
        int result = 0;
        if(v.x < static_cast<float>(xMin)) {
            v.x = static_cast<float>(xMax);
            result = -1;
        } else if(v.x > static_cast<float>(xMax)) {
            v.x = static_cast<float>(xMin);
            result = 1;
        }

        if(v.y < static_cast<float>(yMin)) {
            v.y = static_cast<float>(yMax);
            result = -2;
        } else if(v.y > static_cast<float>(yMax)) {
            v.y = static_cast<float>(yMin);
            result = 2;
        }

        return result;
    } // CheckBounds

    /** Draw content.
     *  Draw your content to the window every frame.
     *  @param window Provides the RenderTarget::draw(...) endpoint.
     */
    void OnDraw(sf::RenderWindow &window) final {
        if(m_drawShape) {
            window.draw(m_shape);
        }

        sf::sleep(sf::milliseconds(10));
    }

private:

    const float Speed = 250.f;
    V2F m_coord {0, 0};
    MyShape m_shape;
    bool m_drawShape = false;
};

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    //logSomething();
    //core::bla();
    //locale();

    //auto window = grg::createRenderWindow(1280, 16, 9, __FILE_NAME__);
    auto window = grg::createRenderWindow(1280, 16, 9, __FILE__);
    //window.setFramerateLimit(60 * 4);
    window.setVerticalSyncEnabled(true);

    grg::Application app(window);
    app.Run<MyApplication>();

    return 0;
}         // main
