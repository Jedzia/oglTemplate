//
// Created by Jedzia on 14.03.2020.
//

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <fmt/format.h>
#include <iostream>

int main() {
    const int WINDOW_WIDTH = 1280;
    const auto WINDOW_RATIO = std::make_tuple(16.1, 9.0);
    //const int WINDOW_HEIGHT = WINDOW_WIDTH * 9 / 16;
    const int WINDOW_HEIGHT = WINDOW_WIDTH * std::get<1>(WINDOW_RATIO) / std::get<0>(WINDOW_RATIO);
    //const int WINDOW_HEIGHT = WINDOW_WIDTH / WINDOW_RATIO;

    auto title = fmt::format("SFML Window ({0}, {1} -> {2:.1f}:{3})", WINDOW_WIDTH, WINDOW_HEIGHT,
            std::get<0>(WINDOW_RATIO), std::get<1>(WINDOW_RATIO));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title);
    //window.setFramerateLimit(60 * 4 );
    window.setVerticalSyncEnabled(true);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Font mainGameFont;
    mainGameFont.loadFromFile("Futura Bk BT Book.ttf");
    sf::Text fpsDisplay("Test, Depp", mainGameFont);

    const float Speed = 250.f;
    float x = 0, y = 0;
    int frame_counter = 0;
    double fps_time = 0;

    sf::Clock clock; // starts the clock
    while(window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float elapsedSeconds = elapsed.asSeconds();
        fps_time = fps_time + elapsedSeconds;
        //std::cout << elapsedSeconds << std::endl;
        //clock.restart();

        sf::Event event{};
        while(window.pollEvent(event)) {
            /*switch(event.type)
                case sf::Event::Closed:
                    window.close();*/

            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                    window.close();
                }
            }
            if(event.type == sf::Event::KeyPressed) {
            }
        }


        /*if(elapsedSeconds < 0.01)
        {
            const char *formatStr = "FPS: {:.1f}, Frame Counter: {}";
            fpsDisplay.setString(fmt::format(formatStr, 1.0 / elapsedSeconds, frame_counter));
        }*/


        if(frame_counter % 60 == 0)
        {
            const char *formatStr = "FPS: {:.1f}, Frame Counter: {}";
            fpsDisplay.setString(fmt::format(formatStr, 60 / fps_time, frame_counter));

            fps_time = 0;
        }

        shape.setPosition(x, y);
        x += Speed * elapsedSeconds;
        y += Speed * 0.5f * elapsedSeconds;
        if(x > 500)
            x = 0;
        if(y > 500)
            y = 0;

        window.clear();
        window.draw(shape);
        window.draw(fpsDisplay);
        window.display();


        //sf::Thread::wait(1);
        frame_counter++;
    }

    return 0;
}