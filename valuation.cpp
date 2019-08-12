#include "valuation.h"


Valuation::Valuation(const Domain &d)
    : m_domain(d)
{
}

void Valuation::setValue(const Variable &v, const AnyType &val)
{   
    if (m_domain->hasValue(val))
    {
        m_map[v] = val;
    }
    else
    {
        throw std::runtime_error{"Value not in domain"};
    }
}

const AnyType &Valuation::getValue(const Variable &v) const
{   
    return m_map.at(v);
}
