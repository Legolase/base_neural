#ifndef cell_h
#define cell_h

#include <iostream>
#include <vector>

#include "contact.h"

class neuro_cell {
	std::vector<contact> upper_layer;
	size_t size_;
public:
	double in, out;

	neuro_cell();
	neuro_cell(const neuro_cell&);

	void assign_c(std::vector<neuro_cell>& from);
	void assign_w(const std::vector<double>&);

	contact& operator[](const size_t);
	const contact& operator[](const size_t) const;
	void update();
	size_t size() const;

	const neuro_cell& operator=(const neuro_cell&);

	friend std::ostream& operator<<(std::ostream&, const neuro_cell&);

	friend std::istream& operator>>(std::istream&, neuro_cell&);
};

#endif
