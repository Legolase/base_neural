#ifndef CELL_LAYER_H
#define CELL_LAYER_H

#include <vector>
#include "neuro_cell.h"

class cell_layer {
	std::vector<neuro_cell> layer;
	size_t size_;
public:
	cell_layer(const size_t size = 0);
	cell_layer(const size_t size, cell_layer& upper_layer);
	cell_layer(const cell_layer&);

	void assign(cell_layer&);

	neuro_cell& operator[](const size_t);
	const neuro_cell& operator[](const size_t) const;

	void update();
	size_t size() const;

	const cell_layer& operator=(const cell_layer& from);

	friend std::ostream& operator<<(std::ostream&, const cell_layer&);

	friend std::istream& operator>>(std::istream&, cell_layer&);
};

#endif