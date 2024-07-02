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
    katan.ChooseStartingPlayer();
    katan.printWinner();
        
    // Player actions
    katan.getCurrentPlayer().buildSettlement(5, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(2, 5, katan.getBoard());

    // Advance turn and roll dice
    katan.nextTurn();

    katan.getCurrentPlayer().buildSettlement(3, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(3, 6, katan.getBoard());

    katan.nextTurn();

    katan.getCurrentPlayer().buildSettlement(1, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(1, 4, katan.getBoard());

    katan.getCurrentPlayer().buildSettlement(13, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(9, 13, katan.getBoard());

    katan.nextTurn();

    katan.getCurrentPlayer().buildSettlement(31, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(31, 25, katan.getBoard());

    katan.nextTurn();

    katan.getCurrentPlayer().buildSettlement(29, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(29, 34, katan.getBoard());
    
    katan.nextTurn();

    katan.getCurrentPlayer().buildSettlement(45, katan.getBoard());
    katan.getCurrentPlayer().buildRoad(45, 40, katan.getBoard());

    katan.nextTurn();
    int rollDice = katan.getCurrentPlayer().rollDice();
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

    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    katan.nextTurn();
    rollDice = katan.getCurrentPlayer().rollDice();
    katan.getBoard().distributeResources(rollDice, p1, p2, p3);

    katan.printPlayerResources();

    return 0;
}


//     try
//     {
//         p3.placeSettelemnt(places, placesNum, board);
//     }
//     catch (const std::exception &e)
//     {
//         cout << e.what() << endl;
//     }
//     places = {"Forest", "Pasture Land"};
//     placesNum = {5, 9};
//     p2.placeSettelemnt(places, placesNum, board);
//     p2.placeRoad(places, placesNum, board);

//     places = {"Mountains", "Pasture Land"};
//     placesNum = {3, 8};
//     p3.placeSettelemnt(places, placesNum, board);
//     p3.placeRoad(places, placesNum, board);
//     places = {"Agricultural Land", "Pasture Land"};
//     placesNum = {3, 9};
//     p3.placeSettelemnt(places, placesNum, board);
//     p3.placeRoad(places, placesNum, board);

//     p1.rollDice();
//     p1.placeRoad({"Forest", "Hills"}, {5, 6}, board);
//     p1.endTurn();

//     p2.rollDice();
//     p2.endTurn();

//     p3.rollDice();
//     p3.endTurn();

//     p1.rollDice();
//     p1.trade(p2, "wood", "brick", 1, 1);
//     p1.endTurn();

//     p2.rollDice();
//     p2.buyDevelopmentCard();
//     p2.endTurn();

//     p1.printPoints();
//     p2.printPoints();
//     p3.printPoints();

//     catan.printWinner();
// }
