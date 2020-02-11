#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

using namespace sf;
using namespace std;

Player *player;

void Load() {
	player = new Player();

}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	player->Update(dt);	
}

void Render(RenderWindow &window) {
	player->Render(window);
}

  int main() {
	RenderWindow window(VideoMode(800, 600), "Tile Engine");
	
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }