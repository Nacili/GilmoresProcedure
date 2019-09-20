#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "common.h"

#include <unordered_map>
#include <memory>
#include <vector>

class Signature
{
public:
    using Sptr = std::shared_ptr<Signature>;
private:
    using Map = std::unordered_map<std::string, Arity>;
private:
    static unsigned s_UniqueCounter;
public:
    void addFunctionSymbol(const FunctionSymbol &fsym, Arity ar);
    
    void addPredicateSymbol(const RelationSymbol &fsym, Arity ar);
    
    bool hasFunctionSymbol(const FunctionSymbol &fsym, const Arity &ar) const;
    
    bool hasPredicateSymbol(const RelationSymbol &psym, const Arity &ar) const;
    
    FunctionSymbol getUniqueFunctionSymbol() const;

    const size_t MAX_UNIQUE_CTS = 100;
    FunctionSymbol getNewUniqueConstant() const;
private:
    Map m_functions;
    Map m_predicates;
    std::vector<FunctionSymbol> _uniqueConstants;
};

#endif // SIGNATURE_H
