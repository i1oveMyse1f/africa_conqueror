#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<double>> d(n, vector<double>(n));
	for (auto& x : d) {
		for (auto& y : x) {
			cin >> y;
		}
	}

	for (int i = 0; i < n; ++i) {
		assert(d[i][i] == 0);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			assert(d[i][j] == d[j][i]);
		}
	}
}
