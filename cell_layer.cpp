#include "cell_layer.h"

cell_layer::cell_layer(const size_t size) : 
	layer(size + 1), size_(size)
{
	layer.back().out = 1;
}

cell_layer::cell_layer(const size_t size, cell_layer& upper_layer) : 
	layer(size + 1), size_(size)
{
	for (int i = 0; i < size_; ++i) {
		layer[i].assign_c(upper_layer.layer);
	}
	layer[size_].out = 1;
}

cell_layer::cell_layer(const cell_layer& from) : layer(from.layer), size_(from.size_)
{
}

void cell_layer::assign(cell_layer& upper_layer)
{
	for (int i = 0; i < size_; ++i) {
		layer[i].assign_c(upper_layer.layer);
	}
	layer[size_].out = 1;
}

neuro_cell& cell_layer::operator[](const size_t index)
{
	return layer[index];
}

const neuro_cell& cell_layer::operator[](const size_t index) const
{
	return layer[index];
}

void cell_layer::update()
{
	for (int i = 0; i < size_; ++i) {
		layer[i].update();
	}
}

size_t cell_layer::size() const
{
	return size_;
}

const cell_layer& cell_layer::operator=(const cell_layer& from)
{
	layer = from.layer;
	size_ = from.size_;

	return from;
}

std::ostream& operator<<(std::ostream& out, const cell_layer& cl)
{
	out << "{ ";
	for (size_t i = 0; i < cl.size_; ++i) {
		out << cl.layer[i] << ' ';
	}
	out << '}';
	return out;
}

std::istream& operator>>(std::istream& in, cell_layer& cl)
{
	cl.layer.clear();
	cl.layer.shrink_to_fit();
	cl.size_ = 0;

	char ch;
	in >> ch;

	if (ch != '{') {
		throw std::invalid_argument("invalid symbol before reading weights of cell");
	}

	neuro_cell d;
	while (true) {
		in >> ch;

		if (ch == '}') {
			break;
		}
		else if (ch != '{') {
			throw std::invalid_argument("layer must be consists of cells");
		}

		in.putback(ch);
		in >> d;

		if (cl.size()) {
			if (cl[0].size() != d.size()) {
				cl.layer.clear();
				cl.layer.shrink_to_fit();
				cl.size_ = 0;
				throw std::invalid_argument("count of contacts must be the same in layer");
			}
		}

		++cl.size_;
		cl.layer.push_back(d);
	}
	cl.layer.push_back(neuro_cell());
	cl.layer.back().out = 1;

	return in;
}
