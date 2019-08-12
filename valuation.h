#ifndef BASEVALUATION_H
#define BASEVALUATION_H

#include "common.h"
#include "domain.h"

#include <unordered_map>

class Valuation
{
public:
  using Map = std::unordered_map<Variable, AnyType>;
  
public:
  Valuation(const Domain &d);
  
  void setValue(const Variable &v, const AnyType &val);
  
  const AnyType& getValue(const Variable &v) const;
private:
  Domain m_domain;
  Map m_map;
};

#endif // BASEVALUATION_H
