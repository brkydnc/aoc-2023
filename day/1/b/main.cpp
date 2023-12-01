#include <bits/stdc++.h>

static constexpr std::string_view NUMBERS = "0123456789";
static constexpr std::string_view LETTERS[] = {
    "zero", "one", "two", "three", "four",
    "five" ,"six", "seven", "eight", "nine"
};

struct Digit {
    std::string::size_type index;
    int value;

    static std::optional<Digit> first_number(const std::string& str) {
        auto index = str.find_first_of(NUMBERS);

        if (index != str.npos) {
            Digit digit = { index, str[index] - '0' };
            return std::make_optional(digit);
        }

        return { };
    }

    static std::optional<Digit> first_letter(const std::string& str) {
        std::optional<Digit> first { };

        for (auto n = 0; n < 10; n++) {
            auto index = str.find(LETTERS[n]);
            Digit current = { index, n };

            if (index != str.npos && (!first || first->follows(current)))
                first = current;
        }

        return first;
    }

    static std::optional<Digit> last_number(const std::string& str) {
        auto index = str.find_last_of(NUMBERS);

        if (index != str.npos) {
            Digit digit = { index, str[index] - '0' };
            return std::make_optional(digit);
        }

        return { };
    }

    static std::optional<Digit> last_letter(const std::string& str) {
        std::optional<Digit> last { };

        for (auto n = 0; n < 10; n++) {
            auto index = str.rfind(LETTERS[n]);
            Digit current = { index, n };

            if (index != str.npos && (!last || last->precedes(current)))
                last = current;
        }

        return last;
    }

    bool precedes(const Digit& other) {
        return index < other.index;
    }

    bool follows(const Digit& other) {
        return index > other.index;
    }
};

int main() {
    std::ifstream input { "./day/1/input.txt" };

    if (!input) {
        std::cout << "Error opening input.txt" << '\n';
        return EXIT_FAILURE;
    }

    std::size_t sum { 0 };

    for(std::string line; std::getline(input, line);) {
        auto first_number = Digit::first_number(line);
        auto first_letter = Digit::first_letter(line);
        auto last_number = Digit::last_number(line);
        auto last_letter = Digit::last_letter(line);

        if (first_number && first_letter) {
            auto value  = (first_number->precedes(*first_letter))
                ? first_number->value
                : first_letter->value;

            sum += 10 * value;
        } else if (first_number){
            sum += 10 * first_number->value;
        } else if (first_letter){
            sum += 10 * first_letter->value;
        }

        if (last_number && last_letter) {
            auto value  = (last_number->follows(*last_letter))
                ? last_number->value
                : last_letter->value;

            sum += value;
        } else if (last_number){
            sum += last_number->value;
        } else if (last_letter){
            sum += last_letter->value;
        }
    }

    std::cout << sum << '\n';

	return 0;
}
