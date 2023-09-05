#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#define g 9.81

class PendulumCart : public sf::Drawable, public sf::Transformable
{
public:
	PendulumCart (
		float c_dist, // Cart distance
		float c_vel, // Cart velocity
		float p_phi, // Pendulum angle
		float p_omega, // Pendulum angular velocity
		float p_mass, // Pendulum mass
		float c_mass, // Cart mass
		float p_length // Pendulum length
	) :
		c_x(c_dist),
		c_vx(c_vel),
		p_phi(p_phi),
		p_ome(p_omega),
		p_mass(p_mass),
		c_mass(c_mass),
		p_len(p_length),
		c_ax(0),
		p_eps(0),
		origin(0, 0)
	{}

	PendulumCart(float p_len, float p_mass, float c_mass) : 
		p_len(p_len), p_mass(p_mass), c_mass(c_mass),
		c_x(0), c_vx(0), c_ax(0), p_phi(0), p_ome(0), p_eps(0),
		origin(0, 0)
	{}

	/* Setters for the pendulum-cart */
	void setPendulumLength(float p_len);
	void setPendulumMass(float p_mass);
	void setCartMass(float c_mass);
	void setPendulumMovement(float p_phi = 0, float p_ome = 0, float p_eps = 0);
	void setCartMovement(float c_x = 0, float c_vx = 0, float c_ax = 0);

	// Function to numerically update the state of the pendulum
	void update();

private:

	// Origin position in the canvas
	sf::Vector2f origin;

	/* Variables describing the movement of the pendulum-cart*/
	float c_x;
	float c_vx;
	float c_ax;
	float p_phi;
	float p_ome;
	float p_eps;

	/* Variable constants (yes, I am aware that is an oxymoron) of the pendulum-cart*/
	float p_mass;
	float c_mass;
	float p_len;

	// Our implementation of the virtual draw function
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Just a basic clamp, because apparently my compiler doesn't use C++17
	template<class T>
	const T& clamp(const T& x, const T& upper, const T& lower) 
	{
		return std::min(upper, std::max(x, lower));
	}

};
