#include "Random.h"
#include <random>

static std::mt19937 gen{ std::random_device()() };
static std::uniform_int_distribution<int> dist(0, 1'000'000);

int random(const int min, const int max) {
	return (dist(gen) % (max - min + 1)) + min;
}