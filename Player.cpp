#include "Player.hpp"
#include "Building.hpp"
#include "Board.hpp"    
#include "Settlement.hpp"
#include "Road.hpp"
#include "City.hpp"
#include "DevelopmentCard.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include "KnightCard.hpp"
#include "VictoryPointCard.hpp"
#include "RoadBuildingCard.hpp"
#include "YearOfPlentyCard.hpp"
#include "MonopolyCard.hpp"

#include <algorithm> 
#include <iostream>
#include <cstdlib> // Include for random number generation


Player::Player(std::string name) : name(name), victoryPoints(0), isTurn(false), roadsBuilt(0) {
    // איתחול המשאבים ל-0
    resources[WOOD] = 0;
    resources[BRICK] = 0;
    resources[SHEEP] = 0;
    resources[WHEAT] = 0;
    resources[IRON] = 0;
}

std::string Player::getName() const {
    return name; // מחזיר את שם השחקן
}

const bool Player::getTurn() const  {
    return isTurn;
}

int Player::getCountKnights(){
    return countKnights;
}

int Player::getVictoryPoints() const  {
    return victoryPoints;
}

std::vector<Building*> Player::getBuildings() const {
    return buildings;
}

const std::unordered_map<Resource, int>& Player::getResources() const {
    return resources; // מחזיר את המשאבים של השחקן
}

std::vector<DevelopmentCard*>& Player::getDevelopmentCards() {
    return developmentCards; 
}

void Player::setTurn(bool turn) {
    isTurn = turn;
}

void Player::addCountKnights() {
    countKnights++;
}


void Player::addDevelopmentCard(DevelopmentCard*card){
    developmentCards.push_back(card);
}


void Player::addToVictoryPoints(int victory) {
    victoryPoints += victory;
}

void Player::removeVictoryPoints(int victory) {
    victoryPoints -= victory;
}

int Player::rollDice() {
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int sum = dice1 + dice2;
    std::cout << "rollDice: " << sum << std::endl;
    return sum;
}

void Player::addResource(Resource r, int amount) {
    resources[r] += amount; // Use += to add resources
}

int Player::countDevelopmentCard(std::string nameCard){
    int count=0;
    for (int i=0; i<developmentCards.size(); i++){
        if (developmentCards[i]->getName()== nameCard){
            count++;
        }
    }
    return count;
}

void Player::buildSettlement(int numVertex, Board& board) {
    std::cout << "Attempting to build settlement at vertex " << numVertex << " for player " << getName() << std::endl;
                    
    if (victoryPoints >= 2 &&
        (resources.at(WOOD) < 1 ||
         resources.at(BRICK) < 1 ||
         resources.at(WHEAT) < 1 ||
         resources.at(SHEEP) < 1)) {

        std::cout << "You don't have enough resources to build a settlement." << std::endl;
        return;
    }

    const Vertex& vertex = board.getVertexFromIndex(numVertex);

    if (vertex.getBuilding() != nullptr) {
        std::cout << "Vertex already has a Settlement or City." << std::endl;
        return;
    }

    if (vertex.getNumIndex() == -1) {
        std::cout << "Vertex does not exist." << std::endl;
        return;
    }

    if (vertex.hasAdjacentSettlement(board)) {
        std::cout << "Settlements need a space of two vertices between them." << std::endl;
        return;
    }

    bool f = true;
    if (victoryPoints < 2) {
        f = false;
    }

    Settlement* settlement = new Settlement(this, numVertex);
    if (!settlement->buildSettlement(this, numVertex, board)) {
        delete settlement;
        return;
    }

    buildings.push_back(settlement);
    addToVictoryPoints(1);
    if (f) {
        deductResourcesForSettlement();
    }
}


void Player::buildRoad(int numSource, int numTarget, Board& board) {
    std::cout << "Attempting to build road from vertex " << numSource << " to " << numTarget << " for player " << getName() << std::endl;

    if (victoryPoints > 2 &&
        (resources.at(WOOD) < 1 ||
         resources.at(BRICK) < 1)) {

        std::cout << "You don't have enough resources to build a road." << std::endl;
        return;
    }

    const Path& path = board.getPathFromIndexes(numSource, numTarget);

    //Invalid path
    if (path.getSource() == -1 && path.getTarget() == -1) {
        std::cout << "Path not found between " << numSource << " and " << numTarget << "." << std::endl;
        return;
    }

    if (path.getBuilding() != nullptr || path.hasRoad()) {
        std::cout << "Path is invalid or already has a building." << std::endl;
        return;
    }
  
    Road* road = new Road(this, numSource, numTarget);
    if (!road->buildRoad(this, numSource, numTarget, board)) {
        delete road;
        return;
    }

    buildings.push_back(road);
    roadsBuilt++; // Increase the road count


    // ניכוי משאבים אם נבנו יותר משתי דרכים
    if (roadsBuilt>2) {
        deductResourcesForRoad();
    }
}void Player::buildCity(int vertexIndex, Board& board) {
    std::cout << "Attempting to build city at vertex " << vertexIndex << " for player " << getName() << std::endl;
    
    const Vertex& vertex = board.getVertexFromIndex(vertexIndex);
    if (vertex.getBuilding() == nullptr || vertex.getBuilding()->getType() != SETTLEMENT) {
        std::cout << "No settlement exists at this vertex to upgrade." << std::endl;
        return;
    }
    
    if (resources.at(IRON) < 3 || resources.at(WHEAT) < 2) {
        std::cout << "You don't have enough resources to build a city." << std::endl;
        return;
    }
    
    // יצירת העיר החדשה
    City* city = new City(this, vertexIndex);
    if (!city->upgradeToCity(this, vertexIndex, board)) {
        delete city;
        return;
    }
    
    deductResourcesForCity();
    buildings.push_back(city);
    addToVictoryPoints(1);
    
    std::cout << "City successfully built at vertex " << vertexIndex << std::endl;
}

void Player::buildDevelopmentCard() {
    if (resources.at(SHEEP) < 1 || resources.at(IRON) < 1 || resources.at(WHEAT) < 1){
        std::cout << "You don't have enough resources to buy a Development Card." << std::endl;
        return;
    }
    drawDevelopmentCard(); 
}

void Player::removeBuilding(Building* building) {
    auto it = std::find(buildings.begin(), buildings.end(), building);
    if (it != buildings.end()) {
        buildings.erase(it);
    }
}

bool Player::trade(Player* otherPlayer, Resource offer, Resource request, int offerCount, int requestCount) {
    // Check if this player has enough resources to offer
    if (!hasEnoughResources(offer, offerCount)) {
        std::cout << "Player does not have enough " << Tile::resourceToString(offer) << " to offer." << std::endl;
        return false;
    }
    
    // Check if the other player has the requested resource
    if (!otherPlayer->hasEnoughResources(request, requestCount)) {
        std::cout << "Other player does not have the " << Tile::resourceToString(request) << " resource." << std::endl;
        return false;
    }

    // Deduct resources from this player and add to the other player
    deductResource(offer, offerCount);
    otherPlayer->addResource(offer, offerCount);

    // Deduct resources from the other player and add to this player
    otherPlayer->deductResource(request, requestCount);
    addResource(request, requestCount);

    std::cout << "Trade successful: exchanged " <<offerCount<< " " << Tile::resourceToString(offer) << " for " << requestCount << " " << Tile::resourceToString(request) << std::endl;
    return true;
}

void Player::deductResourcesForRoad() {
    resources[WOOD]--;
    resources[BRICK]--;
}

void Player::deductResourcesForSettlement() {
    resources[WOOD]--;
    resources[BRICK]--;
    resources[SHEEP]--;
    resources[WHEAT]--;
}

void Player::deductResourcesForCity() {
    resources[IRON] -= 3;
    resources[WHEAT] -= 2;
}

void Player::deductResourcesForDevelopmentCard() {
    resources[IRON]--;
    resources[WHEAT]--;
    resources[SHEEP]--;
}

void Player::deductResource(Resource type, int amount) {
    resources[type] -= amount;
    if (resources[type] < 0) {
        resources[type] = 0; // אם יש כמות שלילית של משאבים אין לקלות מכמות
    }
}


void Player::printBuildings() const {
    std::cout << "Buildings for player " << name << ": ";
    for (const auto& building : buildings) {
        std::cout << "Vertex " << building->getVertex() << ", ";
    }
    std::cout << std::endl;
}


void Player::printResources() const {
    std::cout << getName() << "'s resources:" << std::endl;
    const std::unordered_map<Resource, int>& resources = getResources();
    for (const auto& [resource, amount] : resources) {
        std::cout << "  " << Tile::resourceToString(resource) << ": " << amount << std::endl;
    }
}


void Player::drawDevelopmentCard() {
    // אפשרויות לסוגי קלפים
    static const std::vector<std::string> cardTypes = {"Knight", "victory_point", "road_building", "year_of_plenty", "monopoly"};
    
    // בחירה אקראית של סוג קלף
    std::string cardType = cardTypes[rand() % cardTypes.size()];
    DevelopmentCard* card = nullptr;

    // יצירת קלף תואם לפי סוג הקלף הנבחר
    if (cardType == "Knight") {
        card = new KnightCard();
    } else if (cardType == "victory_point") {
        card = new VictoryPointCard();
    } else if (cardType == "road_building") {
        card = new RoadBuildingCard();
    } else if (cardType == "year_of_plenty") {
        card = new YearOfPlentyCard();
    } else if (cardType == "monopoly") {
        card = new MonopolyCard();
    }

    // הוספת הקלף ליד השחקן אם הוא תקין
    if (card) {
        addDevelopmentCard(card);
    }
}

bool Player::hasEnoughResources(Resource type, int amount) const {
    return resources.at(type) >= amount;
}

bool Player::hasWon() const {
    return victoryPoints >= 10;  // Assuming winning condition is 10 victory points
}
