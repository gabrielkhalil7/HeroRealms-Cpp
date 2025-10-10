#include "../include/player.hpp"

Player::Player(std::string playerName) : name(playerName), health(30), goldReserve(0), combatReserve(0) {
    // pioche = new Deck();
    // defausse = new Deck();
}

Player::~Player() {
    // delete pioche;
    // delete defausse;
}

void Player::initializeDeck() {
    // Initialiser le deck de départ du joueur
    // Ajouter des cartes de base au deck
}

void Player::showHand() const {
    // Afficher les cartes dans la main du joueur
    // cout << "Main de " << name << " :" << endl;
    // for (const auto& card : main) {
    //     cout << "- " << card->getName() << endl;
    // }
}