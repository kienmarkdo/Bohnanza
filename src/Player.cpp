#include "Player.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <limits>
#include "CardFactory.h"
#include "Chain.h"

Player::Player(const std::string &playerName)
    : name(playerName) {
    chains.reserve(3);
    chains.push_back(nullptr);
    chains.push_back(nullptr);
}

// Updated constructor to load from file
Player::Player(std::istream &in, const CardFactory *factory) {
    // Read player name
    std::getline(in, name);

    // Read coins
    in >> coins;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read number of chains
    int chainCount;
    in >> chainCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    chains.reserve(3);

    for (int i = 0; i < chainCount; ++i) {
        std::string line;
        std::getline(in, line);

        if (line == "EMPTY_CHAIN") {
            chains.push_back(nullptr);
            continue;
        }

        // line should now be the chain type
        std::string chainType = line;

        if (chainType == "Blue") {
            chains.push_back(std::make_unique<Chain<Blue>>(in, factory));
        } else if (chainType == "Chili") {
            chains.push_back(std::make_unique<Chain<Chili>>(in, factory));
        } else if (chainType == "Stink") {
            chains.push_back(std::make_unique<Chain<Stink>>(in, factory));
        } else if (chainType == "Green") {
            chains.push_back(std::make_unique<Chain<Green>>(in, factory));
        } else if (chainType == "Soy") {
            chains.push_back(std::make_unique<Chain<Soy>>(in, factory));
        } else if (chainType == "Black") {
            chains.push_back(std::make_unique<Chain<Black>>(in, factory));
        } else if (chainType == "Red") {
            chains.push_back(std::make_unique<Chain<Red>>(in, factory));
        } else if (chainType == "Garden") {
            chains.push_back(std::make_unique<Chain<Garden>>(in, factory));
        } else {
            throw std::runtime_error("Unknown chain type encountered while loading player: " + chainType);
        }
    }

    // Load the hand
    Hand loadedHand(in, factory);
    hand = std::move(loadedHand);
}

Player &Player::operator+=(int additionalCoins) {
    if (additionalCoins < 0) {
        throw std::invalid_argument("Cannot add negative coins");
    }
    coins += additionalCoins;
    return *this;
}

int Player::getNumChains() const {
    return std::count_if(chains.begin(), chains.end(),
                         [](const auto &chain) {
                             return chain && chain->size() > 0;
                         });
}

void Player::validateChainIndex(int index) const {
    if (index < 0 || index >= static_cast<int>(chains.size())) {
        std::ostringstream oss;
        oss << "Chain index " << index << " is out of range. Player has "
            << chains.size() << " chains";
        throw std::out_of_range(oss.str());
    }
}

Chain_Base &Player::operator[](int i) {
    validateChainIndex(i);
    return *chains[i];
}

const Chain_Base &Player::operator[](int i) const {
    validateChainIndex(i);
    return *chains[i];
}

void Player::buyThirdChain() {
    if (chains.size() >= 3) {
        throw std::runtime_error("Already has maximum number of chains");
    }

    if (coins < 3) {
        throw NotEnoughCoins();
    }

    coins -= 3;
    chains.push_back(nullptr);
}

void Player::printHand(std::ostream &out, bool all) const {
    if (all) {
        out << hand;
    } else {
        if (!hand.empty()) {
            out << "Top card: ";
            if (const Card *top = hand.top()) {
                top->print(out);
                out << "\n";
            }
        } else {
            out << "Hand is empty\n";
        }
    }
}

void Player::serialize(std::ostream &out) const {
    out << name << "\n";
    out << coins << "\n";
    out << chains.size() << "\n";

    for (const auto &chain : chains) {
        if (chain) {
            chain->serialize(out);
        } else {
            out << "EMPTY_CHAIN\n";
        }
    }

    hand.serialize(out);
}

std::ostream &operator<<(std::ostream &out, const Player &player) {
    out << std::left << player.name << "\t" << player.coins << " coins\n";

    for (const auto &chain : player.chains) {
        if (chain) {
            out << chain->getType() << "\t";
            chain->print(out);
            out << "\n";
        } else {
            out << "empty\t\n";
        }
    }

    return out;
}

void Player::addToFrontOfHand(std::unique_ptr<Card> card) {
    if (!card) {
        throw std::runtime_error("Cannot add null card to hand");
    }
    hand.addToFront(std::move(card));
}
