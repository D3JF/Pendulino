#include <SFML/Graphics.hpp>
#include "PendulumCart.h"
#include <iostream>

int main()
{
	const double c_dist = 0.25; // Cart distance
	const double c_vel = 0; // Cart velocity
	const double p_phi = 0.5; // Pendulum angle
	const double p_omega = 0; // Pendulum angular velocity
	const double p_mass = 2; // Pendulum mass
	const double c_mass = 1; // Cart mass
	const double p_length = 1; // Pendulum length

	// Graphics start constants
	unsigned int x_0 = 100;
	unsigned int y_0 = 100;

	// Create a graph image where the pendulum-cart will be plotted
	sf::Image graph;
	graph.create(800, 600, sf::Color::Black);

	// Create the pendulum-cart object
	PendulumCart pc(c_dist, c_vel, p_phi, p_omega, p_mass, c_mass, p_length);

	// Create window and start a clock that will track the time delta for each frame
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pendulino");
	sf::Clock clock;

	int cycles = 0;

	// Render loop
	while (window.isOpen())
	{
		// Handle events so the window doesn't freeze
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Update the pendulum-cart
		cycles++;
		sf::Time elapsed = clock.restart();
		pc.update(elapsed, cycles);
		
		// Update the graph
		pc.plot(graph, 400);

		// Draw the graph
		window.clear();
		sf::Texture graph_texture;
		graph_texture.loadFromImage(graph);
		sf::Sprite graph_sprite(graph_texture);
		window.draw(graph_sprite);
		window.display();

	}

	return 0;

}