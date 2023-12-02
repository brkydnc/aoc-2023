#include <bits/stdc++.h>

constexpr static std::string_view SET_DELIMITER { "; " };
constexpr static std::string_view HAND_DELIMITER { ", " };

int main() {
    std::ifstream input { "day/2/input.txt" };

    if (!input) {
        std::cout << "Error opening input.txt" << '\n';
        return EXIT_FAILURE;
    }

    std::size_t sum = 0;

    for (std::string line; std::getline(input, line);) {
        std::string_view game = line;

        // Find the reference points.
        auto space_before_id =  game.find(' ');
        auto column = game.find(':');

        // Read the id.
        std::size_t id;
        std::from_chars(game.begin() + space_before_id + 1, game.begin() + column, id);

        // Remove the "Game id: " prefix.
        game.remove_prefix(column + 2);

        std::size_t max_red = 0;
        std::size_t max_green = 0;
        std::size_t max_blue = 0;

        for (auto set : game | std::views::split(SET_DELIMITER)) {
            for (auto hand : set | std::views::split(HAND_DELIMITER)) {
                // Construct a string view from subrange.
                std::string_view view { hand.begin(), hand.end() };

                // Find the space in the middle.
                auto space = view.find(' ');

                // Parse the number of cubes.
                std::size_t count;
                std::from_chars(view.begin(), view.begin() + space, count);

                // Get the color of the cubes;
                std::string_view color { view.begin() + space + 1, view.end() };

                if (color == "red") {
                    max_red = std::max(count, max_red);
                } else if (color == "green") {
                    max_green = std::max(count, max_green);
                } else {
                    max_blue = std::max(count, max_blue);
                }
            }
        }

        sum += max_red * max_green * max_blue;
    }

    std::cout << sum << '\n';

	return 0;
}
