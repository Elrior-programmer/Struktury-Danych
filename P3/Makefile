CXX      = g++
CXXFLAGS = -std=c++17
INCLUDE = -Iinclude
TARGET = hash_bench
SRC    = src/main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
