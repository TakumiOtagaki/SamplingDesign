#include "PairConstraints.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>

using namespace std;

void is_valid_target_structure(const string& structure) {
    stack<char> s;
    const string validChars = "().";

    for (char c : structure) {
        if (validChars.find(c) == string::npos) {
            throw runtime_error("Invalid target structure.");
        }

        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty() || s.top() != '(') {
                throw runtime_error("Invalid target structure.");
            }
            s.pop();
        }
    }

    if (!s.empty()) {
        throw runtime_error("Invalid target structure.");
    }
}

vector<pair<int, int>> parse_target_structure_pairs(const string& structure) {
    vector<pair<int, int>> pairs;
    stack<int> stk;

    for (int idx = 0; idx < static_cast<int>(structure.size()); idx++) {
        if (structure[idx] == '(') {
            stk.push(idx);
        } else if (structure[idx] == ')') {
            if (stk.empty()) {
                throw runtime_error("Invalid target structure.");
            }
            int left = stk.top();
            stk.pop();
            pairs.push_back({left, idx});
        }
    }

    if (!stk.empty()) {
        throw runtime_error("Invalid target structure.");
    }
    return pairs;
}

vector<pair<int, int>> load_pair_constraints_file(const string& path) {
    vector<pair<int, int>> pairs;
    if (path.empty()) {
        return pairs;
    }

    ifstream in(path);
    if (!in.is_open()) {
        throw runtime_error("Failed to open pair constraints file.");
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream row(line);
        int i = -1;
        int j = -1;
        string trailing;
        if (!(row >> i >> j) || (row >> trailing)) {
            throw runtime_error("Invalid pair constraints format.");
        }
        pairs.push_back({i, j});
    }
    return pairs;
}

vector<pair<int, int>> merge_validate_pairs(const string& structure,
                                            const vector<pair<int, int>>& base_pairs,
                                            const vector<pair<int, int>>& extra_pairs) {
    vector<pair<int, int>> merged;
    merged.reserve(base_pairs.size() + extra_pairs.size());
    vector<int> partner(structure.size(), -1);

    auto add_pair = [&](pair<int, int> p) {
        int i = p.first;
        int j = p.second;
        if (i > j) {
            swap(i, j);
        }
        if (i < 0 || j < 0 || i >= static_cast<int>(structure.size()) ||
            j >= static_cast<int>(structure.size()) || i == j) {
            throw runtime_error("Pair constraints out of range.");
        }
        if (partner[i] == j && partner[j] == i) {
            return;
        }
        if (partner[i] != -1 || partner[j] != -1) {
            throw runtime_error("Pair constraints overlap target structure positions.");
        }
        partner[i] = j;
        partner[j] = i;
        merged.push_back({i, j});
    };

    for (const auto& p : base_pairs) {
        add_pair(p);
    }
    for (const auto& p : extra_pairs) {
        add_pair(p);
    }

    sort(merged.begin(), merged.end());
    return merged;
}
