// Chain_Base.h
#ifndef CHAIN_BASE_H
#define CHAIN_BASE_H

#include <iostream>
class Chain_Base
{
public:
    virtual ~Chain_Base() = default;
    virtual int sell() = 0;
    virtual void print(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, const Chain_Base &chain)
{
    chain.print(out);
    return out;
}

#endif // CHAIN_BASE_H