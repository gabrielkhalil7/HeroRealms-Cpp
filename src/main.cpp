#include <iostream>
#include <string>
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/actionCard.hpp"

void testTaxationCard() {
    std::cout << "\n=== TEST CARTE TAXATION ===" << std::endl;
    
    // Créer un joueur de test
    Player* testPlayer = new Player("TestPlayer");
    Game* testGame = new Game("TestPlayer", "DummyPlayer"); // Game simple pour les tests
    
    // Initialiser le joueur avec des cartes Taxation
    testPlayer->initializeDeck();
    
    std::cout << "\nÉtat initial:" << std::endl;
    std::cout << "Gold: " << testPlayer->getGold() << std::endl;
    testPlayer->showHand();
    
    std::cout << "\n--- Jouer première carte Taxation ---" << std::endl;
    testPlayer->playCard(0, testGame);
    std::cout << "Gold après 1ère carte: " << testPlayer->getGold() << std::endl;
    
    std::cout << "\n--- Jouer deuxième carte Taxation (effet allié activé) ---" << std::endl;
    testPlayer->playCard(0, testGame); // Index 0 car la première a été supprimée
    std::cout << "Gold après 2ème carte: " << testPlayer->getGold() << std::endl;
    
    std::cout << "\n--- Jouer troisième carte Taxation (effet allié toujours actif) ---" << std::endl;
    testPlayer->playCard(0, testGame); // Index 0 car les précédentes ont été supprimées
    std::cout << "Gold après 3ème carte: " << testPlayer->getGold() << std::endl;
    
    std::cout << "\nCartes en jeu: " << testPlayer->getCartesEnJeu().size() << std::endl;
    
    delete testPlayer;
    delete testGame;
    
    std::cout << "=== FIN DU TEST ===" << std::endl;
}

int main() {
    std::cout << "=============================" << std::endl;
    std::cout << "        HERO REALMS         " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << " 1. Commencer la partie      " << std::endl;
    std::cout << " 2. Test carte Taxation      " << std::endl;
    std::cout << " 3. Quitter                  " << std::endl;
    std::cout << "=============================" << std::endl;

    int choice;
    do {
        std::cout << "Entrez votre choix: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string player1Name, player2Name;
            
            std::cout << "\n--- Configuration de la partie ---" << std::endl;
            std::cout << "Nom du joueur 1: ";
            std::cin.ignore();
            std::getline(std::cin, player1Name);
            
            std::cout << "Nom du joueur 2: ";
            std::getline(std::cin, player2Name);
            
            Game game(player1Name, player2Name);
            //game.start();
            
        } else if (choice == 2) {
            testTaxationCard();
        } else if (choice == 3) {
            std::cout << "Au plaisir de vous revoir ! Au revoir !" << std::endl;
        } else {
            std::cout << "Ce choix n'est pas dans la liste de choix." << std::endl;
        }
    } while (choice != 3);

    return 0;
}