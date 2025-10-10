#include "../include/player.hpp"
#include "../include/actionCard.hpp"
#include "../include/championCard.hpp"
#include "../include/game.hpp"
#include "../include/deck.hpp"
#include <iostream>
#include <string>

Player::Player(std::string playerName) : name(playerName), health(30), goldReserve(0), combatReserve(0) {
    pioche = new Deck();
    defausse = new Deck();
}

Player::~Player() {
    delete pioche;
    delete defausse;
}

void Player::initializeDeck() {
    // Pour les tests, on va créer quelques cartes Taxation
    // Normalement ce serait 7 Or, 1 Épée courte, 1 Dague, 1 Rubis
    
    // Créer 3 cartes Taxation pour tester les effets alliés
    ActionCard* taxation1 = new ActionCard("Taxation", 1, Faction::IMPERIAL, CardId::TAXATION);
    ActionCard* taxation2 = new ActionCard("Taxation", 1, Faction::IMPERIAL, CardId::TAXATION);
    ActionCard* taxation3 = new ActionCard("Taxation", 1, Faction::IMPERIAL, CardId::TAXATION);
    
    // Ajouter à la pioche (normalement on les ajouterait au deck)
    // Pour simplicité, on les met directement en main
    main.push_back(taxation1);
    main.push_back(taxation2);
    main.push_back(taxation3);
    
    std::cout << name << " a été initialisé avec 3 cartes Taxation pour les tests" << std::endl;
}

void Player::showHand() const {
    // Afficher les cartes dans la main du joueur
    std::cout << "Main de " << name << " :" << std::endl;
    for (const auto& card : main) {
        std::cout << "- " << card->getName() << std::endl;
    }
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
    
    // Retirer la carte de la main et la mettre en jeu
    main.erase(main.begin() + cardIndex);
    cartesEnJeu.push_back(card);
    
    // Jouer la carte
    card->play(this, game);
}