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
    //joueur1->initializeDeck();
    //joueur2->initializeDeck();

    cout << "=== Partie Hero Realms initialisée ===" << endl;
    cout << joueur1->getName() << " VS " << joueur2->getName() << endl;
}

Game::~Game() {
    delete joueur1;
    delete joueur2;
    delete marche;
}
/*
void Game::start() {
    cout << "=== Début de la partie ===" << endl;

    Player* currentPlayer = joueur1;
    Player* opponent = joueur2;

    while (!isFinished()) {
        playTurn(currentPlayer);

        // alternance des joueurs
        if (currentPlayer == joueur1) {
            currentPlayer = joueur2;
            opponent = joueur1;
        } else {
            currentPlayer = joueur1;
            opponent = joueur2;
        }
    }

    cout << "=== Fin de la partie ===" << endl;

    if (joueur1->getHealth() <= 0)
        cout << joueur2->getName() << " remporte la victoire !" << endl;
    else
        cout << joueur1->getName() << " remporte la victoire !" << endl;
}

void Game::playTurn(Player* currentPlayer) {
    cout << "\n--- Tour de " << currentPlayer->getName() << " ---" << endl;

    // 🔹 Afficher la main et le marché
    currentPlayer->showHand();
    marche->display();

    cout << "\nActions possibles :" << endl;
    cout << "  [1] Jouer une carte" << endl;
    cout << "  [2] Acheter une carte" << endl;
    cout << "  [3] Finir le tour" << endl;
    cout << "Choix : ";

    int choix;
    cin >> choix;

    switch (choix) {
        case 1:
            currentPlayer->playCards(); // méthode que tu coderas plus tard
            break;
        case 2:
            currentPlayer->buyCard(*marche, godMode); // achat (avec mode dieu si actif)
            break;
        case 3:
        default:
            cout << "Fin du tour de " << currentPlayer->getName() << "." << endl;
            currentPlayer->endTurn();
            break;
    }
}

bool Game::isFinished() const {
    return (joueur1->getHealth() <= 0 || joueur2->getHealth() <= 0);
}
*/