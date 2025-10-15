#include "../include/game.hpp"
#include "../include/championCard.hpp"
#include "../include/display.hpp"
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
    Display::clearScreen();
    Display::printTitle();
    
    cout << Display::GREEN << Display::BOLD << "🎯 Début de la partie 🎯" << Display::RESET << endl;
    Display::printSeparator();
    
    // Boucle principale de la partie
    Player* currentPlayer = joueur1;
    while (!isFinished()) {
        playTurn(currentPlayer);
        currentPlayer = (currentPlayer == joueur1) ? joueur2 : joueur1;
    }

    Display::clearScreen();
    Display::printTitle();
    cout << Display::RED << Display::BOLD << "🏆 FIN DE LA PARTIE 🏆" << Display::RESET << endl;
    Display::printSeparator();

    if (joueur1->getHealth() <= 0)
        cout << Display::GREEN << Display::BOLD << "🎉 " << joueur2->getName() << " remporte la victoire ! 🎉" << Display::RESET << endl;
    else
        cout << Display::GREEN << Display::BOLD << "🎉 " << joueur1->getName() << " remporte la victoire ! 🎉" << Display::RESET << endl;

    Display::printSeparator();
    std::cout << Display::CYAN << "Retour au menu principal..." << Display::RESET << std::endl;
}

void Game::playTurn(Player* currentPlayer) {
    Display::clearScreen();
    Display::printGameBoard();
    
        Display::printSeparator("🎮 TOUR DE " + currentPlayer->getName() + " 🎮", "=", 60);    bool turnFinished = false;
    
    while (!turnFinished) {
        // Afficher la main et le marché
        currentPlayer->showHand();
        marche->display();
        
        // Afficher les champions en jeu des deux joueurs
        Display::printSeparator("⚔️  CHAMPIONS EN JEU ⚔️", "-", 60);
        
        // Champions du joueur actuel
        cout << Display::GREEN << Display::BOLD << "🛡️  " << currentPlayer->getName() << ": " << Display::RESET;
        if (currentPlayer->getChampionsEnJeu().empty()) {
            cout << Display::WHITE << "Aucun champion" << Display::RESET << endl;
        } else {
            cout << endl;
            for (size_t i = 0; i < currentPlayer->getChampionsEnJeu().size(); i++) {
                cout << Display::GREEN << "  ⚔️  " << (i+1) << ". " << Display::BOLD 
                     << currentPlayer->getChampionsEnJeu()[i]->getName() << Display::RESET;
                if (currentPlayer->getChampionsEnJeu()[i]->getActivated()) {
                    cout << Display::YELLOW << " (Activé)" << Display::RESET;
                }
                if (currentPlayer->getChampionsEnJeu()[i]->getGuarding()) {
                    cout << Display::BLUE << " (🛡️ Garde)" << Display::RESET;
                }
                cout << endl;
            }
        }
        
        // Champions de l'adversaire
        Player* opponent = getOpponent(currentPlayer);
        cout << Display::RED << Display::BOLD << "💀 " << opponent->getName() << ": " << Display::RESET;
        if (opponent->getChampionsEnJeu().empty()) {
            cout << Display::WHITE << "Aucun champion" << Display::RESET << endl;
        } else {
            cout << endl;
            for (size_t i = 0; i < opponent->getChampionsEnJeu().size(); i++) {
                cout << Display::RED << "  ⚔️  " << (i+1) << ". " << Display::BOLD 
                     << opponent->getChampionsEnJeu()[i]->getName() << Display::RESET;
                if (opponent->getChampionsEnJeu()[i]->getActivated()) {
                    cout << Display::YELLOW << " (Activé)" << Display::RESET;
                }
                if (opponent->getChampionsEnJeu()[i]->getGuarding()) {
                    cout << Display::BLUE << " (🛡️ Garde)" << Display::RESET;
                }
                cout << endl;
            }
        }
        
        // Menu d'actions amélioré
        cout << endl;
        Display::printSeparator("🎯 ACTIONS DISPONIBLES 🎯", "-", 60);
        cout << Display::CYAN << "┌──────────────────────────────────────────────────────────┐" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[1] 🃏 Jouer une carte de votre main                  " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[2] 📖 Lire la description d'une carte                " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[3] 🏪 Acheter une carte du marché                   " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[4] ⚔️  Attaquer l'adversaire ou ses champions        " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[5] ⏭️  Finir le tour                                 " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "└──────────────────────────────────────────────────────────┘" << Display::RESET << endl;
        
        int choice;
        do {
            cout << Display::YELLOW << Display::BOLD << "🎯 Votre choix (1-5): " << Display::RESET;
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
        
        if (!turnFinished) {
            cout << Display::WHITE << "\nAppuyez sur Entrée pour continuer..." << Display::RESET;
            cin.ignore();
            cin.get();
        }
    }
    
    // Fin du tour
    cout << endl;
    Display::printSeparator("⏭️  FIN DU TOUR DE " + currentPlayer->getName() + " ⏭️", "=", 60);
    currentPlayer->endTurn(); // Remet Or et Combat a 0, defausse les cartes en jeu, pioche 5 cartes
    
    cout << Display::WHITE << "Appuyez sur Entrée pour continuer..." << Display::RESET;
    cin.ignore();
    cin.get();
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
