#ifndef KATAN_HPP
#define KATAN_HPP

#include "Board.hpp"
#include <vector>
#include <unordered_map> 

class Board;
class Player;

class Katan {

private:
    // פרטיות המחלקה
    Katan(Player& p1, Player& p2, Player& p3); // קונסטרקטור פרטי
    static Katan* instance; // אינסטנס סטטי של המחלקה

    std::vector<Player*> players;
    int currentPlayerIndex;
    Board* board;

public:
    // פונקציה סטטית לקבלת המופע היחיד של המחלקה
    static Katan& getInstance(Player& p1, Player& p2, Player& p3);

    // פונקציות רגילות של המחלקה
    Player& ChooseStartingPlayer();
    void printWinner();
    Player& getCurrentPlayer();
    Player& getSpetcificPlayer(std::string name);
    Board& getBoard();
    void nextTurn();

    void printPlayerResources() const;
    void useDevelopmentCard(Player* player, const std::string& nameCard);
};

#endif // KATAN_HPP
