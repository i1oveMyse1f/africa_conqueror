#include <iostream>
#include <vector>
#include <random>
#include <fstream>

const int kRandomSeed = 228;
std::mt19937 rnd(kRandomSeed);

const int kGroups = 3;
const int kMinAlianceSize = 1;

std::vector<std::vector<double>> read(std::istream& stream = std::cin) {
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

void print_conqueror(const std::vector<int>& conq, std::ostream& stream = std::cout) {
    for (int x : conq) {
        stream << x + 1 << ' ';
    }
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

bool is_nash_equilibrium(const std::vector<int>& colony, const std::vector<std::vector<double>>& d) {
    int cnt[3] = { 0 };
    for (int n_colony : colony) {
        ++cnt[n_colony];
    }

    auto new_colony = colony;

    for (size_t i = 0; i < colony.size(); ++i) {
        if (cnt[colony[i]] > 1) {
            int was = colony[i];
            double current_utility = calc_utility(i, colony, d);
            for (int j = 0; j < kGroups; ++j) {
                if (j != was) {
                    new_colony[i] = j;
                    double new_utility = calc_utility(i, new_colony, d);
                    if (new_utility > current_utility) {
                        return false;
                    }
                }
            }
            new_colony[i] = was;
        }
    }

    return true;
}

std::vector<std::pair<int, int>> find_pos_to_change(const std::vector<int>& colony, const std::vector<std::vector<double>>& d) {
    int cnt[3] = { 0 };
    for (int n_colony : colony) {
        ++cnt[n_colony];
    }

    auto new_colony = colony;

    std::vector<std::pair<int, int>> can_change;

    for (size_t i = 0; i < colony.size(); ++i) {
        if (cnt[colony[i]] > kMinAlianceSize) {
            int was = colony[i];
            double current_utility = calc_utility(i, colony, d);
            for (int j = 0; j < kGroups; ++j) {
                if (j != was) {
                    new_colony[i] = j;
                    double new_utility = calc_utility(i, new_colony, d);
                    if (new_utility > current_utility) {
                        can_change.push_back({ i, j });
                    }
                }
            }
            new_colony[i] = was;
        }
    }

    return can_change;
}

std::vector<int> generate_conqueror(int n) {
    std::vector<int> conqueror(n);
    std::uniform_int_distribution<int> rand_alianse(0, kGroups - 1);
    for (int& x : conqueror) {
        x = rand_alianse(rnd);
    }
    return conqueror;
}

std::vector<int> find_conqueror(const std::vector<std::vector<double>>& d) {
    int n = d.size();
    std::vector<int> conqueor = generate_conqueror(n);

    int count_iters = 0;

    while (!is_nash_equilibrium(conqueor, d)) {
        if (count_iters % 10'000'000 == 0) {
            std::cerr << "Now " << count_iters << " iters \n";
        }
        auto pos_to_change = find_pos_to_change(conqueor, d);
        while (!is_nash_equilibrium(conqueor, d) && pos_to_change.empty()) {
            conqueor = generate_conqueror(n);
            pos_to_change = find_pos_to_change(conqueor, d);
        }
        std::uniform_int_distribution<int> rand_int(0, pos_to_change.size() - 1);
        auto [i, j] = pos_to_change[rand_int(rnd)];
        conqueor[i] = j;
        ++count_iters;
    }

    return conqueor;
}

int main() {
    //std::ifstream in("dist_matrix.txt");
    //auto d = read(in);

    auto d = read();
    auto conqueror = find_conqueror(d);
    print_conqueror(conqueror);
}
