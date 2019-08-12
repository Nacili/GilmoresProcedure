#ifndef IFF_H
#define IFF_H

#include "binary_connective.h"

class Iff : public BinaryConnective
{
public:
    Iff(const Formula &op1, const Formula &op2);
    
    virtual std::ostream& print(std::ostream & out) const;
    
    virtual Formula substitute(const Variable & v, const Term & t) const;
    
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
    
    virtual Formula simplify() const;
    
    virtual Formula nnf() const;
};

#endif // IFF_H
