#include "quantifier.h"

uint64_t Quantifier::s_UniqueCounter = 0U;

Quantifier::Quantifier(const Variable &var, const Formula &f)
  : BaseFormula (), m_var(var), m_op(f)
{
}

unsigned Quantifier::complexity() const
{
  return 1 + m_op->complexity();
}

bool Quantifier::equalTo(const Formula &f) const
{
  if (BaseFormula::equalTo(f))
  {
    return m_var == static_cast<const Quantifier*>(f.get())->m_var &&
        m_op->equalTo(static_cast<const Quantifier*>(f.get())->m_op);
  }
  return false;
}

void Quantifier::getVars(VariablesSet &vars, bool free) const
{
  VariablesSet tmp;
  m_op->getVars(tmp);
  if (free)
  {
    tmp.erase(m_var);
  }
  vars.insert(tmp.cbegin(), tmp.cend());
}

std::ostream &Quantifier::printImpl(std::ostream &out, const std::string &symbol) const
{
  out << '(' << symbol << '.' << m_var << ")(";
  m_op->print(out);
  return out << ')';
}
