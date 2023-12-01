#include <bits/stdc++.h>
#include <string_view>

static constexpr std::string_view NUMBERS = "0123456789";

int main() {
    std::ifstream input { "./day/1/input.txt" };

    if (!input) {
        std::cout << "Error opening input.txt" << '\n';
        return EXIT_FAILURE;
    }

    std::size_t sum { 0 };

    for(std::string line; std::getline(input, line);) {
        auto first = line.find_first_of(NUMBERS);
        auto last = line.find_last_of(NUMBERS);

        if (first != line.npos && last != line.npos) {
            sum += 10 * (line[first] - '0') + (line[last] - '0');
        } else {
            std::cout << "The input is erroneous" << '\n';
            return EXIT_FAILURE;
        }
    }

    std::cout << sum << '\n';

	return 0;
}
