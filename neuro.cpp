#include "neuro.h"
#include "Random.h"

neuro::neuro() : layer(), size_(0)
{
}

neuro::neuro(const std::vector<size_t>& v) : layer(), size_(v.size())
{
	layer.reserve(v.size());
	layer.push_back(cell_layer(v[0]));
	for (size_t i = 1; i < size_; ++i) {
		layer.push_back(cell_layer(v[i], layer.back()));
	}
}

neuro::neuro(const neuro& from) : layer(from.layer), size_(from.size_)
{
	for (size_t i = 1; i < size_; ++i) {
		layer[i].assign(layer[i - 1]);
	}
}

void neuro::update()
{
	for (size_t i = 0; i < size_; ++i) {
		layer[i].update();
	}
}

cell_layer& neuro::in()
{
	return layer[0];
}

cell_layer& neuro::out()
{
	return layer[size_ - 1];
}

size_t neuro::size()
{
	return size_;
}

cell_layer& neuro::operator[](const size_t index)
{
	return layer[index];
}

const cell_layer& neuro::operator[](const size_t index) const
{
	return layer[index];
}

const neuro& neuro::operator=(const neuro& n)
{
	layer = n.layer;
	size_ = n.size_;

	for (size_t i = 1; i < n.size_; ++i) {
		layer[i].assign(layer[i - 1]);
	}

	return n;
}

std::ostream& operator<<(std::ostream& out, const neuro& n)
{
	out << "{ ";
	for (size_t i = 0; i < n.size_; ++i) {
		out << n.layer[i] << ' ';
	}
	out << '}';
	return out;
}

std::istream& operator>>(std::istream& in, neuro& n)
{
	n.layer.clear();
	n.layer.shrink_to_fit();
	n.size_ = 0;

	char ch;
	in >> ch;

	if (ch != '{') {
		throw std::invalid_argument("invalid symbol before reading neuro");
	}

	cell_layer d;
	while (true) {
		in >> ch;

		if (ch == '}') {
			break;
		}
		else if (ch != '{') {
			throw std::invalid_argument("neuro must be consists of cell's layer");
		}

		in.putback(ch);
		in >> d;

		++n.size_;
		n.layer.push_back(d);
	}

	for (size_t i = 1; i < n.size_; ++i) {
		n.layer[i].assign(n.layer[i - 1]);
	}

	return in;
}


