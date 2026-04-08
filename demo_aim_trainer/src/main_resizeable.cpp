#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Helper function to create a letterboxed view (keeps aspect ratio)
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
    float windowRatio = static_cast<float>(windowWidth) / windowHeight;
    float viewRatio = view.getSize().x / view.getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    bool horizontalSpacing = windowRatio > viewRatio;

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Aim Trainer",
        sf::Style::Default
    );
    window.setFramerateLimit(165);

    // Base view (this defines your fixed aspect ratio)
    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    window.setView(view);

    sf::CircleShape target(30.f);
    target.setFillColor(sf::Color::Red);

    auto spawnTarget = [&]() {
        float x = static_cast<float>(std::rand()) / RAND_MAX * (800.f - 60.f);
        float y = static_cast<float>(std::rand()) / RAND_MAX * (600.f - 60.f);
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

            if (event.type == sf::Event::Resized) {
                window.setView(getLetterboxView(view, event.size.width, event.size.height));
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // Convert mouse position to world coordinates (important with views!)
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                if (target.getGlobalBounds().contains(worldPos)) {
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