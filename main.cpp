#include <SFML/Graphics.hpp>
#include "PendulumCart.hpp"
#include <iostream>

int main()
{
	const float c_dist = 1.5; // Cart distance
	const float c_vel = 0; // Cart velocity
	const float p_phi = 1; // Pendulum angle
	const float p_omega = 0; // Pendulum angular velocity
	const float p_mass = 1; // Pendulum mass
	const float c_mass = 10; // Cart mass
	const float p_length = 2; // Pendulum length

	// Create the pendulum-cart object
	PendulumCart pc(c_dist, c_vel, p_phi, p_omega, p_mass, c_mass, p_length);

	// Create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pendulino");

	// We want to update the simulation faster than the graphics
	// So we will start a thread to update the simulation
	// The main thread will be in charge of rendering
	sf::Thread simulation(&PendulumCart::update, &pc);
	simulation.launch();

	// Start the clock to measure the time elapsed between frames
	sf::Clock clock;
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

		// Get the time elapsed since the last frame
		sf::Time elapsed = clock.restart();

		// Draw the pendulum-cart to the window
		window.clear();
		window.draw(pc);
		window.display();
		
	}

	simulation.terminate();
	return 0;

}