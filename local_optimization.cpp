#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int kRandomSeed = 228;
mt19937 rnd(kRandomSeed);

const int kGroups = 3;

pair<vector<double>, vector<vector<double>>> read(istream& stream = std::cin) {
    int n;
    stream >> n;
    vector<double> w(n);
    for (auto&x : w) {
        stream >> x;
    }
    vector<vector<double>> d(n, vector<double>(n));
    for (auto& x : d) {
        for (auto& y : x) {
            stream >> y;
        }
    }
    return {w, d};
}

void print_conqueror(const vector<int>& conq, ostream& stream = std::cout) {
    for (int x : conq) {
        stream << x + 1 << ' ';
    }
}

double calc_utility(int i, const vector<int>& colony, const vector<double>& w, const vector<vector<double>>& d) {
    double utility = 0;
    for (size_t j = 0; j < colony.size(); ++j) {
        if (colony[j] == colony[i]) {
            utility += w[j] * d[i][j];
        }
    }
    return utility;
}

vector<pair<int, int>> is_nash_eq(const vector<int>& colony, const vector<double>& w, const vector<vector<double>>& d) {
    int cnt[3] = { 0 };
    for (int n_colony : colony) {
        ++cnt[n_colony];
    }

    auto new_colony = colony;

    vector<pair<int, int>> can_change;

    for (size_t i = 0; i < colony.size(); ++i) {
        if (cnt[colony[i]] > 1) {
            int was = colony[i];
            double current_utility = calc_utility(i, colony, w, d);
            for (int j = 0; j < kGroups && j != was; ++j) {
                new_colony[i] = j;
                if (calc_utility(i, new_colony, w, d) > current_utility) {
                    can_change.push_back({ i, j });
                }
            }
            new_colony[i] = was;
        }
    }

    return can_change;
}

std::vector<int> find_conqueror(const vector<double>& w, const vector<vector<double>>& d) {
    int n = w.size();
    vector<int> conq(n);
    for (int i = 0; i < n; ++i) {
        conq[i] = i % kGroups;
    }

    int count_iters = 0;

    auto need_change = is_nash_eq(conq, w, d);
    while (!need_change.empty())  {
        if (count_iters % 10000 == 0) {
            cerr << "Now " << count_iters << "iters \n";
        }
        uniform_int_distribution<int> rand_int(0, need_change.size());
        auto [i, j] = need_change[rand_int(rnd)];
        conq[i] = j;
        need_change = is_nash_eq(conq, w, d);
        ++count_iters;
    }

    return conq;
}

int main() {
    auto [w, d] = read();
    auto conq = find_conqueror(w, d);
    print_conqueror(conq);
}
