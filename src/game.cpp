#include "../include/game.hpp"
#include <iostream>

using namespace std;

Game::Game(const std::string& player1Name, const std::string& player2Name){
    //godmode par defaut a false
    godMode = false;

    // creation des joueurs
    joueur1 = new Player(player1Name);
    joueur2 = new Player(player2Name);

    // creation du marche
    marche = new Market();

    // initialisation des decks de depart
    joueur1->initializeDeck();
    joueur2->initializeDeck();

    // Pioche initiale selon les règles
    // Le premier joueur (joueur1) pioche 3 cartes
    std::cout << "\n--- Pioche initiale ---" << std::endl;
    joueur1->draw(3);
    std::cout << joueur1->getName() << " pioche 3 cartes (premier joueur)." << std::endl;
    
    // Le deuxième joueur pioche 5 cartes
    joueur2->draw(5);
    std::cout << joueur2->getName() << " pioche 5 cartes (deuxième joueur)." << std::endl;

    cout << "=== Partie Hero Realms initialisée ===" << endl;
    cout << joueur1->getName() << " VS " << joueur2->getName() << endl;
    cout << "=======================================" << endl;
}

Game::~Game() {
    delete joueur1;
    delete joueur2;
    delete marche;
}

void Game::start() {
    cout << "=== Début de la partie ===" << endl;
    // Boucle principale de la partie
    Player* currentPlayer = joueur1;
    while (!isFinished()) {
        playTurn(currentPlayer);
        currentPlayer = (currentPlayer == joueur1) ? joueur2 : joueur1;
    }

    cout << "=== Fin de la partie ===" << endl;

    if (joueur1->getHealth() <= 0)
        cout << joueur2->getName() << " remporte la victoire !" << endl;
    else
        cout << joueur1->getName() << " remporte la victoire !" << endl;
}

void Game::playTurn(Player* currentPlayer) {
    cout << "\n--- Tour de " << currentPlayer->getName() << " ---" << endl;

    // afficher la main et le marché
    currentPlayer->showHand();
    marche->display();
}

bool Game::isFinished() const {
    return (joueur1->getHealth() <= 0 || joueur2->getHealth() <= 0);
}

Player* Game::getOpponent(Player* player) const {
    return (player == joueur1) ? joueur2 : joueur1;
}
