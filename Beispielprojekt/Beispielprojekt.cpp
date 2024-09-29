#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>

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
	double p_pos_x;
	double p_pos_y;
	bool on_ground;
	Gosu::Image runner;

	Player() : p_pos_x(POS_MID), p_pos_y(POS_GROUND), on_ground(true), runner("runner.png") {}

	void update()
	{
		while (p_pos_y != POS_GROUND)
		{
			p_pos_y += GRAVITY;
			on_ground = false;
		}

		if (p_pos_y == POS_GROUND)
		{
			on_ground = true;
		}
	}

	void jump()
	{
		p_pos_y -= 150;
		on_ground = false;
	}

	void draw()
	{
		runner.draw(p_pos_x, p_pos_y, 1);
	}
};

class Obstacle
{
public:
	double width = 50;
	double position;
	Gosu::Image obstacle;

	Obstacle() : position(POS_MID), obstacle("rakete.png") {}

	void draw() const
	{
		// obstacle.draw_rot(pos_x, )
	}
};

class Huerde
{
public:

};

class GameWindow : public Gosu::Window
{
private:
	Player player;
	Obstacle obstacle;

public:
	GameWindow() : Gosu::Window(WINDOW_WIDTH, WINDOW_HEIGHT), player(), obstacle()
	{
		set_caption("Jump 'n' Run");
	}

	void update() override
	{
		player.update();

		// Spieler-Bewegung nach rechts
		if (input().down(Gosu::KB_D))
		{
			if (player.p_pos_x == POS_LEFT)
			{
				player.p_pos_x = POS_MID;
			}
			else if (player.p_pos_x == POS_MID)
			{
				player.p_pos_x = POS_RIGHT;
			}
		}

		// Spieler-Bewegung nach links
		if (input().down(Gosu::KB_A))
		{
			if (player.p_pos_x == POS_RIGHT)
			{
				player.p_pos_x = POS_MID;
			}
			else if (player.p_pos_x == POS_MID)
			{
				player.p_pos_x = POS_LEFT;
			}
		}

		// Sprung auslösen
		if (input().down(Gosu::KB_SPACE))
		{
			player.jump();
		}
	}

	void draw() override
	{
		player.draw();
		obstacle.draw();

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
