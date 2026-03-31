#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  sf::RenderWindow window(sf::VideoMode(800, 600), "Aim Trainer");
  window.setFramerateLimit(165);

  sf::CircleShape target(30.f);
  target.setFillColor((sf::Color::Red));

  auto spawnTarget = [&]() {
    float x = std::rand() % (800 - 60);
    float y = std::rand() % (600 - 60);
    target.setPosition(x, y);
  };

  spawnTarget();

  int score = 0;

  sf::Clock clock;
  float reactionTime = 0.f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (target.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                              static_cast<float>(mousePos.y))) {
          reactionTime = clock.restart().asSeconds();
          score++;

          std::cout << "Hit ^-^ SCORE: " << score
                    << " | REACTION TIME: " << reactionTime << "s\n";
          spawnTarget();
        }
      }
    }

    window.clear(sf::Color::Black);
    window.draw(target);
    window.display();
  }

  return 0;
}