#include <bits/stdc++.h>

// ASSUMPTIONS:
//     - Edges don't have symbols.
//     - No number is captured by more than one symbols.
//     - Numbers are always valid (std::from_chars never fail).

static constexpr auto SKIP { "1234567890." };

std::size_t capture(const std::string& line, std::string::size_type i) {
    std::size_t number;
    std::string::size_type start, end;

    for (end = i; std::isdigit(line[end]) && end < line.size(); end++);
    for (start = i; std::isdigit(line[start]) && start >= 0; start--);

    std::from_chars(&line[start + 1], &line[end], number);

    return number;
}

int main() {
    std::ifstream input { "day/3/input.txt" };

    if (!input) {
        std::cout << "Error opening input.txt" << '\n';
        return EXIT_FAILURE;
    }

    std::size_t sum = 0;
    std::string prev, line, next;

    // Assume `number of lines` >= 2, and iterate 2 lines ahead.
    std::getline(input, prev);
    std::getline(input, line);

    // For each line between the first and the last...
    while (std::getline(input, next)) {
        // Find the next symbol.
        for (
            std::string::size_type i = line.find_first_not_of(SKIP);
            i != std::string::npos;
            i = line.find_first_not_of(SKIP, i + 1)
        ) {
            if (line[i] != '*') continue;

            auto adjacent = 0;
            std::size_t ratio = 1;

            // Add the numbers in the previous line.
            if (prev[i] != '.') {
                ratio *= capture(prev, i - 1);
                adjacent++;
            } else {
                if (prev[i - 1] != '.') {
                    ratio *= capture(prev, i - 1);
                    adjacent++;
                }

                if (prev[i + 1] != '.') {
                    ratio *= capture(prev, i + 1);
                    adjacent++;
                }
            }

            // Add the numbers in the current line.
            if (line[i - 1] != '.') {
                ratio *= capture(line, i - 1);
                adjacent++;
            }

            if (line[i + 1] != '.') {
                ratio *= capture(line, i + 1);
                adjacent++;
            }

            // Add the numbers in the next line.
            if (next[i] != '.') {
                ratio *= capture(next, i - 1);
                adjacent++;
            } else {
                if (next[i - 1] != '.') {
                    ratio *= capture(next, i - 1);
                    adjacent++;
                }

                if (next[i + 1] != '.') {
                    ratio *= capture(next, i + 1);
                    adjacent++;
                }
            }

            if (adjacent ==  2) {
                sum += ratio;
            }
        }

        prev = line;
        line = next;
    }

    std::cout << sum << '\n';

	return 0;
}
