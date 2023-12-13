//
// Created by Cristopha on 13.12.23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>

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

auto getdigits(std::string_view line) {
    int first{0};
    int last{0};

    std::unordered_map<std::string_view, unsigned> stringToInt =
            {
                    {"one",   1},
                    {"two",   2},
                    {"three", 3},
                    {"four",  4},
                    {"five",  5},
                    {"six",   6},
                    {"seven", 7},
                    {"eight", 8},
                    {"nine",  9},
            };
    //[occurrence, digit]
    std::map<unsigned, unsigned> digits;
    for (const auto &[str, num]: stringToInt) {
        auto found = line.find(str);
        if (found != std::string::npos) {
            digits[found] = stringToInt[str];
        }
        found = line.rfind(str);
        if (found != std::string::npos) {
            digits[found] = stringToInt[str];
        }
    }
    auto f = std::find_if(line.begin(), line.end(), [](char c) { return std::isdigit(c); });
    if (f != line.end()) {
        digits[std::distance(line.begin(), f)] = static_cast<unsigned >(*f - 48);
    }

    auto l = std::find_if(line.rbegin(), line.rend(), [](char c) { return std::isdigit(c); });
    if (l != line.rend()) {
        digits[std::distance(l, line.rend())-1] = static_cast<unsigned >(*l - 48);
    }


    return ((digits.begin()->second) * 10) + digits.rbegin()->second;
}

auto solve02(std::vector<std::string> &input) {
    unsigned result{0};

    for (const auto &line: input) {
        unsigned debug = getdigits(line);
        result += debug;
    }

    return result;
}


int main() {
    auto input = parseInput("../../data/input01");
    std::cout << "Solution for part one is: " << solve01(input) << std::endl;
    std::cout << "Solution for part two is: " << solve02(input) << std::endl;
    std::cout << "End!!" << std::endl;
}