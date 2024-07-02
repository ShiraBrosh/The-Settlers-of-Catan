#include <iostream>
#include <cassert>
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include "KnightCard.hpp"
#include "RoadBuildingCard.hpp"
#include "MonopolyCard.hpp"
#include "VictoryPointCard.hpp"
#include "YearOfPlentyCard.hpp"
#include "Katan.hpp" // Assuming this is where Katan::getInstance() is defined

void testPlayerInitialization() {
    Player player("Alice");
    assert(player.getName() == "Alice");
    assert(player.getVictoryPoints() == 0);
    
    // Checking that all resources are initialized to 0
    const auto& resources = player.getResources();
    assert(resources.at(Resource::WOOD) == 0);
    assert(resources.at(Resource::BRICK) == 0);
    assert(resources.at(Resource::SHEEP) == 0);
    assert(resources.at(Resource::WHEAT) == 0);
    assert(resources.at(Resource::IRON) == 0);
    
    assert(player.getDevelopmentCards().empty());
}

void testPlayerAddResources() {
    Player player("Bob");
    player.addResource(Resource::WOOD, 5);
    player.addResource(Resource::BRICK, 3);
    const auto& resources = player.getResources();
    assert(resources.at(Resource::WOOD) == 5);
    assert(resources.at(Resource::BRICK) == 3);
    assert(resources.at(Resource::SHEEP) == 0);
    assert(resources.at(Resource::WHEAT) == 0);
    assert(resources.at(Resource::IRON) == 0);
}

void testPlayerAddDevelopmentCard() {
    Player player("Carol");
    player.drawDevelopmentCard();
    player.drawDevelopmentCard();
    auto& devCards = player.getDevelopmentCards();
    assert(devCards.size() == 2);
    std::cout << "the type of the first devCard is: " << devCards[0]->getName() << std::endl;
    std::cout << "the type of the second devCard is: " << devCards[1]->getName() << std::endl;

    DevelopmentCard* card1 = new KnightCard();
    DevelopmentCard* card2 = new RoadBuildingCard();
    player.addDevelopmentCard(card1);
    player.addDevelopmentCard(card2);
    devCards = player.getDevelopmentCards();
    assert(devCards.size() == 4);

    // Ensure correct types of cards
    assert(dynamic_cast<KnightCard*>(devCards[2]) != nullptr);
    assert(dynamic_cast<RoadBuildingCard*>(devCards[3]) != nullptr);
}

void testDevelopmentCardUse() {
    Player player1("David");
    Player player2("Emma");
    Player player3("Ori");

    Katan& katan = Katan::getInstance(player1, player2, player3);
    std::vector<Player*> allPlayers = { &player1, &player2, &player3 };

    // MonopolyCard
    DevelopmentCard* card = new MonopolyCard();
    player1.addDevelopmentCard(card);

    player1.addResource(Resource::WOOD, 5);
    player2.addResource(Resource::BRICK, 4);
    player2.addResource(Resource::IRON, 3);
    player2.addResource(Resource::SHEEP, 3);
    player2.addResource(Resource::WHEAT, 3);

    player3.addResource(Resource::BRICK, 3);
    player3.addResource(Resource::IRON, 2);
    player3.addResource(Resource::SHEEP, 1);
    player3.addResource(Resource::WHEAT, 1);

    katan.useDevelopmentCard(&player1, "Monopoly");

    assert(player1.getResources().at(Resource::IRON) == 5);
    assert(player2.getResources().at(Resource::IRON) == 0);
    assert(player3.getResources().at(Resource::IRON) == 0);

    // YearOfPlentyCard
    DevelopmentCard* card2 = new YearOfPlentyCard();
    player2.addDevelopmentCard(card2);
    katan.useDevelopmentCard(&player2, "YearOfPlenty");

    assert(player2.getResources().at(Resource::WOOD) == 1);
    assert(player2.getResources().at(Resource::IRON) == 1);

    // VictoryPointCard
    DevelopmentCard* card3 = new VictoryPointCard();
    player2.addDevelopmentCard(card3);

    assert(player2.getVictoryPoints() == 0);
    katan.useDevelopmentCard(&player2, "VictoryPoint");
    assert(player2.getVictoryPoints() == 1);

    // KnightCard
    DevelopmentCard* card4 = new KnightCard();
    player1.addDevelopmentCard(card4);
    katan.useDevelopmentCard(&player1, "Knight");

    assert(player1.getVictoryPoints() == 0);
    DevelopmentCard* card5 = new KnightCard();
    player1.addDevelopmentCard(card5);
    katan.useDevelopmentCard(&player1, "Knight");

    assert(player1.getVictoryPoints() == 0);
    DevelopmentCard* card6 = new KnightCard();
    player1.addDevelopmentCard(card6);
    katan.useDevelopmentCard(&player1, "Knight");

    assert(player1.getVictoryPoints() == 2);

    // Check that after use the card is erased
    assert(player1.getDevelopmentCards().empty());
    assert(player2.getDevelopmentCards().empty());
    assert(player3.getDevelopmentCards().empty());

    DevelopmentCard* card7 = new RoadBuildingCard();
    player1.addDevelopmentCard(card7);
    katan.useDevelopmentCard(&player1, "RoadBuilding");

    // Assertions to check road building
    assert(!katan.getBoard().hasRoadOnEdge(1, 4)); // Player can only build a road connected to their own settlement or city.
    assert(!katan.getBoard().hasRoadOnEdge(2, 3)); // Path not found between 2 and 3.
}

void testPlayerBuild_Settlement_Roads() {
    Player player1("Emily");
    Player player2("yael");
    Player player3("ketty");

    Katan& katan = Katan::getInstance(player1, player2, player3);
    
    player1.buildSettlement(16, katan.getBoard());
    assert(katan.getBoard().hasSettlementOnVertex(16));
    player1.buildRoad(16, 21, katan.getBoard());
    assert(katan.getBoard().hasRoadOnEdge(16, 21));

    player2.buildSettlement(16, katan.getBoard()); // Place with another settlement

    player1.buildSettlement(19, katan.getBoard());
    assert(katan.getBoard().hasSettlementOnVertex(19));
    player1.buildRoad(19, 14, katan.getBoard());
    assert(katan.getBoard().hasRoadOnEdge(19, 14));

    player1.buildSettlement(24, katan.getBoard()); // Don't have enough resources
    assert(!katan.getBoard().hasSettlementOnVertex(24));

    player1.buildRoad(35, 40, katan.getBoard()); 
    assert(!katan.getBoard().hasRoadOnEdge(35, 40));

    player1.addResource(Resource::WOOD, 2);
    player1.addResource(Resource::BRICK, 2);
    player1.addResource(Resource::WHEAT, 2);
    player1.addResource(Resource::SHEEP, 2);

    player1.buildSettlement(50, katan.getBoard()); // Cannot build a settlement without an adjacent road.
    assert(!katan.getBoard().hasSettlementOnVertex(50));

    player1.buildSettlement(30, katan.getBoard()); // Don't have a space of two vertices between them.
    assert(!katan.getBoard().hasSettlementOnVertex(30));


    assert(player1.getBuildings().size() == 4);
    assert(player2.getBuildings().size() == 0);
    assert(player3.getBuildings().size() == 0);
}


void testPlayerTrading() {
    Player player1("David");
    Player player2("Emma");

    // Initialize players with resources
    player1.addResource(Resource::WOOD, 3);
    player1.addResource(Resource::BRICK, 3);
    player2.addResource(Resource::IRON, 2);
    player2.addResource(Resource::WHEAT, 2);

    // Perform trading between players
    assert(player1.trade(&player2, Resource::WOOD, Resource::IRON, 2, 1));
    assert(player1.trade(&player2, Resource::BRICK, Resource::WHEAT, 2, 2));
    assert(!player2.trade(&player2, Resource::SHEEP, Resource::WHEAT, 2, 2));

    // Check resources after trading
    assert(player1.getResources().at(Resource::WOOD) == 1);
    assert(player1.getResources().at(Resource::BRICK) == 1);
    assert(player2.getResources().at(Resource::IRON) == 1);
    assert(player2.getResources().at(Resource::WHEAT) == 0);

    player1.printResources();
    player2.printResources();
}

void testVictoryConditions() {
    Player player("Alice");
    assert(player.getVictoryPoints() == 0);

    // Simulate gaining victory points
    player.addToVictoryPoints(5);
    assert(player.getVictoryPoints() == 5);

    // Simulate winning conditions
    assert(!player.hasWon());
    player.addToVictoryPoints(5);  // Assuming winning condition is at 10 points
    assert(player.hasWon());
}
void testSettlementBuildingAndResourceCollection() {
    Player player1("David");
    Player player2("Emma");
    Player player3("Ori");

    Katan& katan = Katan::getInstance(player1, player2, player3);
    
    // Build settlements
    player1.buildSettlement(16, katan.getBoard());
    player1.buildRoad(16,21, katan.getBoard());

    player2.buildSettlement(19, katan.getBoard());
    player2.buildRoad(19,24, katan.getBoard());

    player3.buildSettlement(22, katan.getBoard());
    player3.buildRoad(22,28, katan.getBoard());


    player1.buildSettlement(50, katan.getBoard());
    player1.buildRoad(50,53, katan.getBoard());

    player2.buildSettlement(1, katan.getBoard());
    player2.buildRoad(1,4, katan.getBoard());

    player3.buildSettlement(9, katan.getBoard());
    player3.buildRoad(9,13, katan.getBoard());


    // Print initial resources
    std::cout << "Initial resources:" << std::endl;
    player1.printResources();
    player2.printResources();
    player3.printResources();

    // Roll the dice
    int diceRoll = 6; // Example dice roll
    katan.getBoard().distributeResources(diceRoll, player1, player2, player3);

    // Print resources after distributing based on dice roll
    std::cout << "\nResources after rolling dice (" << diceRoll << "):" << std::endl;
    player1.printResources();
    player2.printResources();
    player3.printResources();
    assert (player3.getResources().at(Resource::BRICK) == 1);
 
    player3.addResource(Resource::BRICK, 2);
    player3.addResource(Resource::WOOD, 3);
    player3.addResource(Resource::SHEEP, 1);
    player3.addResource(Resource::WHEAT, 1);

    // check the resources after bought settlement
    player3.buildRoad(5,9, katan.getBoard());
    player3.buildRoad(5,2, katan.getBoard());
    player3.buildSettlement(2, katan.getBoard());
    assert (player3.getResources().at(Resource::BRICK) == 0);
    assert (player3.getResources().at(Resource::BRICK) == 0);
    assert (player3.getResources().at(Resource::BRICK) == 0);
    assert (player3.getResources().at(Resource::BRICK) == 0);

}


void testPlayerBuildCity() {
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    Katan& katan = Katan::getInstance(player1, player2, player3);
            std::cout << "new" << std::endl;

    player1.addResource(Resource::WHEAT, 2);
    player1.addResource(Resource::IRON, 3);

    // Build initial settlement and road to upgrade later
    player1.buildSettlement(16, katan.getBoard());
    player1.buildRoad(16, 11, katan.getBoard());

    player1.buildSettlement(26, katan.getBoard());
    player1.buildRoad(26, 21, katan.getBoard());
    
    // Attempt to build city at vertex without a settlement
    // player1.buildCity(19, katan.getBoard());
    // assert(!katan.getBoard().hasCityOnVertex(19));
    
 std::cout << "Building type at vertex 16 before upgrade: " << 
    (katan.getBoard().getVertexFromIndex(16).getBuilding() ? 
    katan.getBoard().getVertexFromIndex(16).getBuilding()->getBuildingTypeName() : "None") << std::endl;

player1.buildCity(16, katan.getBoard());

std::cout << "Building type at vertex 16 after upgrade: " << 
    (katan.getBoard().getVertexFromIndex(16).getBuilding() ? 
    katan.getBoard().getVertexFromIndex(16).getBuilding()->getBuildingTypeName() : "None") << std::endl;

    assert(katan.getBoard().hasCityOnVertex(16));

    // Attempt to build city without enough resources
    player1.buildCity(26, katan.getBoard());
    assert(!katan.getBoard().hasCityOnVertex(26));
    
    const auto& resources = player1.getResources();
    assert(resources.at(Resource::WHEAT) == 0); // after building
    assert(resources.at(Resource::IRON) == 0);  
}


void runTests() {
    testPlayerInitialization();
    testPlayerAddResources();
    testPlayerAddDevelopmentCard();
    testDevelopmentCardUse();
    testPlayerBuild_Settlement_Roads();
    testPlayerTrading();
    testVictoryConditions();
    testSettlementBuildingAndResourceCollection();
    testPlayerBuildCity();
    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
