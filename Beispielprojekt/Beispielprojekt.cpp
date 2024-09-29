#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


class Player
{
public:
	double x;
	double y;
	bool on_ground;
	Gosu::Image runner;

	Player() : x(WINDOW_WIDTH / 2), y(WINDOW_HEIGHT - 150), on_ground(true), runner("runner.png") {}

	void update()
	{
		if (on_ground == false)
		{
			while (y != (WINDOW_HEIGHT - 150))
			{
				y += 5;
			}
		}
		if (y == (WINDOW_HEIGHT - 150))
		{
			on_ground == true;
		}
	}

	void jump()
	{
		y -= 10;
		on_ground == false;
	}

	void draw()
	{
		runner.draw(x, y, 1);
	}
};

class Block
{
public:
	double x, y, width, height;
	Gosu::Color color;

	Block(double x, double y, double width, double height, Gosu::Color color)
		: x(x), y(y), width(width), height(height), color(color) {}

	void draw() const
	{
		Gosu::Graphics::draw_rect(x, y, width, height, color, 0);
	}
};

class GameWindow : public Gosu::Window
{
private:
	Player player;
	Block block;

public:
	GameWindow() : Gosu::Window(WINDOW_WIDTH, WINDOW_HEIGHT), player(), block(400, WINDOW_HEIGHT - 50, 100, 50, Gosu::Color::RED)
	{
		set_caption("Jump 'n' Run Spiel");
	}

	void update() override
	{
		player.update();

		// Spieler-Bewegung nach rechts
		if (Gosu::Input::down(Gosu::KB_RIGHT))
		{
			player.x += 5;
		}

		// Spieler-Bewegung nach links
		if (Gosu::Input::down(Gosu::KB_LEFT))
		{
			player.x -= 5;
		}

		// Sprung auslösen
		if (Gosu::Input::down(Gosu::KB_SPACE))
		{
			player.jump();
		}


	}

	void draw() override
	{
		player.draw();
		block.draw();

		// Boden zeichnen
		Gosu::Graphics::draw_rect(0, WINDOW_HEIGHT - 20, WINDOW_WIDTH, 20, Gosu::Color::GRAY, 0);
	}
};

int main()
{
	GameWindow window;
	window.show();
	return 0;
}
