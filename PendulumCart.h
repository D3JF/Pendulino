#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#define g 9.81

class PendulumCart
{
public:
	PendulumCart(
		double c_dist, // Cart distance
		double c_vel, // Cart velocity
		double p_phi, // Pendulum angle
		double p_omega, // Pendulum angular velocity
		double p_mass, // Pendulum mass
		double c_mass, // Cart mass
		double p_length // Pendulum length
	) :
		c_dist(c_dist),
		c_vel(c_vel),
		p_phi(p_phi),
		p_omega(p_omega),
		p_mass(p_mass),
		c_mass(c_mass),
		p_length(p_length)
	{
		c_acc = 0;
		p_eps = 0;
	}

	void update(sf::Time elapsed, int cycles);
	void plot(sf::Image & graph, unsigned int scale);

private:

	// Variables
	double c_dist;
	double c_vel;
	double c_acc;
	double p_phi;
	double p_omega;
	double p_eps;

	// Fixed constants
	double p_mass;
	double c_mass;
	double p_length;

	template<class T>
	const T& clamp(const T& x, const T& upper, const T& lower) {
		return std::min(upper, std::max(x, lower));
	}

};
