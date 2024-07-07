#Shira Brosh
#211821137
#shira1d2631@gmail.com

CXX=clang++
CXXFLAGS=-std=c++11 -Wall -g
LDFLAGS=-std=c++11 -Wall -g
SRCS = main.cpp Board.cpp Building.cpp Path.cpp Player.cpp Vertex.cpp Katan.cpp Tile.cpp Settlement.cpp Road.cpp City.cpp DevelopmentCard.cpp KnightCard.cpp RoadBuildingCard.cpp MonopolyCard.cpp VictoryPointCard.cpp YearOfPlentyCard.cpp
OBJS = $(SRCS:.cpp=.o)

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f main $(OBJS)