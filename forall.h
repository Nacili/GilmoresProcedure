#ifndef FORALL_H
#define FORALL_H

#include "quantifier.h"


class Forall : public Quantifier
{
public:
    Forall(const Variable &var, const Formula &f);

    virtual std::ostream& print(std::ostream & out) const;

    virtual Formula substitute(const Variable & v, const Term & t) const;

    virtual Formula substitute(const Substitution &s) const;

    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;

    virtual Formula simplify() const;

    virtual Formula nnf() const;

    virtual Formula prenex() const;

    virtual Formula skolem(Signature::Sptr s, VariablesSet &&vars) const;

    virtual Formula pullQuantifiers();
};

#endif // FORALL_H
