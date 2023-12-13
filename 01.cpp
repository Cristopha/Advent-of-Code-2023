//
// Created by Cristopha on 13.12.23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

// reading the file and writing the file line by line into a vector
auto parseInput(std::string_view fileName) {
    std::ifstream inFile(fileName);

    if (!inFile) {

        throw std::runtime_error("could not read file: " + std::string(std::strerror(errno)));
    }

    std::vector<std::string> result;

    std::string line;
    while (getline(inFile, line)) {
        result.push_back(std::move(line));
    }
    return result;
}

auto solve01(std::vector<std::string> &input) {
    int result{0};
    for (const auto &line: input) {
        auto first = std::find_if(line.begin(), line.end(), [](char c) { return std::isdigit(c); });
        auto last = std::find_if(line.rbegin(), line.rend(), [](char c) { return std::isdigit(c); });
        //48 shifts from ascii to actual number ('7'(55) -> 0(55-48 = 7))
        result += static_cast<int>(*first - 48) * 10 + static_cast<int>(*last - 48);
    }
    return result;
}


int main() {
    auto input = parseInput("../../data/input01");
    std::cout << "Solution for part one is: "<<solve01(input)<<std::endl;
}