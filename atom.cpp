#include "atom.h"

#include <algorithm>

Atom::Atom(Signature::Sptr signature, const RelationSymbol &rsym, const std::vector<Term> &terms)
    : AtomicFormula(), m_sig{signature}, m_rsym{rsym}, m_terms{terms}
{
    if(!signature->hasPredicateSymbol(rsym, terms.size())){
        throw std::runtime_error("Construction of Atom");
    }
}

bool Atom::hasVariable(const Variable &v, bool free) const
{
    UNUSED_ARG(free);
    for (const auto &term : m_terms)
    {
      if (term->hasVariable(v))
      {
        return true;
      }
    }
    return false;
}


std::ostream &Atom::print(std::ostream &out) const
{
    if(m_terms.empty()){
        return out << m_rsym;
    }
    else{
        out << m_rsym << "(";
        for(auto first = m_terms.cbegin(), last = m_terms.cend(); first + 1 != last; ++first){
            (*first)->print(out);
            out << ", ";
        }
        m_terms.back()->print(out);
        return out << ")";
    }
}

bool Atom::equalTo(const Formula &f) const
{
    const Atom *fP = dynamic_cast<const Atom*>(f.get());
    if(fP){
        return fP->symbol() == symbol() &&
                fP->m_terms.size() == m_terms.size() &&
                std::equal(m_terms.cbegin(), m_terms.cend(), fP->m_terms.cbegin());
    }
    else{
        return false;
    }
}

bool Atom::eval(const LStructure &structure, const Valuation &valuation) const
{
    Relation r = structure.getRelation(m_rsym);
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
    return std::make_shared<Atom>(m_sig, m_rsym, terms);
}

Formula Atom::substitute(const Substitution &s) const
{
    std::vector<Term> modifiedTerms;
    modifiedTerms.reserve(m_terms.size());
    for (const Term &t : m_terms)
    {
        modifiedTerms.push_back(t->substitute(s));
    }
    return std::make_shared<Atom>(m_sig, m_rsym, modifiedTerms);
}


void Atom::getVars(VariablesSet &vars, bool free) const
{
    UNUSED_ARG(free);
    for (const Term &t : m_terms)
    {
        t->getVariables(vars);
    }
}

void Atom::getConstants(ConstantSet &cts) const
{
    for(unsigned i = 0; i < m_terms.size(); i++) {
            m_terms[i]->getConstants(cts);
    }
}

void Atom::getFunctions(FunctionSet &fs) const
{
    for(unsigned i = 0; i < m_terms.size(); i++) {
            m_terms[i]->getFunctions(fs);
    }
}


LiteralListList Atom::listDNF()
{
    return {{std::const_pointer_cast<BaseFormula>(shared_from_this())}};
}
