CC=clang++
FLAGS=-std=c++20 -Wall -O3

# $(file < SESSION) is not supported in macOS (make v3.81)
SESSION=$(shell cat SESSION)

all:
	$(CC) $(FLAGS) day/$(DAY)/$(PART).cpp -o day/$(DAY)/$(PART)
	./day/$(DAY)/$(PART)

init:
ifndef DAY
	$(error DAY is not specified)
endif
	@mkdir -p day/$(DAY)
	@printf "int main() {\n\treturn 0;\n}" > day/$(DAY)/a.cpp
	@printf "int main() {\n\treturn 0;\n}" > day/$(DAY)/b.cpp
	@curl -o day/$(DAY)/input.txt "https://adventofcode.com/2023/day/$(DAY)/input" --cookie "session=$(SESSION)" 
