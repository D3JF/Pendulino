#include "PendulumCart.h"
#include <iostream>

void PendulumCart::update(sf::Time elapsed, int cycles)
{
	double dt = elapsed.asSeconds();

	p_eps =
		-std::sin(p_phi) * ((p_mass + c_mass) * 9.81 + p_mass * p_length * p_omega * p_omega * std::cos(p_phi))
			/
		(c_mass + p_mass - p_mass * std::cos(p_phi) * std::cos(p_phi))
			/
		p_length;
	c_acc =
		p_mass * std::sin(p_phi) * (p_length * p_omega * p_omega + 9.81 * std::cos(p_phi))
		/
		(c_mass + p_mass - p_mass * std::cos(p_phi) * std::cos(p_phi));
	p_omega = p_omega + p_eps * dt;
	c_vel = c_vel + c_acc * dt;
	p_phi = p_phi + p_omega * dt;
	c_dist = c_dist + c_vel * dt;

	std::cout << "dt = " << elapsed.asSeconds() << " s" << std::endl;
}

void PendulumCart::plot(sf::Image & graph, unsigned int scale)
{
	// Get the width and height of the graph
	sf::Vector2u size = graph.getSize();
	unsigned int w = size.x;
	unsigned int h = size.y;

	// Get the screen position of the cart
	unsigned int c_x = clamp(static_cast<unsigned int>(10 + c_dist * scale + 0.5), w, (unsigned int)10);
	unsigned int c_y = 10;

	// Get the screen position of the pendulum
	unsigned int p_x = clamp(static_cast<unsigned int>(10 + c_x + p_length * std::sin(p_phi) * scale + 0.5), w, (unsigned int)10);
	unsigned int p_y = clamp(static_cast<unsigned int>(10 + p_length * std::cos(p_phi) * scale + 0.5), h, (unsigned int)10);

	// Draw cart and pendulum
	graph.setPixel(c_x, c_y, sf::Color::Cyan);
	graph.setPixel(p_x, p_y, sf::Color::Magenta);
}