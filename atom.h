#ifndef ATOM_H
#define ATOM_H

#include "atomic_formula.h"
#include "base_term.h"
#include "signature.h"

#include <vector>

class Atom : public AtomicFormula
{
public:
    Atom(Signature::Sptr signature, const RelationSymbol &symbol, const std::vector<Term> &terms);
    
    inline const RelationSymbol& symbol() const { return m_symbol; }
    
    inline const std::vector<Term>& operands() const { return m_terms; }
    
    virtual std::ostream& print(std::ostream & out) const;
  
    virtual bool equalTo(const Formula & f) const;
  
    virtual void getVars(VariablesSet & vars, bool free = false) const;
  
    bool hasVariable(const Variable & v, bool free = false) const;
  
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
  
    virtual Formula substitute(const Variable & v, const Term & t) const;
    
private:
    /**
     * @brief m_signature je signatura kojoj relacijski simbol 'm_symbol' mora da pripada
     */
    Signature::Sptr m_signature;
    /**
     * @brief m_symbol je simbol relacije, na primer '<' za relaciju 'manje od'
     */
    RelationSymbol m_symbol;
    /**
     * @brief m_terms je vektor termova koji su argumenti relacije, na primer 
     * relacija '<' bi mogla da ima 2 argumenta koji se porede
     */
    std::vector<Term> m_terms;
};

#endif // ATOM_H