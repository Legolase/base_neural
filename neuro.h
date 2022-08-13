#ifndef NEURO_H
#define NEURO_H

#include "cell_layer.h"

class neuro {
	std::vector<cell_layer> layer;
	size_t size_;
public:
	neuro();
	neuro(const std::vector<size_t>&);
	neuro(const neuro&);

	void update();

	cell_layer& in();
	cell_layer& out();
	size_t size();

	cell_layer& operator[](const size_t);
	const cell_layer& operator[](const size_t) const;
	const neuro& operator=(const neuro&);

	friend std::ostream& operator<<(std::ostream&, const neuro&);

	friend std::istream& operator>>(std::istream&, neuro&);
};

#endif