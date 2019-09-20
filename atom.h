#ifndef ATOM_H
#define ATOM_H

#include "atomic_formula.h"
#include <vector>

class Atom : public AtomicFormula
{
public:
    Atom(Signature::Sptr signature, const RelationSymbol &rsym, const std::vector<Term> &terms);
    inline const RelationSymbol& symbol() const {return m_rsym;}
    inline const std::vector<Term>& operands() const {return m_terms;}
    bool hasVariable(const Variable &v, bool free = false) const;
private:
    Signature::Sptr m_sig;
    RelationSymbol m_rsym;
    std::vector<Term> m_terms;

    // BaseFormula interface
public:
    std::ostream &print(std::ostream &out) const;
    bool equalTo(const Formula &f) const;
    bool eval(const LStructure &structure, const Valuation &valuation) const;
    Formula substitute(const Variable &v, const Term &t) const;
    Formula substitute(const Substitution &s) const;
    void getVars(VariablesSet &vars, bool free) const;
    virtual void getConstants(ConstantSet & cts) const;
    virtual void getFunctions(FunctionSet & fs) const;
    virtual LiteralListList listDNF();
};

#endif // ATOM_H
