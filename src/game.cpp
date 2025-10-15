#include "../include/game.hpp"
#include "../include/championCard.hpp"
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

    std::cout << "=============================" << std::endl;
    std::cout << "        HERO REALMS         " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << " 1. Commencer la partie      " << std::endl;
    std::cout << " 2. Quitter                  " << std::endl;
    std::cout << "=============================" << std::endl;
}

void Game::playTurn(Player* currentPlayer) {
    cout << "\n--- Tour de " << currentPlayer->getName() << " ---" << endl;
    cout << "Santé: " << currentPlayer->getHealth() << " | Or: " << currentPlayer->getGold() 
         << " | Combat: " << currentPlayer->getCombat() << endl;

    bool turnFinished = false;
    
    while (!turnFinished) {
        // Afficher la main et le marché
        cout << "\n=== État actuel ===" << endl;
        currentPlayer->showHand();
        marche->display();
        
        // Afficher les champions en jeu des deux joueurs
        cout << "\n=== Champions en jeu ===" << endl;
        cout << currentPlayer->getName() << " : ";
        if (currentPlayer->getChampionsEnJeu().empty()) {
            cout << "Aucun champion" << endl;
        } else {
            cout << endl;
            for (size_t i = 0; i < currentPlayer->getChampionsEnJeu().size(); i++) {
                cout << "  " << (i+1) << ". " << currentPlayer->getChampionsEnJeu()[i]->getName();
                if (currentPlayer->getChampionsEnJeu()[i]->getActivated()) {
                    cout << " (Activé)";
                }
                if (currentPlayer->getChampionsEnJeu()[i]->getGuarding()) {
                    cout << " (Garde)";
                }
                cout << endl;
            }
        }
        
        Player* opponent = getOpponent(currentPlayer);
        cout << opponent->getName() << " : ";
        if (opponent->getChampionsEnJeu().empty()) {
            cout << "Aucun champion" << endl;
        } else {
            cout << endl;
            for (size_t i = 0; i < opponent->getChampionsEnJeu().size(); i++) {
                cout << "  " << (i+1) << ". " << opponent->getChampionsEnJeu()[i]->getName();
                if (opponent->getChampionsEnJeu()[i]->getActivated()) {
                    cout << " (Activé)";
                }
                if (opponent->getChampionsEnJeu()[i]->getGuarding()) {
                    cout << " (Garde)";
                }
                cout << endl;
            }
        }
        
        // Menu d'actions
        cout << "\n=== Actions disponibles ===" << endl;
        cout << "1. Jouer une carte de votre main" << endl;
        cout << "2. Lire la description d'une carte" << endl;
        cout << "3. Acheter une carte du marché" << endl;
        cout << "4. Attaquer l'adversaire ou ses champions" << endl;
        cout << "5. Finir le tour" << endl;
        
        int choice;
        do {
            cout << "Votre choix (1-5): ";
            cin >> choice;
        } while (choice < 1 || choice > 5);
        
        switch (choice) {
            case 1:
                playCardFromHand(currentPlayer);
                break;
            case 2:
                readCardDescription(currentPlayer);
                break;
            case 3:
                buyCardFromMarket(currentPlayer);
                break;
            case 4:
                attackTarget(currentPlayer);
                break;
            case 5:
                turnFinished = true;
                break;
        }
    }
    
    // Fin du tou
    cout << "\n--- Fin du tour de " << currentPlayer->getName() << " ---" << endl;
    currentPlayer->endTurn(); // Remet Or et Combat a 0, defausse les cartes en jeu, pioche 5 cartes
}

bool Game::isFinished() const {
    return (joueur1->getHealth() <= 0 || joueur2->getHealth() <= 0);
}

Player* Game::getOpponent(Player* player) const {
    return (player == joueur1) ? joueur2 : joueur1;
}

void Game::playCardFromHand(Player* currentPlayer) {
    if (currentPlayer->getHand().empty()) {
        cout << "Votre main est vide." << endl;
        return;
    }
    
    cout << "Choisissez une carte à jouer :" << endl;
    for (size_t i = 0; i < currentPlayer->getHand().size(); i++) {
        cout << (i + 1) << ". " << currentPlayer->getHand()[i]->getName() << endl;
    }
    
    int choice;
    do {
        cout << "Votre choix (1-" << currentPlayer->getHand().size() << "): ";
        cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(currentPlayer->getHand().size()));
    
    currentPlayer->playCard(choice - 1, this); // playCard attend un index basé sur 0
}

void Game::readCardDescription(Player* currentPlayer) {
    cout << "Lire la description de quelle carte ?" << endl;
    cout << "1. Carte de votre main" << endl;
    cout << "2. Carte du marché" << endl;
    
    int choice;
    do {
        cout << "Votre choix (1-2): ";
        cin >> choice;
    } while (choice < 1 || choice > 2);
    
    if (choice == 1) {
        // Lire carte de la main
        if (currentPlayer->getHand().empty()) {
            cout << "Votre main est vide." << endl;
            return;
        }
        
        cout << "Choisissez une carte de votre main :" << endl;
        for (size_t i = 0; i < currentPlayer->getHand().size(); i++) {
            cout << (i + 1) << ". " << currentPlayer->getHand()[i]->getName() << endl;
        }
        
        int cardChoice;
        do {
            cout << "Votre choix (1-" << currentPlayer->getHand().size() << "): ";
            cin >> cardChoice;
        } while (cardChoice < 1 || cardChoice > static_cast<int>(currentPlayer->getHand().size()));
        
        Card* selectedCard = currentPlayer->getHand()[cardChoice - 1];
        cout << "\n=== " << selectedCard->getName() << " ===" << endl;
        cout << "Coût: " << selectedCard->getCost() << " Or" << endl;
        cout << "Description: " << selectedCard->getDescription() << endl;
        
    } else {
        // Lire carte du marché - afficher toutes les descriptions
        marche->display();
        cout << "\nEntrez le numéro de la carte pour voir sa description (1-6): ";
        int cardChoice;
        cin >> cardChoice;
        
        if (cardChoice >= 1 && cardChoice <= 6) {
            if (cardChoice <= 5) {
                // Cartes du marché principal (1-5)
                Card* card = marche->getCard(cardChoice - 1);
                if (card != nullptr) {
                    cout << "\n=== " << card->getName() << " ===" << endl;
                    cout << "Coût: " << card->getCost() << " Or" << endl;
                    cout << "Description: " << card->getDescription() << endl;
                } else {
                    cout << "Cette position du marché est vide." << endl;
                }
            } else {
                // Gemme de feu (option 6)
                cout << "\n=== Rubis (Gemme de Feu) ===" << endl;
                cout << "Coût: 2 Or" << endl;
                cout << "Description: Gagnez 1 Or." << endl;
            }
        } else {
            cout << "Choix invalide." << endl;
        }
    }
}

void Game::buyCardFromMarket(Player* currentPlayer) {
    currentPlayer->buyCard(*marche, godMode);
}

void Game::attackTarget(Player* currentPlayer) {
    if (currentPlayer->getCombat() <= 0) {
        cout << "Vous n'avez pas de Combat disponible pour attaquer." << endl;
        return;
    }
    
    Player* opponent = getOpponent(currentPlayer);
    
    // Vérifier s'il y a des champions avec Garde
    std::vector<ChampionCard*> targetableChampions = opponent->getTargetableChampions();
    
    cout << "Combat disponible: " << currentPlayer->getCombat() << endl;
    cout << "Choisissez votre cible :" << endl;
    
    int optionCount = 1;
    
    // Si pas de champions avec Garde, on peut attaquer le joueur
    if (targetableChampions.empty() || !opponent->hasGuardingChampions()) {
        cout << optionCount << ". " << opponent->getName() << " (Santé: " << opponent->getHealth() << ")" << endl;
        optionCount++;
    }
    
    // Afficher les champions ciblables
    for (size_t i = 0; i < targetableChampions.size(); i++) {
        cout << optionCount + i << ". Champion " << targetableChampions[i]->getName();
        if (targetableChampions[i]->getGuarding()) {
            cout << " (Garde)";
        }
        cout << endl;
    }
    
    if (optionCount == 1 && targetableChampions.empty()) {
        cout << "Aucune cible disponible." << endl;
        return;
    }
    
    int choice;
    do {
        cout << "Votre choix (1-" << (optionCount + targetableChampions.size() - 1) << "): ";
        cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(optionCount + targetableChampions.size() - 1));
    
    // Demander combien de combat utiliser
    int combatToUse;
    do {
        cout << "Combien de Combat voulez-vous utiliser ? (1-" << currentPlayer->getCombat() << "): ";
        cin >> combatToUse;
    } while (combatToUse < 1 || combatToUse > currentPlayer->getCombat());
    
    currentPlayer->useCombat(combatToUse);
    
    if (choice == 1 && (targetableChampions.empty() || !opponent->hasGuardingChampions())) {
        // Attaquer le joueur directement
        opponent->takeDamage(combatToUse);
        cout << currentPlayer->getName() << " inflige " << combatToUse << " dégâts à " << opponent->getName() << " !" << endl;
        cout << opponent->getName() << " a maintenant " << opponent->getHealth() << " points de santé." << endl;
    } else {
        // Attaquer un champion
        int championIndex = (targetableChampions.empty() || !opponent->hasGuardingChampions()) ? choice - 2 : choice - 1;
        ChampionCard* targetChampion = targetableChampions[championIndex];
        
        opponent->stunChampion(targetChampion);
        cout << currentPlayer->getName() << " assomme le champion " << targetChampion->getName() << " de " << opponent->getName() << " !" << endl;
    }
}
