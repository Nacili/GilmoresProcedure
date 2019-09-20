#include "base_formula.h"
#include "forall.h"

#include <typeinfo>

BaseFormula::BaseFormula()
{}

BaseFormula::~BaseFormula()
{}

bool BaseFormula::equalTo(const Formula &f) const
{
    const BaseFormula *base = f.get();
    return typeid (*this) == typeid (*base);
}

bool BaseFormula::hasVariable(const Variable &v, bool free) const
{
  VariablesSet vset;
  getVars(vset, free);
  return vset.find(v) != vset.cend();
}

Formula BaseFormula::substitute(const Substitution &s) const
{
    UNUSED_ARG(s);
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::simplify() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::nnf() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::pullQuantifiers() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::prenex() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::removeUniversalQ(const Formula &f)
{
    Forall * fa = NULL;
    if (BaseFormula::isOfType<Forall>(f)) {
        fa = (Forall*)f.get();
        return removeUniversalQ(fa->operand());
    } else {
        return f;
    }
}

Formula BaseFormula::skolem(Signature::Sptr s, VariablesSet &&vars) const
{
    UNUSED_ARG(s);
    UNUSED_ARG(vars);
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

std::ostream& operator<<(std::ostream &out, const Formula &f)
{
    return f->print(out);
}


template<typename ListType>
ListType concatLists(const ListType &l1, const ListType &l2)
{
    ListType result;
    result.reserve(l1.size() + l2.size());
    std::copy(l1.cbegin(), l1.cbegin(), std::back_inserter(result));
    std::copy(l2.cbegin(), l2.cend(), std::back_inserter(result));
    return result;
}

LiteralListList makePairs(const LiteralListList &c1, const LiteralListList &c2)
{
    LiteralListList result;
    result.reserve(c1.size()*c2.size());
    for(const auto& outer : c1)
    {
        for(const auto& inner : c2)
        {
            result.push_back(concatLists(outer, inner));
        }
    }
    return result;
}
