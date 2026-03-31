#include <SFML/Graphics.hpp>

int main (void) {
	sf::RenderWindow window(sf::VideoMode(800,600), "test window");

	sf::CircleShape shape(200);
	shape.setFillColor(sf::Color::Red);

	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}