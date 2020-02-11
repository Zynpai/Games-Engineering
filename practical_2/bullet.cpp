#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

//unsigned char bulletPointer;
Bullet Bullet::bullets[256];

float Bullet::speed;
//Create definition for the constructor
//...
Bullet::Bullet() {};

Bullet::Bullet(const sf::Vector2f& pos, const bool mode)  {
	setOrigin(3.5f, 6.0f);
	setPosition(pos);

	setTexture(spritesheet);

	if (_mode)
	{
		setTextureRect(IntRect(32 * 1 + 12, 32 +10, 7, 12));
	}
	else
	{
		setTextureRect(IntRect(32 * 3 + 12, 32 + 10, 7, 12));
	}

	bool _mode = mode;
}

void Bullet::Init()
{
	for (int i = 0; i < 256; i++)
	{
		bullets[i].setPosition(-999.0f,-999.0f);

	}
}

void Bullet::Update(const float &dt) {
	for (auto& b : bullets) {
		b._Update(dt);
	};
}

void Bullet::Render(sf::RenderWindow& window) {
	for (const auto& b : bullets) {
		window.draw(b);
	};
}

void Bullet::_Update(const float& dt) {
	move(0, dt * speed * (/*_mode ? 1.f : -1.f*/-1.0f));
	const sf::FloatRect bulletBounds = getGlobalBounds();

	for (auto ship : ships) {
		// invader bullet on invader collision
		// player bullet on player collision
		if (!_mode && ship->isPlayer())
			continue;
		if (!ship->isExploded() && ship->getGlobalBounds().intersects(bulletBounds)) {
			ship->explode();
			setPosition(-100, -100);
			return;
		}
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
	bullets[bulletPointer++] = Bullet(pos,mode);
}