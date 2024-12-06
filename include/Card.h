#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
public:
    virtual ~Card() {}
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Card& c) {
        c.print(out);
        return out;
    }
};

class Blue : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Chili : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Stink : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Green : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Soy : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Black : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Red : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Garden : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

#endif
