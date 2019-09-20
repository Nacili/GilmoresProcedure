#ifndef OR_H
#define OR_H

#include "binary_connective.h"

class Or : public BinaryConnective
{
public:
    Or(const Formula &op1, const Formula &op2);
    
    virtual std::ostream& print(std::ostream & out) const;
    
    virtual Formula substitute(const Variable & v, const Term & t) const;
    
    virtual Formula substitute(const Substitution &s) const;
    
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
    
    virtual Formula simplify() const;
    
    virtual Formula nnf() const;
    
    virtual Formula pullQuantifiers() const;
    
    virtual Formula prenex() const;


    LiteralListList listDNF();
};

#endif // OR_H
