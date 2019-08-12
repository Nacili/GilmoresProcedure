#include "first_order_logic.h"

#include <iostream>

using namespace std;

class Zero : public BaseFunction
{
public:
    Zero()
        : BaseFunction(0)
    {}
    
    AnyType eval(const std::vector<AnyType> &args) const
    {
        UNUSED_ARG(args);
        return 0;
    }
};

class One : public BaseFunction
{
public:
    One()
        : BaseFunction(0)
    {}
    
    AnyType eval(const std::vector<AnyType> &args) const
    {
        UNUSED_ARG(args);
        return 1;
    }
};

class Even : public BaseRelation
{
public:
    Even()
        : BaseRelation(1)
    {}
    
    bool eval(const std::vector<AnyType> &args) const
    {
      if (args.size() != getArity())
      {
          throw std::runtime_error{"Wrong number of arguments for Even relation"};
      }
      int val = AnyTypeToType(int, args[0]);
      return !(val % 2);
    }
};

class ModularPlus : public BaseFunction
{
public:
    ModularPlus(int mod)
        : BaseFunction(2), m_mod(mod)
    {}
    
    AnyType eval(const std::vector<AnyType> &args) const
    {
      if (args.size() != getArity())
      {
          throw std::runtime_error{"Wrong number of arguments for Plus relation"};
      }
      int op1 = AnyTypeToType(int, args[0]);
      int op2 = AnyTypeToType(int, args[1]);
      return (op1 + op2) % m_mod;
    }
private:
    int m_mod;
};

int main()
{
    /* Definisemo strukturu */
    Signature::Sptr s = std::make_shared<Signature>();
    
    /* Dodajemo funkcijske i predikatske simbole */
    s->addFunctionSymbol("0", 0);
    s->addFunctionSymbol("1", 0);
    s->addFunctionSymbol("+", 2);
    s->addFunctionSymbol("*", 2);
    s->addPredicateSymbol("even", 1);
    s->addPredicateSymbol("odd", 1);
    s->addPredicateSymbol("=", 2);
    s->addPredicateSymbol("<=", 2);
    
    
    /* Primeri termova i formula */
    
    Term t0 = make_shared<FunctionTerm>(s, "0");
    Term t1 = make_shared<FunctionTerm>(s, "1");
    
    Formula f0 = make_shared<Atom>(s, "even", vector<Term> { t0 });
    
    cout << f0 << endl;
    
    Formula f1 = make_shared<Atom>(s, "even", vector<Term> { t1 });
    
    cout << f1 << endl;
    
    Term tx = make_shared<VariableTerm>("x");
    Term ty = make_shared<VariableTerm>("y");
    
    Term xpy = make_shared<FunctionTerm>(s, "+", vector<Term> {tx, ty});
    
    Formula xeven = make_shared<Atom>(s, "even", vector<Term> { tx });
    
    Formula yeven = make_shared<Atom>(s, "even", vector<Term> { ty });
    
    Formula xpyeven = make_shared<Atom>(s, "even", vector<Term> { xpy });
    
    cout << xpyeven << endl;
    
    Formula xandy = make_shared<And>(xeven, yeven);
    Formula imp = make_shared<Imp>(xandy, xpyeven);
    
    Formula forall_x = make_shared<Forall>("x", imp);
    Formula forall_y = make_shared<Forall>("y", forall_x);
    
    cout << forall_y << endl;
    
    /* Semantika */
    Domain idomain = std::make_shared<DomainSpecialization<int>>();
    idomain->insert(0);
    idomain->insert(1);
    idomain->insert(2);
    idomain->insert(3);
    idomain->insert(4);
    idomain->insert(5);
    idomain->insert(6);
    idomain->insert(7);
    LStructure structure{s, idomain};
    structure.addFunction("+", std::make_shared<ModularPlus>(8));
    structure.addFunction("0", std::make_shared<Zero>());
    structure.addFunction("1", std::make_shared<One>());
    structure.addRelation("even", std::make_shared<Even>());
    Valuation v{idomain};
    v.setValue("x", 0);
    v.setValue("y", 0);
    
    std::cout << std::boolalpha << f0->eval(structure, v) << '\n';
    std::cout << f1->eval(structure, v) << '\n';
    std::cout << xpyeven->eval(structure, v) << '\n';
    std::cout << forall_y->eval(structure, v) << '\n';
    
    /* Prenex */
    Formula f = make_shared<Imp>(make_shared<Or>(make_shared<Exists>("x", xeven), 
                             make_shared<Exists>("x", make_shared<Atom>(s, "odd", vector<Term>{ tx }))),
                     make_shared<Forall>("x", make_shared<Or>(xeven, 
                                      make_shared<Forall>("y", make_shared<Exists>("x", make_shared<Atom>(s, "odd", vector<Term>{ xpy }))))));
    cout << "original formula:\n";
    cout << f << "\nsimplify:\n";
    Formula fs = f->simplify();
    cout << fs << "\nnnf:\n";
    Formula fnnf = fs->nnf();
    cout << fnnf << "\nprenex:\n";
    Formula fprenex = fnnf->prenex();
    cout << fprenex << "\nskolem:\n";
    cout << fprenex->skolem(s) << '\n';
    return 0;
}
