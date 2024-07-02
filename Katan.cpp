#include "Katan.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map> 


// איתחול האינסטנס הסטטי
Katan* Katan::instance = nullptr;

// קונסטרקטור פרטי שמקבל את השחקנים ואיתחול הפרמטרים הפרטיים
Katan::Katan(Player& p1, Player& p2, Player& p3) : players({&p1, &p2, &p3}), currentPlayerIndex(0), board(new Board()) {
    srand(time(nullptr));
    std::cout << "Katan instance created" << std::endl;
}

// פונקציה סטטית לקבלת המופע היחיד של המחלקה
Katan& Katan::getInstance(Player& p1, Player& p2, Player& p3) {
    if (!instance) {
        instance = new Katan(p1, p2, p3); // יצירת האיבר היחיד אם עוד לא קיים
    }
    return *instance;
}

// פונקציות רגילות לפעולה של המחלקה
Player& Katan::ChooseStartingPlayer() {
    if (players.empty()) {
        throw std::runtime_error("No players in the game");
    }
    currentPlayerIndex = rand() % players.size();
    std::cout << "Starting player: " << players[currentPlayerIndex]->getName() << std::endl;
    return *players[currentPlayerIndex];
}

Board& Katan::getBoard() {
    return *board;
}

Player& Katan::getCurrentPlayer() {
    return *players[currentPlayerIndex];
}

Player& Katan::getSpetcificPlayer(std::string name){
    for (int i=0; i<players.size(); i++){
        if (players[i]->getName() == name)
                    return *players[i];
    }
    throw std::runtime_error("Player not found");
 
}
    

void Katan::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Katan::printWinner() {
    Player* winner = nullptr;
    for (Player* player : players) {
        if (player->getVictoryPoints() >= 10) {
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


void Katan::printPlayerResources() const {
    for (const Player* player : players) {
        player->printResources();
    }
}

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
            devCards.erase(devCards.begin() + i); // הסרת הקלף מהרשימה לאחר השימוש
            break;
        }
    }

    // שימוש בקלף
    if (card) {
        card->use(player, players);
        delete card; // מחיקת הקלף מהזיכרון
    } else {
        std::cerr << "Failed to use development card." << std::endl;
    }
}
