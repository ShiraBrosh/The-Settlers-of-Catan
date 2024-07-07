/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/
#ifndef KATAN_HPP
#define KATAN_HPP

#include "Board.hpp"
#include <vector>
#include <unordered_map> 

class Board; // Forward declaration of the internal class to use in the interface

class Player; // Forward declaration of the internal class to use in the interface

class Katan {
private:
    Katan(Player& p1, Player& p2, Player& p3); // Private constructor for creating the game with players and a board
    static Katan* instance; // Static variable to hold the singleton instance of the class

    std::vector<Player*> players; // List of all players in the game
    int currentPlayerIndex; // Index of the current player's turn
    Board* board; // The game board

public:
    // Static function to get the singleton instance of the class
    static Katan& getInstance(Player& p1, Player& p2, Player& p3);

    // Static function to reset the singleton instance of the class
    static void resetInstance();

    // Destructor to free the memory used by the board
    ~Katan();

    // Function to reset the game board
    void resetBoard();

    // Function to choose the starting player
    Player& ChooseStartingPlayer();

    // Function to print the winner of the game
    void printWinner();

    // Function to get the current player
    Player& getCurrentPlayer();

    // Function to get a specific player by name
    Player& getSpecificPlayer(std::string name);

    // Function to get the game board
    Board& getBoard();

    // Function to proceed to the next turn
    void nextTurn();

    // Function to print resources of all players
    void printPlayerResources() const;

    // Function to use a development card for a player
    void useDevelopmentCard(Player* player, const std::string& nameCard);
    
};

#endif // KATAN_HPP
