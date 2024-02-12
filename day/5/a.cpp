#include <bits/stdc++.h>

struct Entry {
    size_t dst;
    size_t src;
    size_t n;
};

using Map = std::vector<Entry>;

struct Input {
    std::vector<size_t> seeds;
    std::vector<Map> maps;
};

Input parse(std::ifstream& file) {
    std::string line;

    std::getline(file, line);
    line.erase(0, 7);

    std::vector<size_t> seeds;
    std::stringstream first_line(line);

    for (size_t seed; first_line >> seed;)
        seeds.push_back(seed);

    // Read the second line (empty).
    std::getline(file, line);

    std::vector<Map> maps;

    while (!file.eof()) {
        // Read the map name
        std::getline(file, line);

        Map map;

        for (size_t dst, src, n; std::getline(file, line) && !line.empty();) {
            std::stringstream(line) >> dst >> src >>n;
            map.push_back({ dst, src, n});
        }

        maps.push_back(map);
    }

    return { seeds, maps };
}

int main() {
    std::ifstream file { "day/5/input.txt" };

    if (!file) {
        std::cout << "Error opening input.txt" << '\n';
        return EXIT_FAILURE;
    }

    auto input = parse(file);
    size_t min = std::numeric_limits<size_t>::max();

    for (auto pivot: input.seeds) {
        for (auto map : input.maps) {
            for (auto entry : map)  {
                if (entry.src <= pivot && pivot <= entry.src + entry.n) {
                    pivot = entry.dst + pivot - entry.src;
                    break;
                }
            }
        }

        min = std::min(min, pivot);
    }

    std::cout << min << '\n';

	return 0;
}
