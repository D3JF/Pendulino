#include "PendulumCart.hpp"
#include <iostream>

void PendulumCart::setPendulumLength(float p_len)
{
	this->p_len = p_len;
}
void PendulumCart::setPendulumMass(float p_mass)
{
	this->p_mass = p_mass;
}
void PendulumCart::setCartMass(float c_mass)
{
	this->c_mass = c_mass;
}
void PendulumCart::setPendulumMovement(float p_phi, float p_ome, float p_eps)
{
	this->p_phi = p_phi;
	this->p_ome = p_ome;
	this->p_eps = p_eps;
}
void PendulumCart::setCartMovement(float c_x, float c_vx, float c_ax)
{
	this->c_x = c_x;
	this->c_vx = c_vx;
	this->c_ax = c_ax;
}

void PendulumCart::update()
{
	// Create a clock to measure the time between updates
	sf::Clock clock;

	while (true)
	{

		// Get the time elapsed since the last update
		float dt = clock.restart().asSeconds();

		// Here, we have isolated the second derivatives of angular acceleration (eps) and linear acceleration (ax)
		// We use a basic Newton's differential scheme to get back to the angle (phi) and distance (x)
		// I promise the equations look less intimidating on paper.
		p_eps =
			-std::sin(p_phi) * ((p_mass + c_mass) * 9.81 + p_mass * p_len * p_ome * p_ome * std::cos(p_phi))
			/
			(c_mass + p_mass - p_mass * std::cos(p_phi) * std::cos(p_phi))
			/
			p_len;
		c_ax =
			p_mass * std::sin(p_phi) * (p_len * p_ome * p_ome + 9.81 * std::cos(p_phi))
			/
			(c_mass + p_mass - p_mass * std::cos(p_phi) * std::cos(p_phi));
		p_ome = p_ome + p_eps * dt;
		c_vx = c_vx + c_ax * dt;
		p_phi = p_phi + p_ome * dt;
		c_x = c_x + c_vx * dt;

	}
}

void PendulumCart::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transforms (basically boilerplate)
	states.transform *= getTransform();
	// No textures will be used
	states.texture = NULL;

	// Create pendulum and cart shapes
	sf::CircleShape pendulum(10.f);
	pendulum.setFillColor(sf::Color::Magenta);
	pendulum.setOutlineColor(sf::Color::Blue);
	sf::RectangleShape cart(sf::Vector2f(40.f, 20.f));
	cart.setFillColor(sf::Color::Green);
	cart.setOutlineColor(sf::Color::White);

	// Now we need to place them accordingly to the origin
	int scale = 200;
	sf::Vector2f cart_pos = origin + sf::Vector2f(c_x * scale, 0);
	sf::Vector2f pendulum_pos = origin + sf::Vector2f((c_x + p_len * std::sin(p_phi)) * scale, p_len * std::cos(p_phi) * scale);
	pendulum.setPosition(pendulum_pos);
	cart.setPosition(cart_pos);

	// Finally, we make a line connecting the cart center to the pendulum center
	// Let's get the center of the cart and pendulum
	sf::Vector2f cart_center = cart_pos + sf::Vector2f(cart.getSize().x / 2, cart.getSize().y / 2);
	sf::Vector2f pendulum_center = pendulum_pos + sf::Vector2f(pendulum.getRadius(), pendulum.getRadius());
	// Now we can make the line
	sf::Vertex line[] =
	{
		sf::Vertex(cart_center),
		sf::Vertex(pendulum_center)
	};


	// We are ready to draw!
	target.draw(pendulum, states);
	target.draw(cart, states);
	target.draw(line, 2, sf::Lines, states);

	// We can also draw the origin
	sf::CircleShape origin(5.f);
	origin.setFillColor(sf::Color::Red);
	origin.setPosition(this->origin);
	target.draw(origin, states);


}
