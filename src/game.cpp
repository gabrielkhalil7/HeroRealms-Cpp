#include "../include/game.hpp"
#include "../include/championCard.hpp"
#include "../include/actionCard.hpp"
#include "../include/itemCard.hpp"
#include "../include/display.hpp"
#include <iostream>
#include <limits>

using namespace std;

Game::Game(const std::string& player1Name, const std::string& player2Name){
    //godmode par defaut a false
    godMode = false;
    savedHealthJoueur1 = 50;  // Santé par défaut
    savedHealthJoueur2 = 50;  // Santé par défaut

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

// Fonction utilitaire pour une saisie sécurisée d'entiers
int Game::getSafeInput(int min, int max) {
    int input;
    while (true) {
        if (cin >> input) {
            // Entrée valide, vérifier si dans la plage
            if (input >= min && input <= max) {
                // Vider le buffer des caractères restants
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return input;
            } else {
                cout << Display::RED << "❌ Choix invalide ! Veuillez entrer un nombre entre " 
                     << min << " et " << max << "." << Display::RESET << endl;
            }
        } else {
            // Entrée invalide (non-numérique)
            cout << Display::RED << "❌ Entrée invalide ! Veuillez entrer un nombre." << Display::RESET << endl;
            cin.clear(); // Effacer le flag d'erreur
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vider le buffer
        }
        cout << Display::YELLOW << "Réessayez: " << Display::RESET;
    }
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
                     << currentPlayer->getChampionsEnJeu()[i]->getName() << Display::RESET
                     << Display::WHITE << " [" << Display::RED << Display::BOLD 
                     << currentPlayer->getChampionsEnJeu()[i]->getDefense() << " PV" 
                     << Display::WHITE << "]" << Display::RESET;
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
                     << opponent->getChampionsEnJeu()[i]->getName() << Display::RESET
                     << Display::WHITE << " [" << Display::RED << Display::BOLD 
                     << opponent->getChampionsEnJeu()[i]->getDefense() << " PV" 
                     << Display::WHITE << "]" << Display::RESET;
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
        cout << Display::CYAN << "│ " << Display::WHITE << "[1] 🃏 Jouer une carte de votre main                     " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[2] 📖 Lire la description d'une carte                   " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[3] 🏪 Acheter une carte du marché                       " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[4] ⚔️  Attaquer l'adversaire ou ses champions            " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[5] 💀 Sacrifier une carte                               " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[6] 🛡️  Utiliser une capacité d'un champion en jeu        " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << Display::WHITE << "[7] ⏭️  Finir le tour                                     " << Display::CYAN << "│" << Display::RESET << endl;
        cout << Display::CYAN << "│ " << (godMode ? Display::RED : Display::MAGENTA) << "[8] " << (godMode ? "🔮 Désactiver God Mode       " : "🔓 Activer God Mode          ") << "                        " << Display::CYAN << "│" << Display::RESET << endl;
        if (godMode) {
            cout << Display::CYAN << "│ " << Display::YELLOW << "[9] 🌟 Acheter depuis toute la pioche                    " << Display::CYAN << "│" << Display::RESET << endl;
        }
        cout << Display::CYAN << "└──────────────────────────────────────────────────────────┘" << Display::RESET << endl;
        
        int maxChoice = godMode ? 9 : 8;
        cout << Display::YELLOW << Display::BOLD << "🎯 Votre choix (1-" << maxChoice << "): " << Display::RESET;
        int choice = getSafeInput(1, maxChoice);

        
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
                sacrificeCard(currentPlayer);
                break;
            case 6:
                useChampionAbility(currentPlayer);
                break;
            case 7:
                turnFinished = true;
                break;
            case 8:
                toggleGodMode();
                break;
            case 9:
                if (godMode) {
                    buyCardFromFullMarket(currentPlayer);
                }
                break;
        }
        
        if (!turnFinished) {
            cout << Display::WHITE << "\nAppuyez sur Entrée pour continuer..." << Display::RESET;
            cin.get();
        }
    }
    
    // Fin du tour
    cout << endl;
    Display::printSeparator("⏭️  FIN DU TOUR DE " + currentPlayer->getName() + " ⏭️", "=", 60);
    currentPlayer->endTurn(); // Remet Or et Combat a 0, defausse les cartes en jeu, pioche 5 cartes
    
    cout << Display::WHITE << "Appuyez sur Entrée pour continuer..." << Display::RESET;
    cin.get(); // Attendre l'Entrée
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
        Card* card = currentPlayer->getHand()[i];
        std::string factionColor = Display::getFactionColor(card->getFaction());
        
        // Déterminer le type de carte et son icône (sans couleur de type)
        std::string cardTypeIcon = "";
        if (dynamic_cast<ChampionCard*>(card)) {
            cardTypeIcon = "🛡️";
        } else if (dynamic_cast<ActionCard*>(card)) {
            cardTypeIcon = "⚔️";
        } else if (dynamic_cast<ItemCard*>(card)) {
            cardTypeIcon = "💎";
        }
        
        cout << (i + 1) << ". " << factionColor << Display::getFactionSymbol(card->getFaction()) 
             << " " << cardTypeIcon << " " << card->getName() << Display::RESET << endl;
    }
    
    cout << "Votre choix (1-" << currentPlayer->getHand().size() << "): ";
    int choice = getSafeInput(1, static_cast<int>(currentPlayer->getHand().size()));
    
    currentPlayer->playCard(choice - 1, this); // playCard attend un index basé sur 0
}

void Game::readCardDescription(Player* currentPlayer) {
    cout << "Lire la description de quelle carte ?" << endl;
    cout << "1. Carte de votre main" << endl;
    cout << "2. Carte du marché" << endl;
    
    cout << "Votre choix (1-2): ";
    int choice = getSafeInput(1, 2);
    
    if (choice == 1) {
        // Lire carte de la main
        if (currentPlayer->getHand().empty()) {
            cout << "Votre main est vide." << endl;
            return;
        }
        
        cout << "Choisissez une carte de votre main :" << endl;
        for (size_t i = 0; i < currentPlayer->getHand().size(); i++) {
            Card* card = currentPlayer->getHand()[i];
            std::string factionColor = Display::getFactionColor(card->getFaction());
            
            // Déterminer le type de carte et son icône (sans couleur de type)
            std::string cardTypeIcon = "";
            if (dynamic_cast<ChampionCard*>(card)) {
                cardTypeIcon = "🛡️";
            } else if (dynamic_cast<ActionCard*>(card)) {
                cardTypeIcon = "⚔️";
            } else if (dynamic_cast<ItemCard*>(card)) {
                cardTypeIcon = "💎";
            }
            
            cout << (i + 1) << ". " << factionColor << Display::getFactionSymbol(card->getFaction()) 
                 << " " << cardTypeIcon << " " << card->getName() << Display::RESET << endl;
        }
        
        cout << "Votre choix (1-" << currentPlayer->getHand().size() << "): ";
        int cardChoice = getSafeInput(1, static_cast<int>(currentPlayer->getHand().size()));
        
        Card* selectedCard = currentPlayer->getHand()[cardChoice - 1];
        cout << "\n=== " << selectedCard->getName() << " ===" << endl;
        cout << "Coût: " << selectedCard->getCost() << " Or" << endl;
        cout << "Description: " << selectedCard->getDescription() << endl;
        
    } else {
        // Lire carte du marché - afficher toutes les descriptions
        marche->display();
        cout << "\nEntrez le numéro de la carte pour voir sa description (1-6): ";
        int cardChoice = getSafeInput(1, 6);
        
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
    
    cout << "Votre choix (1-" << (optionCount + targetableChampions.size() - 1) << "): ";
    int choice = getSafeInput(1, static_cast<int>(optionCount + targetableChampions.size() - 1));
    
    // Demander combien de combat utiliser
    cout << "Combien de Combat voulez-vous utiliser ? (1-" << currentPlayer->getCombat() << "): ";
    int combatToUse = getSafeInput(1, currentPlayer->getCombat());
    
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
        
        cout << currentPlayer->getName() << " attaque " << targetChampion->getName() << " avec " << combatToUse << " Combat !" << endl;
        cout << targetChampion->getName() << " avait " << targetChampion->getDefense() << " PV." << endl;
        
        // Infliger les dégâts au champion
        targetChampion->takeDamage(combatToUse);
        
        if (targetChampion->getDefense() <= 0) {
            // Champion assommé
            opponent->stunChampion(targetChampion);
            cout << Display::RED << Display::BOLD << "💀 " << targetChampion->getName() << " est assommé et envoyé en défausse !" << Display::RESET << endl;
        } else {
            // Champion survit mais a perdu des PV
            cout << Display::YELLOW << "⚡ " << targetChampion->getName() << " survit avec " << targetChampion->getDefense() << " PV restants." << Display::RESET << endl;
        }
    }
}

void Game::sacrificeCard(Player* currentPlayer) {
    // Vérifier s'il y a des cartes à sacrifier
    bool hasCardsToSacrifice = !currentPlayer->getHand().empty() || 
                               !currentPlayer->getCartesEnJeu().empty() || 
                               !currentPlayer->getChampionsEnJeu().empty();
    
    if (!hasCardsToSacrifice) {
        cout << Display::RED << "Aucune carte disponible pour le sacrifice." << Display::RESET << endl;
        return;
    }
    
    cout << Display::MAGENTA << Display::BOLD << "💀 SACRIFIER UNE CARTE 💀" << Display::RESET << endl;
    cout << Display::CYAN << "Où voulez-vous sacrifier une carte ?" << Display::RESET << endl;
    cout << Display::WHITE << "1. Main (" << currentPlayer->getHand().size() << " cartes)" << Display::RESET << endl;
    cout << Display::WHITE << "2. Cartes en jeu (" << currentPlayer->getCartesEnJeu().size() << " cartes)" << Display::RESET << endl;
    cout << Display::WHITE << "3. Champions en jeu (" << currentPlayer->getChampionsEnJeu().size() << " champions)" << Display::RESET << endl;
    cout << Display::WHITE << "0. Annuler" << Display::RESET << endl;
    
    cout << Display::YELLOW << "Votre choix (0-3): " << Display::RESET;
    int sourceChoice = getSafeInput(0, 3);
    
    if (sourceChoice == 0) {
        cout << Display::WHITE << "Sacrifice annulé." << Display::RESET << endl;
        return;
    }
    
    if (sourceChoice == 1) {
        // Sacrifier depuis la main
        if (currentPlayer->getHand().empty()) {
            cout << Display::RED << "Votre main est vide." << Display::RESET << endl;
            return;
        }
        
        cout << Display::CYAN << "Choisissez une carte de votre main à sacrifier :" << Display::RESET << endl;
        for (size_t i = 0; i < currentPlayer->getHand().size(); i++) {
            cout << Display::WHITE << (i + 1) << ". " << currentPlayer->getHand()[i]->getName() << Display::RESET << endl;
        }
        
        int cardChoice;
        do {
            cout << Display::YELLOW << "Votre choix (1-" << currentPlayer->getHand().size() << "): " << Display::RESET;
            cin >> cardChoice;
        } while (cardChoice < 1 || cardChoice > static_cast<int>(currentPlayer->getHand().size()));
        
        Card* cardToSacrifice = currentPlayer->getHand()[cardChoice - 1];
        cardToSacrifice->sacrifice(currentPlayer, this, false);
        
    } else if (sourceChoice == 2) {
        // Sacrifier depuis les cartes en jeu
        if (currentPlayer->getCartesEnJeu().empty()) {
            cout << Display::RED << "Aucune carte en jeu." << Display::RESET << endl;
            return;
        }
        
        cout << Display::CYAN << "Choisissez une carte en jeu à sacrifier :" << Display::RESET << endl;
        for (size_t i = 0; i < currentPlayer->getCartesEnJeu().size(); i++) {
            cout << Display::WHITE << (i + 1) << ". " << currentPlayer->getCartesEnJeu()[i]->getName() << Display::RESET << endl;
        }
        
        int cardChoice;
        do {
            cout << Display::YELLOW << "Votre choix (1-" << currentPlayer->getCartesEnJeu().size() << "): " << Display::RESET;
            cin >> cardChoice;
        } while (cardChoice < 1 || cardChoice > static_cast<int>(currentPlayer->getCartesEnJeu().size()));
        
        Card* cardToSacrifice = currentPlayer->getCartesEnJeu()[cardChoice - 1];
        cardToSacrifice->sacrifice(currentPlayer, this, false);
        
    } else if (sourceChoice == 3) {
        // Sacrifier un champion en jeu
        if (currentPlayer->getChampionsEnJeu().empty()) {
            cout << Display::RED << "Aucun champion en jeu." << Display::RESET << endl;
            return;
        }
        
        cout << Display::CYAN << "Choisissez un champion à sacrifier :" << Display::RESET << endl;
        for (size_t i = 0; i < currentPlayer->getChampionsEnJeu().size(); i++) {
            cout << Display::WHITE << (i + 1) << ". " << currentPlayer->getChampionsEnJeu()[i]->getName() << Display::RESET << endl;
        }
        
        int championChoice;
        do {
            cout << Display::YELLOW << "Votre choix (1-" << currentPlayer->getChampionsEnJeu().size() << "): " << Display::RESET;
            cin >> championChoice;
        } while (championChoice < 1 || championChoice > static_cast<int>(currentPlayer->getChampionsEnJeu().size()));
        
        ChampionCard* championToSacrifice = currentPlayer->getChampionsEnJeu()[championChoice - 1];
        championToSacrifice->sacrifice(currentPlayer, this, false);
    }
}

void Game::useChampionAbility(Player* currentPlayer) {
    if (currentPlayer->getChampionsEnJeu().empty()) {
        cout << Display::RED << "❌ Vous n'avez aucun champion en jeu !" << Display::RESET << endl;
        return;
    }
    
    // Afficher les champions disponibles
    cout << Display::GREEN << Display::BOLD << "🛡️  Champions en jeu disponibles :" << Display::RESET << endl;
    Display::printSeparator("", "-", 50);
    
    bool hasAvailableChampions = false;
    for (size_t i = 0; i < currentPlayer->getChampionsEnJeu().size(); i++) {
        ChampionCard* champion = currentPlayer->getChampionsEnJeu()[i];
        cout << Display::CYAN << "   " << (i + 1) << ". " << Display::WHITE << Display::BOLD 
             << champion->getName() << Display::RESET
             << Display::WHITE << " [" << Display::RED << Display::BOLD 
             << champion->getDefense() << " PV" 
             << Display::WHITE << "]" << Display::RESET;
    
        
        if (champion->getActivated()) {
            cout << Display::YELLOW << " (Déjà activé ce tour)" << Display::RESET;
        } else {
            cout << Display::GREEN << " (Disponible)" << Display::RESET;
            hasAvailableChampions = true;
        }
        cout << endl;
    }
    
    if (!hasAvailableChampions) {
        cout << Display::YELLOW << "⚠️  Tous vos champions ont déjà été activés ce tour !" << Display::RESET << endl;
        return;
    }
    
    cout << Display::CYAN << "   0. " << Display::WHITE << "Annuler" << Display::RESET << endl;
    Display::printSeparator("", "-", 50);
    
    cout << Display::YELLOW << Display::BOLD << "🎯 Quel champion activer ? (0-" 
         << currentPlayer->getChampionsEnJeu().size() << "): " << Display::RESET;
    int choice = getSafeInput(0, static_cast<int>(currentPlayer->getChampionsEnJeu().size()));
    
    if (choice == 0) {
        cout << Display::WHITE << "Action annulée." << Display::RESET << endl;
        return;
    }
    
    ChampionCard* selectedChampion = currentPlayer->getChampionsEnJeu()[choice - 1];
    
    if (selectedChampion->getActivated()) {
        cout << Display::RED << "❌ Ce champion a déjà été activé ce tour !" << Display::RESET << endl;
        return;
    }
    
    // Activer le champion
    cout << Display::GREEN << Display::BOLD << "⚔️  Activation de " << selectedChampion->getName() << " !" << Display::RESET << endl;
    selectedChampion->activateAbility(currentPlayer, this);
}

void Game::toggleGodMode() {
    godMode = !godMode;
    
    if (godMode) {
        cout << Display::RED << Display::BOLD << "\n🔮 ═══════════════════════════════════════ 🔮" << Display::RESET << endl;
        cout << Display::RED << Display::BOLD << "     GOD MODE ACTIVÉ !" << Display::RESET << endl;
        cout << Display::RED << Display::BOLD << "🔮 ═══════════════════════════════════════ 🔮\n" << Display::RESET << endl;
        
        cout << Display::YELLOW << "Effets du God Mode:" << Display::RESET << endl;
        cout << Display::WHITE << "• Les joueurs passent à 1 PV" << Display::RESET << endl;
        cout << Display::WHITE << "• Vous pouvez acheter depuis toute la pioche du marché" << Display::RESET << endl;
        cout << Display::WHITE << "• Les cartes achetées vont directement en main\n" << Display::RESET << endl;
        
        // Sauvegarder les PV actuels avant de les changer
        savedHealthJoueur1 = joueur1->getHealth();
        savedHealthJoueur2 = joueur2->getHealth();
        
        cout << Display::CYAN << "💾 Sauvegarde des PV: " << joueur1->getName() << " (" 
             << savedHealthJoueur1 << " PV), " << joueur2->getName() << " (" 
             << savedHealthJoueur2 << " PV)" << Display::RESET << endl;
        
        // Mettre les deux joueurs à 1 PV
        joueur1->setHealth(1);
        joueur2->setHealth(1);
        
        cout << Display::RED << "⚠️  " << joueur1->getName() << " et " << joueur2->getName() 
             << " ont maintenant 1 PV !" << Display::RESET << endl;
    } else {
        cout << Display::GREEN << Display::BOLD << "\n🔓 ═══════════════════════════════════════ 🔓" << Display::RESET << endl;
        cout << Display::GREEN << Display::BOLD << "     GOD MODE DÉSACTIVÉ !" << Display::RESET << endl;
        cout << Display::GREEN << Display::BOLD << "🔓 ═══════════════════════════════════════ 🔓\n" << Display::RESET << endl;
        
        // Restaurer les PV sauvegardés
        joueur1->setHealth(savedHealthJoueur1);
        joueur2->setHealth(savedHealthJoueur2);
        
        cout << Display::GREEN << "🔄 Restauration des PV: " << joueur1->getName() << " (" 
             << savedHealthJoueur1 << " PV), " << joueur2->getName() << " (" 
             << savedHealthJoueur2 << " PV)" << Display::RESET << endl;
    }
}

void Game::buyCardFromFullMarket(Player* currentPlayer) {
    marche->displayFullMarket();
    
    int choice;
    cout << currentPlayer->getName() << ", quelle carte voulez-vous acheter ? (0 pour annuler): ";
    cin >> choice;
    
    if (choice == 0) {
        cout << "Achat annulé." << endl;
        return;
    }
    
    const auto& pioche = marche->getPiocheDuMarche();
    
    if (choice == static_cast<int>(pioche.size()) + 1) {
        // Acheter une gemme de feu
        Card* gem = marche->buyGem();
        if (gem != nullptr) {
            // Vérifier si le joueur a assez d'or
            if (currentPlayer->getGold() >= gem->getCost()) {
                currentPlayer->addGold(-gem->getCost());  // Déduire le coût
                currentPlayer->addCardToHand(gem);  // God Mode: va directement en main
                cout << Display::GREEN << Display::BOLD << "✨ " << currentPlayer->getName() 
                     << " achète " << gem->getName() << " pour " << gem->getCost() 
                     << " Or (ajoutée à la main) !" << Display::RESET << endl;
            } else {
                cout << Display::RED << "Pas assez d'or ! (Coût: " << gem->getCost() 
                     << " Or, Vous avez: " << currentPlayer->getGold() << " Or)" << Display::RESET << endl;
                // Remettre la gemme dans le stock
                marche->getPiocheDuMarche();  // La gemme a déjà été retirée par buyGem, on ne peut pas la remettre facilement
            }
        } else {
            cout << Display::RED << "Gemme indisponible." << Display::RESET << endl;
        }
        return;
    }
    
    // Acheter une carte de la pioche complète (index 1-N correspond à 0-(N-1))
    if (choice < 1 || choice > static_cast<int>(pioche.size())) {
        cout << Display::RED << "Choix invalide." << Display::RESET << endl;
        return;
    }
    
    // Vérifier le coût AVANT d'acheter
    Card* cardToCheck = pioche[choice - 1];
    if (currentPlayer->getGold() >= cardToCheck->getCost()) {
        Card* card = marche->buyCardFromFullMarket(choice - 1);
        if (card != nullptr) {
            currentPlayer->addGold(-card->getCost());  // Déduire le coût
            currentPlayer->addCardToHand(card);  // God Mode: va directement en main
            cout << Display::GREEN << Display::BOLD << "✨ " << currentPlayer->getName() 
                 << " achète " << card->getName() << " pour " << card->getCost() 
                 << " Or (ajoutée à la main) !" << Display::RESET << endl;
        } else {
            cout << Display::RED << "Carte indisponible." << Display::RESET << endl;
        }
    } else {
        cout << Display::RED << "Pas assez d'or ! (Coût: " << cardToCheck->getCost() 
             << " Or, Vous avez: " << currentPlayer->getGold() << " Or)" << Display::RESET << endl;
    }
}
