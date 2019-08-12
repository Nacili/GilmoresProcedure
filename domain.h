#ifndef DOMAIN_H
#define DOMAIN_H

#include "common.h"

#include <unordered_map>
#include <set>
#include <memory>
#include <vector>

class BaseDomain
{
public:
    virtual ~BaseDomain();
    
    virtual void insert(const AnyType &val) = 0;
    
    virtual bool hasValue(const AnyType &val) const = 0;
    
    virtual std::vector<AnyType> getValues() const = 0;
};

template <typename ValueType>
class DomainSpecialization : public BaseDomain
{
public:
    DomainSpecialization();
    
    virtual void insert(const AnyType &val);
    
    virtual bool hasValue(const AnyType &val) const;
    
    virtual std::vector<AnyType> getValues() const;
private:
    std::set<ValueType> m_values;
};

template <typename ValueType>
DomainSpecialization<ValueType>::DomainSpecialization()
    : BaseDomain ()
{
}

template <typename ValueType>
void DomainSpecialization<ValueType>::insert(const AnyType &val)
{
    m_values.insert(AnyTypeToType(ValueType, val));
}

template <typename ValueType>
bool DomainSpecialization<ValueType>::hasValue(const AnyType &val) const
{
    auto it = m_values.find(AnyTypeToType(ValueType, val));
    return it != m_values.cend();
}

template <typename ValueType>
std::vector<AnyType> DomainSpecialization<ValueType>::getValues() const
{
    std::vector<AnyType> allValues;
    allValues.reserve(m_values.size());
    for (const ValueType &val : m_values)
    {
        allValues.emplace_back(val);
    }
    return allValues;
}

using Domain = std::shared_ptr<BaseDomain>;

#endif // DOMAIN_H
