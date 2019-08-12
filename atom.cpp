#include "atom.h"

#include <algorithm>
#include <stdexcept>

Atom::Atom(Signature::Sptr signature, const RelationSymbol &symbol, const std::vector<Term> &terms)
    : AtomicFormula (), m_signature(signature), m_symbol(symbol), m_terms(terms)
{
    if (!signature->hasPredicateSymbol(m_symbol, (unsigned)m_terms.size()))
    {
        throw std::runtime_error{"Syntax error in construction of Atom"};
    }
}

std::ostream& Atom::print(std::ostream &out) const
{
    if (m_terms.empty())
    {
      return out << m_symbol;
    }
    else
    {
      out << m_symbol << "(";
      for (auto first = m_terms.cbegin(), last = m_terms.cend(); first + 1 != last; ++first)
      {
        (*first)->print(out);
        out << ", ";
      }
      m_terms.back()->print(out);
      return out << ")";
    }
}

bool Atom::equalTo(const Formula &f) const
{
    const Atom *pF = dynamic_cast<const Atom*>(f.get());
    if (pF)
    {
        return symbol() == pF->symbol() && 
            m_terms.size() == pF->m_terms.size() &&
            std::equal(m_terms.cbegin(), m_terms.cend(), pF->m_terms.cbegin());
    }
    else
    {
        return false;
    }
}

void Atom::getVars(VariablesSet &vars, bool free) const
{
    UNUSED_ARG(free);
    for (const Term &t : m_terms)
    {
        t->getVariables(vars);
    }
}

bool Atom::eval(const LStructure &structure, const Valuation &valuation) const
{
    Relation r = structure.getRelation(m_symbol);
    std::vector<AnyType> termValues;
    termValues.reserve(m_terms.size());
    std::transform(m_terms.cbegin(), m_terms.cend(), std::back_inserter(termValues), 
                   [&](const Term &t) {
       return t->eval(structure, valuation); 
    });
    return r->eval(termValues);
}

Formula Atom::substitute(const Variable &v, const Term &t) const
{
    std::vector<Term> terms;
    terms.reserve(m_terms.size());
    std::transform(m_terms.cbegin(), m_terms.cend(), std::back_inserter(terms), [&](const Term &el) { return el->substitute(v, t); });
    return std::make_shared<Atom>(m_signature, m_symbol, terms);
}
