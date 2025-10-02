#include "../include/player.hpp"

Player::Player(std::string playerName) : name(playerName), health(30), goldReserve(0), combatReserve(0) {
    // pioche = new Deck();
    // defausse = new Deck();
}

Player::~Player() {
    // delete pioche;
    // delete defausse;
}