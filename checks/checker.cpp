#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<double>> read_matrix(std::istream& stream) {
    int n;
    stream >> n;
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    for (auto& x : d) {
        for (auto& y : x) {
            stream >> y;
        }
    }
    return d;
}

std::vector<int> read_answer(std::istream& stream) {
    std::vector<int> ans;
    int x;
    while (stream >> x) {
        assert(x >= 1 && x <= 3);
        ans.push_back(x - 1);
    }
    return ans;
}

double calc_utility(int i, const std::vector<int>& colony, const std::vector<std::vector<double>>& d) {
    double utility = 0;
    for (size_t j = 0; j < colony.size(); ++j) {
        if (colony[j] == colony[i]) {
            utility += d[i][j];
        }
    }
    return utility;
}

void check_nash_equilibrium(const std::vector<int>& colony, const std::vector<std::vector<double>>& d) {
    const int kGroups = 3;

    int cnt[kGroups] = { 0 };
    for (int n_colony : colony) {
        ++cnt[n_colony];
    }

    bool does_alianses_not_empty = cnt[0] && cnt[1] && cnt[2];
    assert(does_alianses_not_empty);

    auto new_colony = colony;

    for (size_t i = 0; i < colony.size(); ++i) {
        if (cnt[colony[i]] > 1) {
            int was = colony[i];
            double current_utility = calc_utility(i, colony, d);
            for (int j = 0; j < kGroups; ++j) {
                if (j != was) {
                    new_colony[i] = j;
                    double new_utility = calc_utility(i, new_colony, d);
                    assert(new_utility <= current_utility);
                }
            }
            new_colony[i] = was;
        }
    }
}

int main(int argc, char* argv[]) {
    assert(argc == 3);
    
    std::ifstream input_stream(argv[1]);
    std::ifstream answer_stream(argv[2]);

    auto d = read_matrix(input_stream);
    auto ans = read_answer(answer_stream);
    assert(d.size() == ans.size());

    check_nash_equilibrium(ans, d);
}
