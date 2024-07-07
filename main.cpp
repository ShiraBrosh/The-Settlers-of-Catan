/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Katan.hpp"
#include "Player.hpp"
#include <iostream>

int main() {
    // Initialize players
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    // Initialize game instance (assuming Katan manages the game)
    Katan& katan = Katan::getInstance(p1, p2, p3);

    // Start game actions
    katan.ChooseStartingPlayer(); // Choose the starting player randomly
    katan.printWinner(); // Print the initial winner (none at the start)

    // Player actions for initial setup
    katan.getCurrentPlayer().buildSettlement(5, katan.getBoard()); // Player builds a settlement on vertex 5
    katan.getCurrentPlayer().buildRoad(2, 5, katan.getBoard()); // Player builds a road connecting vertices 2 and 5

    // Advance turn and actions for the second player's turn
    katan.nextTurn(); // Move to the next player's turn

    katan.getCurrentPlayer().buildSettlement(3, katan.getBoard()); // Player builds a settlement on vertex 3
    katan.getCurrentPlayer().buildRoad(3, 6, katan.getBoard()); // Player builds a road connecting vertices 3 and 6

    // Third player's turn actions
    katan.nextTurn(); // Move to the next player's turn

    katan.getCurrentPlayer().buildSettlement(1, katan.getBoard()); // Player builds a settlement on vertex 1
    katan.getCurrentPlayer().buildRoad(1, 4, katan.getBoard()); // Player builds a road connecting vertices 1 and 4

    katan.getCurrentPlayer().buildSettlement(13, katan.getBoard()); // Player builds another settlement on vertex 13
    katan.getCurrentPlayer().buildRoad(9, 13, katan.getBoard()); // Player builds a road connecting vertices 9 and 13

    // Fourth player's turn actions
    katan.nextTurn(); // Move to the next player's turn

    katan.getCurrentPlayer().buildSettlement(31, katan.getBoard()); // Player builds a settlement on vertex 31
    katan.getCurrentPlayer().buildRoad(31, 25, katan.getBoard()); // Player builds a road connecting vertices 31 and 25

    // Fifth player's turn actions
    katan.nextTurn(); // Move to the next player's turn

    katan.getCurrentPlayer().buildSettlement(29, katan.getBoard()); // Player builds a settlement on vertex 29
    katan.getCurrentPlayer().buildRoad(29, 34, katan.getBoard()); // Player builds a road connecting vertices 29 and 34

    // Sixth player's turn actions
    katan.nextTurn(); // Move to the next player's turn

    katan.getCurrentPlayer().buildSettlement(45, katan.getBoard()); // Player builds a settlement on vertex 45
    katan.getCurrentPlayer().buildRoad(45, 40, katan.getBoard()); // Player builds a road connecting vertices 45 and 40

    // Advance to the next turn and simulate resource distribution
    katan.nextTurn(); // Move to the next player's turn
    int rollDice = katan.getCurrentPlayer().rollDice(); // Roll dice to determine resource distribution
    katan.getBoard().distributeResources(rollDice, p1, p2, p3); // Distribute resources based on the dice roll

    // Repeat resource distribution for subsequent turns
    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    // Print each player's resources at the end of the game
    katan.printPlayerResources();

    return 0;
}
