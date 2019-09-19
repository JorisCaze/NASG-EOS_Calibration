.SUFFIXES:

# Declarations
EXEC = exe
CXX = g++
CXXFLAGS = -Wall -Wextra

dirs = $(shell find . -type d)
SRC = $(foreach dir,$(dirs),$(wildcard $(dir)/*.cpp))
OBJ = $(SRC:.cpp=.o)
OUT = res/*.txt

all: $(OBJ)
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS)

%o: %cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

depend:
		makedepend $(SRC)

clean:
	rm -rf $(OBJ) 

mrproper:
	rm -rf $(EXEC) 

resClean:
	rm -rf $(OUT)