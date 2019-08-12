#include "base_formula.h"

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
