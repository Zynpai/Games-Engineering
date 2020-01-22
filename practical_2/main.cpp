#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
    Keyboard::Z,   // Player1 Down
    Keyboard::Up,  // Player2 UP
    Keyboard::Down // Player2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
Font font;
Text text;
RectangleShape paddles[2];

Vector2f ballVelocity;
bool server = false;

int score = 0;
int score2 = 0;

void reset()
{
	// Update Score Text
	//text.setString("Player 1:" << score << " Player 2:" << score2);
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(770 + paddleSize.x / 2, gameHeight / 2);
	// reset Ball Position
	ball.setPosition(400.0f, 300.0f);

	ballVelocity = { (server ? 100.0f : -100.f), 60.0f };
}

void Load()
{
	//Set size and origin of paddles
	for (auto &p : paddles) 
	{
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
		p.setFillColor(sf::Color::Red);
	}
	
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	ball.setFillColor(sf::Color::Blue);
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(770 + paddleSize.x / 2, gameHeight / 2);
	// reset Ball Position
	ball.setPosition(400.0f, 300.0f);

	ballVelocity = {(server ? 100.0f : -100.f), 70.f};

	// Load font-face from res dir
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
}

void Update(RenderWindow& window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if(event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
	
	float direction = 0.0f;
	if(Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if(Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}

	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[2]))
	{
		direction2--;
	}
	if (Keyboard::isKeyPressed(controls[3]))
	{
		direction2++;
	}
	
	paddles[0].move(0, direction * paddleSpeed * dt);
	paddles[1].move(0, direction2 * paddleSpeed * dt);

	ball.move(ballVelocity * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) {
		// bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) { //top wall
		// top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth)
	{	
		// right wall
		reset();
	}
	else if (bx < 0)
	{
		// left wall
		reset();
	}
	else if (
		//ball is inline or behind paddle
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		)
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10, 0);
	}
	else if (
		//ball is inline or behind paddle
		bx > gameWidth - paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		)
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
	}
}

void Render(RenderWindow& window)
{
	 // Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	 Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}