#include "neuro_cell.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <exception>
#include <iomanip>

static double normalization(double x) {
	return 1 / (1 + pow(M_E, (-x)));
	//return (std::pow(M_E, 2 * x) - 1) / (std::pow(M_E, 2 * x) + 1);
}

neuro_cell::neuro_cell() : upper_layer(), size_(0), in(0), out(0)
{
}


neuro_cell::neuro_cell(const neuro_cell& from) : upper_layer(from.upper_layer), in(from.in), out(from.out), size_(from.size_)
{
}

void neuro_cell::assign_w(const std::vector<double>& from)
{
#if defined(_DEBUG)
	if (from.size() != size_) {
		throw std::invalid_argument("in function assign from has invalid size");
	}
#endif

	for (int i = 0; i < size_; ++i) {
		upper_layer[i].w = from[i];
	}
}

void neuro_cell::assign_c(std::vector<neuro_cell>& from)
{
	// setting
	upper_layer.resize(from.size());
	size_ = from.size();
	upper_layer.resize(size_);

	for (int i = 0; i < size_; ++i) {
		upper_layer[i].to = &(from[i]);
	}
}

contact& neuro_cell::operator[](const size_t index)
{
	return upper_layer[index];
}

const contact& neuro_cell::operator[](const size_t index) const
{
	return upper_layer[index];
}

void neuro_cell::update()
{
	if (size_) {
		in = 0;
		for (int i = 0; i < size_; ++i) {
			in += upper_layer[i].to->out * upper_layer[i].w;
		}
	}
	out = normalization(in);
}


size_t neuro_cell::size() const
{
	return size_;
}

const neuro_cell& neuro_cell::operator=(const neuro_cell& from)
{
	upper_layer = from.upper_layer;
	size_ = from.size_;
	in = from.in;
	out = from.out;

	return from;
}

std::ostream& operator<<(std::ostream& out, const neuro_cell& c)
{
	
	std::cout << "{ ";
	for (int i = 0; i < c.size_; ++i) {
		std::cout << std::setprecision(10) << c.upper_layer[i].w << ' ';
	}
	std::cout << '}';

	return out;
}

std::istream& operator>>(std::istream& in, neuro_cell& c)
{
	c.upper_layer.clear();
	c.upper_layer.shrink_to_fit();
	c.size_ = 0;

	char ch;
	in >> ch;

	if (ch != '{') {
		throw std::invalid_argument("invalid symbol before reading weight of contacts");
	}

	double d;
	while (true) {
		in >> ch;

		if (ch == '}') {
			break;
		}
		else if ((ch < '0' || ch > '9') && ch != '.' && ch != '-') {
			c.upper_layer.clear();
			c.upper_layer.shrink_to_fit();
			c.size_ = 0;
			throw std::invalid_argument("array must consist of numbers");
		}

		in.putback(ch);
		in >> d;

		++c.size_;
		c.upper_layer.push_back(contact(nullptr, d));
	}

	return in;
}