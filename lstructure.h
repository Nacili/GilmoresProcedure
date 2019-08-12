#ifndef LSTRUCTURE_H
#define LSTRUCTURE_H

#include "common.h"
#include "signature.h"
#include "domain.h"

#include <vector>
#include <memory>
#include <unordered_map>

class BaseFunction
{
public:
  BaseFunction(Arity arity);
  
  inline Arity getArity() const { return m_arity; }
  
  virtual AnyType eval(const std::vector<AnyType> &args) const = 0;
  
  virtual ~BaseFunction();
private:
  Arity m_arity;
};

class BaseRelation
{
public:
  BaseRelation(Arity arity);
  
  inline Arity getArity() const { return m_arity; }
  
  virtual bool eval(const std::vector<AnyType> &args) const = 0;
  
  virtual ~BaseRelation();
private:
  Arity m_arity;
};

using Function = std::shared_ptr<BaseFunction>;
using Relation = std::shared_ptr<BaseRelation>;

class LStructure
{
public:
  using FuncMap = std::unordered_map<FunctionSymbol, Function>;
  using RelMap = std::unordered_map<RelationSymbol, Relation>;
public:
    LStructure(Signature::Sptr signature, const Domain &d);
    
    inline const Domain& getDomain() const { return m_domain; }
    
    void addFunction(const FunctionSymbol &symbol, const Function &f);
    void addRelation(const RelationSymbol &symbol, const Relation &r);
    
    const Function& getFunction(const FunctionSymbol &symbol) const;
    const Relation& getRelation(const RelationSymbol &symbol) const;
private:
    Signature::Sptr m_signature;
    Domain m_domain;
    FuncMap m_fmap;
    RelMap m_rmap;
};

#endif // LSTRUCTURE_H
