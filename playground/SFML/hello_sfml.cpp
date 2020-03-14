//
// Created by Jedzia on 14.03.2020.
//

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
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
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock; // starts the clock
    const float Speed = 500.f;
    float x = 0, y = 0;

    while(window.isOpen()) {
        sf::Time elapsed = clock.getElapsedTime();
        //std::cout << elapsed.asSeconds() << std::endl;
        clock.restart();

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();

        shape.setPosition(x, y);
        x += Speed * elapsed.asSeconds();
        y += Speed * 0.5f * elapsed.asSeconds();
        if(x > 500)
            x = 0;
        if(y > 500)
            y = 0;
    }

    return 0;
}