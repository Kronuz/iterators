// ctest for iterators: itertools::transform, itertools::chain, and reversed().

#include "itertools.hh"
#include "reversed.hh"

#include <cstdio>
#include <numeric>
#include <vector>

int main() {
	int failures = 0;
	auto check = [&](bool ok, const char* what) {
		if (!ok) { std::fprintf(stderr, "FAIL: %s\n", what); ++failures; }
	};

	// transform: lazily map each element through a function.
	std::vector<int> v{1, 2, 3, 4};
	std::vector<int> doubled;
	for (auto x : itertools::transform([](int n) { return n * 2; }, v.begin(), v.end())) {
		doubled.push_back(x);
	}
	check((doubled == std::vector<int>{2, 4, 6, 8}), "transform doubles each element");

	// chain: iterate two ranges back to back.
	std::vector<int> a{1, 2};
	std::vector<int> b{3, 4, 5};
	std::vector<int> chained;
	for (auto x : itertools::chain(a.begin(), a.end(), b.begin(), b.end())) {
		chained.push_back(x);
	}
	check((chained == std::vector<int>{1, 2, 3, 4, 5}), "chain concatenates two ranges");

	// reversed: walk a container back to front.
	std::vector<int> r;
	for (auto x : reversed(v)) {
		r.push_back(x);
	}
	check((r == std::vector<int>{4, 3, 2, 1}), "reversed walks back to front");

	if (failures == 0) { std::puts("all iterators tests passed"); }
	return failures == 0 ? 0 : 1;
}
