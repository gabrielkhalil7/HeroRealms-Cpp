#include <iostream>
#include <string>
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/actionCard.hpp"

int main() {
    std::cout << "=============================" << std::endl;
    std::cout << "        HERO REALMS         " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << " 1. Commencer la partie      " << std::endl;
    std::cout << " 2. Quitter                  " << std::endl;
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
            game.start();
            
        } else if (choice == 2) {
            std::cout << "Au plaisir de vous revoir ! Au revoir !" << std::endl;
        } else {
            std::cout << "Ce choix n'est pas dans la liste de choix." << std::endl;
        }
    } while (choice != 2);

    return 0;
}