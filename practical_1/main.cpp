#include <SFML/Graphics.hpp>

int main()
{
	float position = 0.0f;
	sf::RenderWindow window(sf::VideoMode(400,400), "SFML works!");
	sf::CircleShape shape(100.f);
	sf::CircleShape shape2(100.f);
	sf::CircleShape shape3(100.f);
	sf::CircleShape shape4(100.f);
	sf::RectangleShape shape5(sf::Vector2f(400.0f, 100.0f));
	shape.setFillColor(sf::Color::Red);
	shape2.setFillColor(sf::Color::Green);
	shape3.setFillColor(sf::Color::Yellow);
	shape4.setFillColor(sf::Color::Red);
	shape5.setFillColor(sf::Color::White);
	shape2.setPosition(0.0f, 200.0f);
	shape3.setPosition(200.0f, 0.0f);
	shape4.setPosition(200.0f, 200.0f);
	shape5.setPosition(0, 150.0f);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.draw(shape3);
		window.draw(shape4);
		window.draw(shape5);
		window.display();
	}
	return 0;
}