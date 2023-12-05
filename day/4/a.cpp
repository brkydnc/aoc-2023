#include <bits/stdc++.h>

int main() {
    std::ifstream input { "day/4/input.txt" };

    if (!input) {
        std::cout << "Error opening input.txt" << '\n';
        return EXIT_FAILURE;
    }

    std::size_t sum { 0 };

    for (std::string line; std::getline(input, line);) {
        auto column { line.find(':') };
        auto pipe { line.find('|') };

        std::string_view winning_sv { line.begin() + column + 1, line.begin() + pipe};
        std::string_view numbers_sv { line.begin() + pipe + 1, line.end()};

        std::vector<std::size_t> winning;

        for (auto i : std::views::split(winning_sv, ' ')) {
            if (i.empty()) continue;
            std::size_t number;
            std::from_chars(i.begin(), i.end(), number);
            winning.push_back(number);
        }

        std::size_t count { 0 };

        for (auto i : std::views::split(numbers_sv, ' ')) {
            if (i.empty()) continue;
            std::size_t number;
            std::from_chars(i.begin(), i.end(), number);

            if (std::find(winning.begin(), winning.end(), number) != winning.end())
                count++;
        }

        if (count > 0) {
            sum += 1 << (count - 1);
        }
    }

    std::cout << sum << '\n';

	return 0;
}
