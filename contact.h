#ifndef CONTACT_H
#define CONTACT_H

#include "Random.h"


class neuro_cell;

struct contact
{
	neuro_cell* to;
	double w;

	contact(neuro_cell* t = nullptr, double ww = random(-10000, 10000) / 1000.0);
	contact(const contact&);

	const contact& operator=(const contact&);
};

#endif
