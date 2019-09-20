#include "common.h"
#include "first_order_logic.h"
#include "gilmore.h"
#include "herbrand.h"

#include <iostream>

using namespace std;

int main()
{
    Signature::Sptr s = std::make_shared<Signature>();
    s->addPredicateSymbol("p", 2);
    Term x = std::make_shared<VariableTerm>("x");
    Term y = std::make_shared<VariableTerm>("y");

    Formula A = std::make_shared<Exists>("x",
                                         std::make_shared<Forall>("y", std::make_shared<Atom>(s, "p", std::vector<Term>{x, y})));

    Formula B = std::make_shared<Forall>("y",
                                         std::make_shared<Exists>("x", std::make_shared<Atom>(s, "p", std::vector<Term>{x, y})));


    Formula C = std::make_shared<Imp>(A, B);

//    C = C->nnf();
//    C = C->prenex();
//    C->skolem(s);
//    std::cout << C->pullQuantifiers() << std::endl;

    prove(s, C);

    return 0;

}
