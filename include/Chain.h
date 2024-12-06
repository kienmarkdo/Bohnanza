#ifndef CHAIN_H
#define CHAIN_H

#include "Chain_Base.h"
#include <vector>
#include <stdexcept>

template<class T>
class Chain : public Chain_Base {
private:
    std::vector<Card*> chain;
public:
    Chain() = default;
    Chain_Base& operator+=(Card* card) override {
        T* casted = dynamic_cast<T*>(card);
        if (!casted) throw std::invalid_argument("IllegalType");
        chain.push_back(card);
        return *this;
    }
    int sell() const override {
        if (chain.empty()) return 0;
        const Card* c = chain.front();
        int total = (int)chain.size();
        for (int coins = 4; coins >= 1; --coins) {
            try {
                int needed = c->getCardsPerCoin(coins);
                if (total >= needed) return coins;
            } catch (...) {}
        }
        return 0;
    }
    std::string getBeanName() const override {
        if (chain.empty()) {
            T tempCard;
            return tempCard.getName();
        } else {
            return chain.front()->getName();
        }
    }
    void print(std::ostream& out) const override {
        if (chain.empty()) {
            T tempCard;
            out << tempCard.getName() << " ";
        } else {
            out << chain.front()->getName() << " ";
        }
        for (auto c : chain) out << *c << " ";
    }
    void clear() override {
        chain.clear();
    }
    void moveCardsToDiscardPile(DiscardPile& dp) override {
        for (auto c : chain) dp += c;
        chain.clear();
    }
    int size() const override {
        return (int)chain.size();
    }
    Card* frontCard() const override {
        return chain.empty() ? nullptr : chain.front();
    }
    void removeFrontCards(int n, DiscardPile& dp) override {
        for (int i = 0; i < n && !chain.empty(); ++i) {
            dp += chain.front();
            chain.erase(chain.begin());
        }
    }
};

#endif
