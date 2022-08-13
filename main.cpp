#include <iostream>
#include <exception>
#include <typeinfo>

#include "neuro.h"

int main() {
	{
		neuro n({32, 9});
		neuro f = n;

		double d;
		for (int i = 0; i < 100; ++i) {
			for (int i = 0; i < n.in().size(); ++i) {
				//std::cin >> d;
				d = random(-10000, 10000) / 1000.0;
				n.in()[i].in = d;
				f.in()[i].in = d;
			}

			n.update();
			f.update();
			std::cout << "--\n";

			for (int i = 0; i < n.out().size(); ++i) {
				std::cout << n.out()[i].out << " ~ " << f.out()[i].out << '\n';
			}
			std::cout << "=========================\n";
		}
	}
}