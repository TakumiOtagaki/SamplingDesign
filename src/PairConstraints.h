#ifndef SAMPLINGDESIGN_PAIR_CONSTRAINTS_H
#define SAMPLINGDESIGN_PAIR_CONSTRAINTS_H

#include <string>
#include <utility>
#include <vector>

void is_valid_target_structure(const std::string& structure);

std::vector<std::pair<int, int>> parse_target_structure_pairs(const std::string& structure);

std::vector<std::pair<int, int>> load_pair_constraints_file(const std::string& path);

std::vector<std::pair<int, int>> merge_validate_pairs(
    const std::string& structure,
    const std::vector<std::pair<int, int>>& base_pairs,
    const std::vector<std::pair<int, int>>& extra_pairs);

#endif  // SAMPLINGDESIGN_PAIR_CONSTRAINTS_H
