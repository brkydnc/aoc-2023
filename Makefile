CC=clang++
FLAGS=-std=c++20 -Wall -O3
SESSION=$(file < SESSION)

all:
	$(CC) $(FLAGS) day/$(DAY)/$(PART)/*.cpp -o day/$(DAY)/$(PART)/main
	./day/$(DAY)/$(PART)/main

init:
ifndef DAY
	$(error DAY is not specified)
endif
	@mkdir -p day/$(DAY)/a day/$(DAY)/b
	@touch day/$(DAY)/a/main.cpp day/$(DAY)/b/main.cpp
	@printf "int main() {\n\treturn 0;\n}" > day/$(DAY)/a/main.cpp
	@printf "int main() {\n\treturn 0;\n}" > day/$(DAY)/b/main.cpp
	@curl -o day/$(DAY)/input.txt "https://adventofcode.com/2023/day/$(DAY)/input" --cookie "session=$(SESSION)" 
