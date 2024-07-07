/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Katan.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map> 

// Static initialization of the singleton instance
Katan* Katan::instance = nullptr;

// Private constructor that initializes the game with players and a board
Katan::Katan(Player& p1, Player& p2, Player& p3) : players({&p1, &p2, &p3}), currentPlayerIndex(0), board(new Board()) {
    srand(time(nullptr)); // Seed the random number generator
    std::cout << "Katan instance created" << std::endl;
}

// Static method to retrieve the singleton instance of the game
Katan& Katan::getInstance(Player& p1, Player& p2, Player& p3) {
    if (!instance) {
        instance = new Katan(p1, p2, p3); // Create the instance if it doesn't exist
    }
    return *instance;
}

Katan::~Katan() {
        delete board;
}

// Method to reset the singleton instance of the game
void Katan::resetInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}


// Method to reset the game board
void Katan::resetBoard() {
    delete board;
    board = new Board();
}

// Regular method to choose the starting player randomly
Player& Katan::ChooseStartingPlayer() {
    if (players.empty()) {
        throw std::runtime_error("No players in the game");
    }
    currentPlayerIndex = rand() % players.size(); // Randomly select starting player
    std::cout << "Starting player: " << players[currentPlayerIndex]->getName() << std::endl;
    return *players[currentPlayerIndex];
}

// Method to retrieve the game board
Board& Katan::getBoard() {
    return *board;
}

// Method to retrieve the current player
Player& Katan::getCurrentPlayer() {
    return *players[currentPlayerIndex];
}

// Method to retrieve a specific player by name
Player& Katan::getSpecificPlayer(std::string name) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getName() == name) {
            return *players[i];
        }
    }
    throw std::runtime_error("Player not found");
}

// Method to advance to the next turn
void Katan::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

// Method to print the winner of the game
void Katan::printWinner() {
    Player* winner = nullptr;
    for (Player* player : players) {
        if (player->getVictoryPoints() >= 10) { // Check if player has enough points to win
            winner = player;
            break;
        }
    }
    if (winner) {
        std::cout << "The winner is: " << winner->getName() << std::endl;
    } else {
        std::cout << "No winner yet." << std::endl;
    }
}

// Method to print resources of all players
void Katan::printPlayerResources() const {
    for (const Player* player : players) {
        player->printResources();
    }
}

// Method to use a development card by a player
void Katan::useDevelopmentCard(Player* player, const std::string& nameCard) {
    if (player->getDevelopmentCards().empty()) {
        std::cerr << "No development cards to use." << std::endl;
        return;
    }

    DevelopmentCard* card = nullptr;
    std::vector<DevelopmentCard*>& devCards = player->getDevelopmentCards();

    for (size_t i = 0; i < devCards.size(); ++i) {
        if (devCards[i]->getName() == nameCard) {
            card = devCards[i];
            devCards.erase(devCards.begin() + i); // Remove card from player's hand after use
            break;
        }
    }

    // Use the development card
    if (card) {
        card->use(player, players);
        delete card; // Delete the card from memory
    } else {
        std::cerr << "Failed to use development card." << std::endl;
    }
}
