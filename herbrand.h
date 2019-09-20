#ifndef HERBRAND_H
#define HERBRAND_H

#include <string>
#include <iostream>

#include "first_order_logic.h"

class HerbrandUniverse {
public:
    HerbrandUniverse(Signature::Sptr signature, const Formula &formula);
    std::set<Term> getLevel() const;
    void nextLevel();
private:
    Signature::Sptr m_signature;
    Formula m_formula;
    FunctionSet m_functions;
    std::set<Term> m_level;
    friend std::ostream& operator<<(std::ostream &out, const HerbrandUniverse &hu);
};

#endif
