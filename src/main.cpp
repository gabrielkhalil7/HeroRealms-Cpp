#include <iostream>
#include <string>
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/actionCard.hpp"
#include "../include/display.hpp"

int main() {
    Display::clearScreen();
    
    while (true) {
        Display::printTitle();
        
        std::cout << Display::CYAN << "┌──────────────────────────────────────────────────────┐" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "│" << Display::WHITE << "                    MENU PRINCIPAL                    " << Display::CYAN << "│" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "├──────────────────────────────────────────────────────┤" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "│ " << Display::GREEN << "[1] 🎮 Commencer une nouvelle partie                 " << Display::CYAN << "│" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "│ " << Display::RED << "[2] 🚪 Quitter le jeu                                " << Display::CYAN << "│" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "└──────────────────────────────────────────────────────┘" << Display::RESET << std::endl;

        std::cout << Display::YELLOW << Display::BOLD << "🎯 Entrez votre choix: " << Display::RESET;
        int choice = Game::getSafeInput(1, 2);

        if (choice == 1) {
            std::string player1Name, player2Name;
            
            Display::clearScreen();
            Display::printSeparator("🎮 CONFIGURATION DE LA PARTIE 🎮", "=", 60);
            
            std::cout << Display::GREEN << "👤 Nom du joueur 1: " << Display::RESET;
            std::cin.ignore();
            std::getline(std::cin, player1Name);
            
            std::cout << Display::BLUE << "👤 Nom du joueur 2: " << Display::RESET;
            std::getline(std::cin, player2Name);
            
            Game game(player1Name, player2Name);
            game.start();
            
            Display::clearScreen();
            
        } else if (choice == 2) {
            Display::clearScreen();
            std::cout << Display::YELLOW << Display::BOLD << "🌟 Merci d'avoir joué à Hero Realms ! 🌟" << Display::RESET << std::endl;
            std::cout << Display::GREEN << "Au plaisir de vous revoir ! 👋" << Display::RESET << std::endl;
            break;
        }
    }

    return 0;
}