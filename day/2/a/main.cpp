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

                // Check if its possible with only 12 reds, 13 greens, 14 blues;
                if ((color == "red"     && count > 12) ||
                    (color == "green"   && count > 13) ||
                    (color == "blue"    && count > 14)
                ) {
                    goto skip_game;
                }
            }
        }

        sum += id;
skip_game:;
    }

    std::cout << sum << '\n';

	return 0;
}
