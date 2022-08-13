#include "contact.h"
#include "Random.h"

contact::contact(neuro_cell* t, double ww) : to(t), w(ww)
{
}

contact::contact(const contact& from) : to(from.to), w(from.w)
{
}

const contact& contact::operator=(const contact& from)
{
	to = from.to;
	w = from.w;

	return from;
}
