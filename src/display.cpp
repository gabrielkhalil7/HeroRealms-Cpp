#include "../include/display.hpp"
#include <iomanip>
#include <sstream>

// Codes couleur ANSI
const std::string Display::RESET = "\033[0m";
const std::string Display::BOLD = "\033[1m";
const std::string Display::UNDERLINE = "\033[4m";

// Couleurs de base
const std::string Display::RED = "\033[31m";
const std::string Display::GREEN = "\033[32m";
const std::string Display::YELLOW = "\033[33m";
const std::string Display::BLUE = "\033[34m";
const std::string Display::MAGENTA = "\033[35m";
const std::string Display::CYAN = "\033[36m";
const std::string Display::WHITE = "\033[37m";
const std::string Display::BLACK = "\033[30m";

// Couleurs de fond
const std::string Display::BG_RED = "\033[41m";
const std::string Display::BG_GREEN = "\033[42m";
const std::string Display::BG_YELLOW = "\033[43m";
const std::string Display::BG_BLUE = "\033[44m";
const std::string Display::BG_MAGENTA = "\033[45m";
const std::string Display::BG_CYAN = "\033[46m";
const std::string Display::BG_WHITE = "\033[47m";
const std::string Display::BG_BLACK = "\033[40m";

void Display::clearScreen() {
    std::cout << "\033[2J\033[H";
}

void Display::printTitle() {
    std::cout << std::endl;
    printSeparator("", "█", 60);
    std::cout << BOLD << YELLOW << "██   ██ ███████ ██████   ██████      ██████  ███████  █████  ██      ███    ███ ███████" << RESET << std::endl;
    std::cout << BOLD << YELLOW << "██   ██ ██      ██   ██ ██    ██     ██   ██ ██      ██   ██ ██      ████  ████ ██     " << RESET << std::endl;
    std::cout << BOLD << YELLOW << "███████ █████   ██████  ██    ██     ██████  █████   ███████ ██      ██ ████ ██ ███████" << RESET << std::endl;
    std::cout << BOLD << YELLOW << "██   ██ ██      ██   ██ ██    ██     ██   ██ ██      ██   ██ ██      ██  ██  ██      ██" << RESET << std::endl;
    std::cout << BOLD << YELLOW << "██   ██ ███████ ██   ██  ██████      ██   ██ ███████ ██   ██ ███████ ██      ██ ███████" << RESET << std::endl;
    printSeparator("", "█", 60);
    std::cout << std::endl;
}

void Display::printSeparator(const std::string& title, const std::string& symbol, int width) {
    if (title.empty()) {
        for (int i = 0; i < width; i++) std::cout << symbol;
        std::cout << RESET << std::endl;
    } else {
        int symbolWidth = symbol.length();
        int padding = (width - title.length() - 2) / 2;
        std::cout << CYAN;
        for (int i = 0; i < padding / symbolWidth; i++) std::cout << symbol;
        std::cout << " " << BOLD << WHITE << title << RESET << CYAN << " ";
        for (int i = 0; i < padding / symbolWidth; i++) std::cout << symbol;
        if ((width - title.length()) % 2 == 1) std::cout << symbol;
        std::cout << RESET << std::endl;
    }
}

void Display::printBox(const std::string& content, const std::string& color) {
    std::cout << color << "┌─────────────────────────────────────┐" << RESET << std::endl;
    std::cout << color << "│ " << WHITE << BOLD << std::left << std::setw(35) << content << RESET << color << " │" << RESET << std::endl;
    std::cout << color << "└─────────────────────────────────────┘" << RESET << std::endl;
}

void Display::printCenteredText(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << std::endl;
}

std::string Display::getFactionColor(Faction faction) {
    switch (faction) {
        case Faction::IMPERIAL: return YELLOW;
        case Faction::GUILDE: return BLUE;
        case Faction::NECROS: return RED;
        case Faction::SAUVAGE: return GREEN;
        case Faction::NEUTRE: return WHITE;
        default: return WHITE;
    }
}

std::string Display::getFactionSymbol(Faction faction) {
    switch (faction) {
        case Faction::IMPERIAL: return "🟡";
        case Faction::GUILDE: return "🔵";
        case Faction::NECROS: return "🔴";
        case Faction::SAUVAGE: return "🟢";
        case Faction::NEUTRE: return "⚪";
        default: return "?";
    }
}

void Display::printGameBoard() {
    std::cout << std::endl;
    printSeparator("TERRAIN DE JEU", "=", 80);
    
    // Zone adversaire
    std::cout << CYAN << "┌─────────────────────── " << RED << "ADVERSAIRE" << CYAN << " ──────────────────────┐" << RESET << std::endl;
    std::cout << CYAN << "│" << std::string(78, ' ') << "│" << RESET << std::endl;
    std::cout << CYAN << "│  " << RED << "Champions:" << WHITE << " [Zone des champions adverses]" << std::string(37, ' ') << CYAN << "│" << RESET << std::endl;
    std::cout << CYAN << "│" << std::string(78, ' ') << "│" << RESET << std::endl;
    std::cout << CYAN << "└────────────────────────────────────────────────────────────────────────────┘" << RESET << std::endl;
    
    // Zone centrale (marché)
    std::cout << YELLOW << "┌─────────────────────────── " << BOLD << "MARCHÉ" << RESET << YELLOW << " ───────────────────────────┐" << RESET << std::endl;
    std::cout << YELLOW << "│" << std::string(78, ' ') << "│" << RESET << std::endl;
    std::cout << YELLOW << "│  " << WHITE << "[1] [2] [3] [4] [5]     " << YELLOW << "Gemmes:" << WHITE << " [16]" << std::string(31, ' ') << YELLOW << "│" << RESET << std::endl;
    std::cout << YELLOW << "│" << std::string(78, ' ') << "│" << RESET << std::endl;
    std::cout << YELLOW << "└────────────────────────────────────────────────────────────────────────────┘" << RESET << std::endl;
    
    // Zone joueur
    std::cout << CYAN << "┌─────────────────────── " << GREEN << "VOTRE ZONE" << CYAN << " ───────────────────────┐" << RESET << std::endl;
    std::cout << CYAN << "│" << std::string(78, ' ') << "│" << RESET << std::endl;
    std::cout << CYAN << "│  " << GREEN << "Champions:" << WHITE << " [Vos champions en jeu]" << std::string(41, ' ') << CYAN << "│" << RESET << std::endl;
    std::cout << CYAN << "│  " << GREEN << "Main:     " << WHITE << " [Vos cartes en main]" << std::string(43, ' ') << CYAN << "│" << RESET << std::endl;
    std::cout << CYAN << "│" << std::string(78, ' ') << "│" << RESET << std::endl;
    std::cout << CYAN << "└────────────────────────────────────────────────────────────────────────────┘" << RESET << std::endl;
    std::cout << std::endl;
}

void Display::printCardFrame(const std::string& name, const std::string& cost, const std::string& faction, bool selected) {
    std::string frameColor = selected ? BG_YELLOW + BLACK : CYAN;
    std::string factionColor = getFactionColor(static_cast<Faction>(std::stoi(faction)));
    
    std::cout << frameColor << "┌─────────────────┐" << RESET << std::endl;
    std::cout << frameColor << "│ " << factionColor << BOLD << std::left << std::setw(15) << name.substr(0, 15) << RESET << frameColor << " │" << RESET << std::endl;
    std::cout << frameColor << "│ " << YELLOW << "Coût: " << WHITE << std::left << std::setw(8) << cost << RESET << frameColor << " │" << RESET << std::endl;
    std::cout << frameColor << "└─────────────────┘" << RESET << std::endl;
}

void Display::printHealthBar(int currentHealth, int maxHealth) {
    int barWidth = 20;
    float percentage = static_cast<float>(currentHealth) / maxHealth;
    int filledWidth = static_cast<int>(percentage * barWidth);
    
    std::string healthColor;
    if (percentage > 0.7f) healthColor = GREEN;
    else if (percentage > 0.3f) healthColor = YELLOW;
    else healthColor = RED;
    
    std::cout << WHITE << "❤️  " << healthColor << BOLD;
    for (int i = 0; i < filledWidth; i++) std::cout << "█";
    std::cout << WHITE;
    for (int i = filledWidth; i < barWidth; i++) std::cout << "░";
    std::cout << RESET << " " << healthColor << BOLD << currentHealth << WHITE << "/" << maxHealth << RESET;
}

void Display::printResourceDisplay(int gold, int combat) {
    std::cout << YELLOW << "💰" << BOLD << gold << RESET << "  " 
              << RED << "⚔️ " << BOLD << combat << RESET;
}