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

void testInfluenceCardSacrifice() {
    std::cout << "\n=== TEST CARTE INFLUENCE ET SACRIFICE ===" << std::endl;
    
    // Créer un joueur de test
    Player* testPlayer = new Player("TestPlayer");
    Game* testGame = new Game("TestPlayer", "DummyPlayer");
    
    // Créer une carte Influence pour tester le sacrifice
    ActionCard* influence = new ActionCard("Influence", 0, Faction::NECROS, CardId::INFLUENCE);
    
    // Ajouter la carte à la main puis la jouer
    testPlayer->addGold(0); // Initialiser les ressources
    
    std::cout << "\nÉtat initial:" << std::endl;
    std::cout << "Gold: " << testPlayer->getGold() << std::endl;
    std::cout << "Combat: " << testPlayer->getCombat() << std::endl;
    
    // Simuler que la carte est en jeu
    testPlayer->addCardToPlay(influence);
    std::cout << "Cartes en jeu avant sacrifice: " << testPlayer->getCartesEnJeu().size() << std::endl;
    
    // Jouer l'effet primaire (gain de 3 gold)
    influence->executePrimaryEffect(testPlayer, testGame);
    std::cout << "Gold après effet primaire: " << testPlayer->getGold() << std::endl;
    
    // Sacrifier la carte (gain de 3 combat et retrait du jeu)
    std::cout << "\n--- Sacrifier la carte Influence ---" << std::endl;
    influence->sacrifice(testPlayer, testGame);
    
    std::cout << "\nÉtat final:" << std::endl;
    std::cout << "Gold: " << testPlayer->getGold() << std::endl;
    std::cout << "Combat: " << testPlayer->getCombat() << std::endl;
    std::cout << "Cartes en jeu après sacrifice: " << testPlayer->getCartesEnJeu().size() << std::endl;
    
    delete testPlayer;
    delete testGame;
    
    std::cout << "=== FIN DU TEST SACRIFICE ===" << std::endl;
}

int main() {
    std::cout << "=============================" << std::endl;
    std::cout << "        HERO REALMS         " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << " 1. Commencer la partie      " << std::endl;
    std::cout << " 2. Test carte Taxation      " << std::endl;
    std::cout << " 3. Test carte Influence     " << std::endl;
    std::cout << " 4. Quitter                  " << std::endl;
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
            testInfluenceCardSacrifice();
        } else if (choice == 4) {
            std::cout << "Au plaisir de vous revoir ! Au revoir !" << std::endl;
        } else {
            std::cout << "Ce choix n'est pas dans la liste de choix." << std::endl;
        }
    } while (choice != 4);

    return 0;
}