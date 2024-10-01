#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>
#include <iostream>

using namespace std;

const double WINDOW_WIDTH = 800;
const double WINDOW_HEIGHT = 600;
const double POS_LEFT = 150;
const double POS_MID = 400;
const double POS_RIGHT = 650;
const double POS_GROUND = 450;
const double GRAVITY = 5;

class Player
{
public:
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	bool on_ground;
	Gosu::Image runner;

	Player() : pos_x(POS_MID), pos_y(POS_GROUND), vel_x(0), vel_y(0), on_ground(true), runner("runner.png") {}

	void update()
	{
		if (!on_ground)
		{
			vel_y += 0.5;
		}

		if (pos_x <= 0)
		{
			pos_x = 0;
		}
		if (pos_x >= WINDOW_WIDTH - 50)
		{
			pos_x = WINDOW_WIDTH - 50;
		}
	}

	void draw()
	{
		runner.draw(pos_x, pos_y, 1);
	}

	void move()
	{
		if (Gosu::Input::down(Gosu::KB_D))
		{
			vel_x = 5;
		}
		else if (Gosu::Input::down(Gosu::KB_A))
		{
			vel_x = -5;
		}
		else
		{
			vel_x = 0;
		}

		if (on_ground && Gosu::Input::down(Gosu::KB_SPACE))
		{
			vel_y = -10;
			on_ground = false;
		}
		pos_x += vel_x;
		pos_y += vel_y;
	}
};

class Obstacle
{
public:
	double width;
	double pos_x;
	double pos_y;
	Gosu::Image obstacle;

	Obstacle() {};
	Obstacle(double pos_x, double pos_y, Gosu::Image obstacle) : pos_x(pos_x), pos_y(pos_y), obstacle(obstacle) {}

	void draw()
	{

	}
};

class Ground : public Obstacle
{
public:
	Ground() {};
	Ground(double pos_x, double pos_y, Gosu::Image obstacle) : Obstacle(pos_x, pos_y, obstacle) {}

	void draw()
	{
		Gosu::Graphics::draw_rect(0, WINDOW_HEIGHT - 20, WINDOW_WIDTH, 20, Gosu::Color::GREEN, 0);
	}
};

class Barrier : public Obstacle
{
public:

};

class GameWindow : public Gosu::Window
{
private:
	Player player;
	Ground ground;


public:
	GameWindow() : Gosu::Window(WINDOW_WIDTH, WINDOW_HEIGHT), player(), ground()
	{
		set_caption("Jump 'n' Run");
	}

	void update() override
	{
		player.update();
		player.move();
		ground.draw();
	}

	void draw() override
	{
		player.draw();

		// Boden zeichnen
		graphics().draw_rect(0, WINDOW_HEIGHT - 20, WINDOW_WIDTH, 20, Gosu::Color::GRAY, 0);
	}
};

int main()
{
	GameWindow window;
	window.show();
	return 0;
}
