#include <iostream>
#include <vector>
#include <cassert>

int main() {
	int n;
	std::cin >> n;
	assert(std::cin.good());
	assert(n >= 3);
	std::vector<std::vector<double>> d(n, std::vector<double>(n));
	for (auto& x : d) {
		for (auto& y : x) {
			std::cin >> y;
		}
	}

	for (int i = 0; i < n; ++i) {
		assert(d[i][i] == 0);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			assert(d[i][j] == d[j][i]);
			assert(d[i][j] >= 0 && d[i][j] <= 1);
		}
	}
}
