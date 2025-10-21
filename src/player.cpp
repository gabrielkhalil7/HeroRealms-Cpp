#include "../include/player.hpp"
#include "../include/actionCard.hpp"
#include "../include/itemCard.hpp"
#include "../include/championCard.hpp"
#include "../include/game.hpp"
#include "../include/deck.hpp"
#include "../include/market.hpp"
#include "../include/display.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

Player::Player(std::string playerName) : name(playerName), health(50), goldReserve(0), combatReserve(0), nextActionCardToTopOfDeck(false), nextAnyCardToTopOfDeck(false) {
    pioche = new Deck();
    defausse = new Deck();
}

Player::~Player() {
    delete pioche;
    delete defausse;
}

void Player::initializeDeck() { 
    // Normalement 7 Or, 1 Épée courte, 1 Dague, 1 Rubis dans la pioche
    ItemCard* or1 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* or2 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* or3 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* or4 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* or5 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* or6 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* or7 = new ItemCard("Or", 0, Faction::NEUTRE, CardId::OR);
    ItemCard* epeeCourte = new ItemCard("Épée Courte", 1, Faction::NEUTRE, CardId::EPEE_COURTE);
    ItemCard* dague = new ItemCard("Dague", 1, Faction::NEUTRE, CardId::DAGUE);
    ItemCard* rubis = new ItemCard("Rubis", 0, Faction::NEUTRE, CardId::RUBIS);
    
    // Ajout à la pioche
    pioche->addCard(or1);
    pioche->addCard(or2);
    pioche->addCard(or3);
    pioche->addCard(or4);
    pioche->addCard(or5);
    pioche->addCard(or6);
    pioche->addCard(or7);
    pioche->addCard(epeeCourte);
    pioche->addCard(dague);
    pioche->addCard(rubis);  

    // Mélanger la pioche
    //pioche->shuffle();
    std::cout << name << " a mélangé sa pioche." << std::endl;

    std::cout << name << " a été initialisé avec une pioche de " << pioche->size() << " cartes." << std::endl;
}

void Player::showHand() const {
    std::cout << std::endl;
    Display::printSeparator("✋ MAIN DE " + name + " ✋", "=", 60);
    
    if (main.empty()) {
        std::cout << Display::CYAN << "┌────────────────────────────────────────────────────────┐" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "│" << Display::WHITE << "                 Aucune carte en main                  " << Display::CYAN << "│" << Display::RESET << std::endl;
        std::cout << Display::CYAN << "└────────────────────────────────────────────────────────┘" << Display::RESET << std::endl;
    } else {
        std::cout << Display::CYAN << "┌────────────────────────────────────────────────────────┐" << Display::RESET << std::endl;
        for (size_t i = 0; i < main.size(); i++) {
            Card* card = main[i];
            std::string factionColor = Display::getFactionColor(card->getFaction());
            std::string factionSymbol = Display::getFactionSymbol(card->getFaction());
            
            // Déterminer le type de carte et son icône (sans couleur de type)
            std::string cardTypeIcon = "";
            if (dynamic_cast<ChampionCard*>(card)) {
                cardTypeIcon = "🛡️";
            } else if (dynamic_cast<ActionCard*>(card)) {
                cardTypeIcon = "⚔️";
            } else if (dynamic_cast<ItemCard*>(card)) {
                cardTypeIcon = "💎";
            }
            
            std::cout << Display::CYAN << "│ " << Display::WHITE << "[" << (i + 1) << "] " 
                      << factionColor << factionSymbol << " " << cardTypeIcon << " " 
                      << Display::BOLD << std::left << std::setw(16) << card->getName() << Display::RESET
                      << Display::YELLOW << " 🪙" << std::setw(2) << card->getCost() << Display::WHITE << " Or"
                      << std::string(18 - card->getName().length(), ' ')
                      << Display::CYAN << "│" << Display::RESET << std::endl;
        }
        std::cout << Display::CYAN << "└────────────────────────────────────────────────────────┘" << Display::RESET << std::endl;
    }
    
    // Affichage des ressources avec barre de santé
    std::cout << std::endl;
    std::cout << Display::WHITE << "🏥 Santé: ";
    Display::printHealthBar(health, 50);
    std::cout << "  ";
    Display::printResourceDisplay(goldReserve, combatReserve);
    std::cout << std::endl << std::endl;
}

void Player::addGold(int amount) {
    goldReserve += amount;
}

void Player::addCombat(int amount) {
    combatReserve += amount;
}

void Player::addHealth(int amount) {
    health += amount;
    if (health < 0) health = 0; // La santé ne peut pas être négative
}

int Player::countCardsInPlayByFaction(Faction faction) const {
    int count = 0;
    
    // Compter les cartes d'action/objet en jeu
    for (const Card* card : cartesEnJeu) {
        if (card->getFaction() == faction) {
            count++;
        }
    }
    
    // Compter les champions en jeu
    for (const Card* champion : championsEnJeu) {
        if (champion->getFaction() == faction) {
            count++;
        }
    }
    
    return count;
}

void Player::playCard(int cardIndex, Game* game) {
    if (cardIndex < 0 || static_cast<size_t>(cardIndex) >= main.size()) {
        std::cout << "Index de carte invalide!" << std::endl;
        return;
    }
    
    Card* card = main[cardIndex];
    
    // Retirer la carte de la main
    main.erase(main.begin() + cardIndex);
    
    // Vérifier si c'est un champion
    ChampionCard* champion = dynamic_cast<ChampionCard*>(card);
    if (champion) {
        // Les champions vont dans championsEnJeu
        championsEnJeu.push_back(champion);
    } else {
        // Les autres cartes vont dans cartesEnJeu
        cartesEnJeu.push_back(card);
    }
    
    // Jouer la carte
    card->play(this, game);
}

void Player::removeCardFromHand(Card* card) {
    auto it = std::find(main.begin(), main.end(), card);
    if (it != main.end()) {
        main.erase(it);
        std::cout << "Carte " << card->getName() << " retirée de la main de " << name << std::endl;
    }
}

void Player::removeCardFromPlay(Card* card) {
    auto it = std::find(cartesEnJeu.begin(), cartesEnJeu.end(), card);
    if (it != cartesEnJeu.end()) {
        cartesEnJeu.erase(it);
        std::cout << "Carte " << card->getName() << " retirée du jeu de " << name << std::endl;
    }
}

void Player::addCardToPlay(Card* card) {
    cartesEnJeu.push_back(card);
}

// Méthode pour piocher n cartes de son deck dans la main (avec mélange de la défausse si nécessaire)
void Player::draw(int n) {
    for (int i = 0; i < n; i++) {
        Card* drawnCard = nullptr;
        
        // Si la pioche est vide, mélanger la défausse pour créer une nouvelle pioche
        if (pioche->isEmpty() && !defausse->isEmpty()) {
            std::cout << name << " mélange sa défausse pour créer une nouvelle pioche." << std::endl;
            // Transférer toutes les cartes de la défausse vers la pioche
            while (!defausse->isEmpty()) {
                pioche->addCard(defausse->drawCard());
            }
            pioche->shuffle();
        }
        
        // Piocher une carte
        drawnCard = pioche->drawCard();
        
        if (drawnCard != nullptr) {
            main.push_back(drawnCard);
            std::cout << name << " pioche une carte : " << drawnCard->getName() << std::endl;
        } else {
            std::cout << name << " ne peut plus piocher de cartes (pioche et défausse vides)." << std::endl;
            break;
        }
    }
}

void Player::addCardToTopOfDeck(Card* card) {
    pioche->addCardToTop(card);
    std::cout << "Carte " << card->getName() << " ajoutée au-dessus de la pioche de " << name << std::endl;
}

void Player::buyCard(Market& market, bool godMode) {
    market.display();
    
    int choice;
    std::cout << name << ", que voulez-vous acheter ? (0 pour annuler): ";
    std::cin >> choice;
    
    if (choice == 0) {
        std::cout << "Achat annulé." << std::endl;
        return;
    }
    
    if (choice == 6) {
        // Acheter une gemme de feu
        Card* gem = market.buyGem();
        if (gem != nullptr && (goldReserve >= gem->getCost() || godMode)) {
            if (!godMode) goldReserve -= gem->getCost();
            defausse->addCard(gem);  // Les gemmes vont normalement en défausse
            std::cout << name << " achète " << gem->getName() << " pour " << gem->getCost() << " Or." << std::endl;
        } else {
            std::cout << "Pas assez d'or ou gemme indisponible." << std::endl;
        }
        return;
    }
    
    // Acheter une carte du marché (index 1-5 correspond à 0-4)
    Card* card = market.buyCard(choice - 1);
    if (card != nullptr && (goldReserve >= card->getCost() || godMode)) {
        if (!godMode) goldReserve -= card->getCost();
        
        // Vérifier les effets spéciaux qui modifient la destination de la carte (effets de cartes)
        bool cardGoesToTop = false;
        std::string effectName = "";
        
        // verification effet Fourberie (n'importe quelle carte)
        if (nextAnyCardToTopOfDeck) {
            cardGoesToTop = true;
            effectName = "Fourberie";
            nextAnyCardToTopOfDeck = false;  // Réinitialiser le flag après usage
        }
        // verification effet Pot-de-Vin (seulement cartes Action)
        else {
            ActionCard* actionCard = dynamic_cast<ActionCard*>(card);
            if (actionCard != nullptr && nextActionCardToTopOfDeck) {
                cardGoesToTop = true;
                effectName = "Pot-de-Vin";
                nextActionCardToTopOfDeck = false;  // Réinitialiser le flag après usage
            }
        }
        
        if (cardGoesToTop) {
            // Effet spécial actif : mettre la carte au-dessus de la pioche
            addCardToTopOfDeck(card);
            std::cout << name << " achète " << card->getName() << " pour " << card->getCost() << " gold (placée au-dessus de la pioche grâce à " << effectName << ")." << std::endl;
        } else {
            // Comportement normal : mettre la carte en défausse
            defausse->addCard(card);
            std::cout << name << " achète " << card->getName() << " pour " << card->getCost() << " gold." << std::endl;
        }
    } else {
        std::cout << "Pas assez d'or ou carte indisponible." << std::endl;
    }
}

void Player::stunChampion(ChampionCard* champion) {
    // Retirer le champion du jeu
    auto it = std::find(championsEnJeu.begin(), championsEnJeu.end(), champion);
    if (it != championsEnJeu.end()) {
        championsEnJeu.erase(it);
        defausse->addCard(champion);  // Ajouter le champion à la défausse
        std::cout << "Champion " << champion->getName() << " de " << name << " a été assommé et envoyé en défausse !" << std::endl;
    }
}

std::vector<ChampionCard*> Player::getTargetableChampions() const {
    std::vector<ChampionCard*> targetableChampions;
    std::vector<ChampionCard*> guardChampions;
    
    // Séparer les champions Gardes des autres
    for (ChampionCard* champion : championsEnJeu) {
        if (champion->getGuarding()) {
            guardChampions.push_back(champion);
        } else {
            targetableChampions.push_back(champion);
        }
    }
    
    // Si il y a des champions Gardes, on ne peut cibler qu'eux
    if (!guardChampions.empty()) {
        return guardChampions;
    }
    
    // Sinon, on peut cibler tous les champions
    return targetableChampions;
}

const std::vector<Card*>& Player::getDiscardPile() const {
    return defausse->getCards();
}

void Player::addToDiscardPile(Card* card) {
    if (card != nullptr) {
        defausse->addCard(card);
    }
}

void Player::removeCardFromDiscard(Card* card) {
    if (card != nullptr) {
        defausse->removeCard(card);
    }
}

Card* Player::moveCardFromDiscardToTopOfDeck(Card* card) {
    Card* removedCard = defausse->removeCard(card);
    if (removedCard != nullptr) {
        pioche->addCardToTop(removedCard);
        std::cout << "Carte " << card->getName() << " déplacée de la défausse vers le haut de la pioche de " << name << std::endl;
        return removedCard;
    }
    return nullptr;
}

bool Player::hasGuardingChampions() const {
    for (const ChampionCard* champion : championsEnJeu) {
        if (champion->getGuarding()) {
            return true;
        }
    }
    return false;
}

void Player::useCombat(int amount) {
    if (amount <= combatReserve) {
        combatReserve -= amount;
    } else {
        std::cout << "Pas assez de Combat disponible." << std::endl;
    }
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void Player::endTurn() {
    // Remettre les ressources à 0
    goldReserve = 0;
    combatReserve = 0;
    
    // Défausser toutes les cartes en jeu (sauf les champions)
    for (Card* card : cartesEnJeu) {
        defausse->addCard(card);
    }
    cartesEnJeu.clear();
    
    // Désactiver tous les champions en jeu (ils restent en jeu mais sont désactivés)
    for (ChampionCard* champion : championsEnJeu) {
        champion->setDefenseActuelle(champion->getMaxDefense()); //  on retablit la defense
        champion->setActivated(false);  // on le desactive pour le prochain tour
    }
    
    // Defausser toutes les cartes de la main (celles qui ne sont pas jouees)
    for (Card* card : main) {
        defausse->addCard(card);
    }
    main.clear();
    
    // Réinitialiser les flags d'effet
    nextActionCardToTopOfDeck = false;
    nextAnyCardToTopOfDeck = false;
    
    // Piocher 5 nouvelles cartes
    draw(5);
    
    std::cout << name << " termine son tour et pioche 5 nouvelles cartes." << std::endl;
}