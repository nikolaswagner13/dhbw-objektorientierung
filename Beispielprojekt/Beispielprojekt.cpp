#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const double WINDOW_WIDTH = 800;
const double WINDOW_HEIGHT = 600;
const double POS_LEFT = 150;
const double POS_MID = 400;
const double POS_RIGHT = 650;
const double POS_GROUND = 450;
const double GRAVITY = 5;

// Einfache Plattform-Klasse
class Platform {
public:
	double x, y, width, height;
	Platform(double x, double y, double width, double height)
		: x(x), y(y), width(width), height(height) {}

	void draw() const {
		Gosu::Graphics::draw_rect(x, y, width, height, Gosu::Color::GREEN, 0);
	}
};

// Spielerklasse
class Player {
public:
	double x, y, width, height, vel_x, vel_y;
	bool on_ground;
	Gosu::Image runner;

	Player() : x(POS_MID), y(POS_GROUND), width(64), height(160), vel_x(0), vel_y(0), on_ground(false), runner("runner.png") {}

	// Spieler zeichnen
	void draw() const {
		runner.draw(x, y);
	}

	// Spielerbewegung und Schwerkraft anwenden
	void update(const std::vector<Platform>& platforms) {
		// Schwerkraft anwenden
		if (!on_ground) {
			vel_y += 0.5; // Beschleunigung nach unten
		}

		// Bewegung
		x += vel_x;
		y += vel_y;

		// Kollisionsüberprüfung
		for (const auto& platform : platforms) {
			if (collides_with(platform)) {
				if (vel_y > 0) { // Fallt nach unten
					y = platform.y - height;
					vel_y = 0;
					on_ground = true;
				}
			}
		}

		// Seitenbegrenzungen (linke und rechte Bildschirmseite)
		if (x < 0) x = 0;
		if (x + width > 800) x = 800 - width;
	}

	// Tastensteuerung
	void handle_input() {
		// Links und Rechts Bewegung
		if (Gosu::Input::down(Gosu::KB_A)) {
			vel_x = -5;
		}
		else if (Gosu::Input::down(Gosu::KB_D)) {
			vel_x = 5;
		}
		else {
			vel_x = 0;
		}

		// Springen
		if (on_ground && Gosu::Input::down(Gosu::KB_SPACE)) {
			vel_y = -10; // Springkraft
			on_ground = false;
		}
	}

private:
	// Kollisionsabfrage mit Plattformen
	bool collides_with(const Platform& platform) const {
		return x < platform.x + platform.width &&
			x + width > platform.x &&
			y < platform.y + platform.height &&
			y + height > platform.y;
	}
};

// Hauptspielklasse
class GameWindow : public Gosu::Window
{
private:
	Player player;
	std::vector<Platform> platforms;
	Gosu::Image runner;

public:
	GameWindow() : Gosu::Window(800, 600), runner("runner.png")
	{
		set_caption("Jump and Run Spiel");

		// Erstellen von Plattformen
		platforms.push_back(Platform(0, WINDOW_HEIGHT - 50, WINDOW_WIDTH, 20)); // Boden
	}

	// Update des Spiels (60 mal pro Sekunde)
	void update() override {
		player.handle_input();
		player.update(platforms);
	}

	// Spielfeld zeichnen
	void draw() override {
		// Plattformen zeichnen
		for (const auto& platform : platforms) {
			platform.draw();
		}

		// Spieler zeichnen
		player.draw();
	}
};

int main()
{
	GameWindow window;
	window.show();
	return 0;
}
