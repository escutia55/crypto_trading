CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC = main.cpp OrderBook.cpp MerkelMain.cpp OrderBookEntry.cpp CSVReader.cpp Wallet.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	del /Q main.o OrderBook.o OrderBookEntry.o MerkelMain.o CSVReader.o  Wallet.o program.exe 2>nul || exit 0