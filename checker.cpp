#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<double>> read_matrix(istream& stream) {
    int n;
    stream >> n;
    vector<vector<double>> d(n, vector<double>(n));
    for (auto& x : d) {
        for (auto& y : x) {
            stream >> y;
        }
    }
    return d;
}

vector<int> read_answer(istream& stream) {
    vector<int> ans;
    int x;
    while (stream >> x) {
        assert(x >= 1 && x <= 3);
        ans.push_back(x - 1);
    }
    return ans;
}

double calc_utility(int i, const vector<int>& colony, const vector<vector<double>>& d) {
    double utility = 0;
    for (size_t j = 0; j < colony.size(); ++j) {
        if (colony[j] == colony[i]) {
            utility += d[i][j];
        }
    }
    return utility;
}

void check_nash_eq(const vector<int>& colony, const vector<vector<double>>& d) {
    const int kGroups = 3;

    int cnt[kGroups] = { 0 };
    for (int n_colony : colony) {
        ++cnt[n_colony];
    }

    assert(cnt[0] && cnt[1] && cnt[2]);

    auto new_colony = colony;

    vector<pair<int, int>> can_change;

    for (size_t i = 0; i < colony.size(); ++i) {
        if (cnt[colony[i]] > 1) {
            int was = colony[i];
            double current_utility = calc_utility(i, colony, d);
            for (int j = 0; j < kGroups && j != was; ++j) {
                new_colony[i] = j;
                assert(calc_utility(i, new_colony, d) <= current_utility);
            }
            new_colony[i] = was;
        }
    }
}

int main(int argc, char* argv[]) {
    assert(argc == 3);
    
    ifstream input_stream(argv[1]);
    ifstream answer_stream(argv[2]);

    auto d = read_matrix(input_stream);
    auto ans = read_answer(answer_stream);
    assert(d.size() == ans.size());

    check_nash_eq(ans, d);
}
