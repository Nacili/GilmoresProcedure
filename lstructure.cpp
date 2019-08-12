#include "lstructure.h"

BaseFunction::BaseFunction(Arity arity)
  : m_arity(arity)
{
}

BaseFunction::~BaseFunction()
{ 
}

BaseRelation::BaseRelation(Arity arity)
  : m_arity(arity)
{ 
}

BaseRelation::~BaseRelation()
{
}

LStructure::LStructure(Signature::Sptr signature, const Domain &d)
  : m_signature(signature), m_domain(d)
{
}

void LStructure::addFunction(const FunctionSymbol &symbol, const Function &f)
{
  if (m_signature->hasFunctionSymbol(symbol, f->getArity()))
  {
    m_fmap[symbol] = f;
  }
  else
  {
    throw std::runtime_error{"Function symbol or arity missmatch (not present in Signature)"};
  }
}

void LStructure::addRelation(const RelationSymbol &symbol, const Relation &r)
{
  if (m_signature->hasPredicateSymbol(symbol, r->getArity()))
  {
    m_rmap[symbol] = r;
  }
  else
  {
    throw std::runtime_error{"Relation symbol or arity missmatch (not present in Signature)"};
  }
}

const Function &LStructure::getFunction(const FunctionSymbol &symbol) const
{
  return m_fmap.at(symbol);
}

const Relation &LStructure::getRelation(const RelationSymbol &symbol) const
{
  return m_rmap.at(symbol);
}
