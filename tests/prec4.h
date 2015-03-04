/* BEGIN HEADER */
#ifndef prec4_INCLUDE_
#define prec4_INCLUDE_

#include <assert.h>
#include <unordered_map>
#include <utility>

#include "classp.h"

// Include files generated by bison
#include "prec4.yacc.hh"
#include "location.hh"
#include "position.hh"

namespace prec4 {
using std::istream;
using std::ostream;
using classp::classpPrint;
using classp::classpFormat;
using classp::AttributeMap;

// Location and state information from the parser.
typedef location ParseState;

class AstNode;
/* BEGIN FORWARD DECLARATIONS */
class Expression;
class IntegerLiteral;
class Product;
class Sum;
/* END FORWARD DECLARATIONS */

// Base class for prec4 AST nodes
class AstNode : public classp::ClasspNode {
 public:
  string className() override { return "AstNode"; }
  AstNode(ParseState parseState)
    : parseState(parseState) {
    }

  // Write out a bracketed form of this AST from the declared syntax.
  virtual void bracketFormat(std::ostream& out, AstNode* self) {
    assert(false);
  }

  ParseState parseState;
};

/* BEGIN CLASS DEFINITIONS */
class Expression: public AstNode {
 public:
  string className() override { return "Expression"; }
  Expression(ParseState parseState);
  static Expression* parse(istream& input, ostream& errors);
  void printMembers(ostream& out) override;
  void bracketFormat(ostream& out, AstNode* self) override;

};

class Sum: public Expression {
 public:
  string className() override { return "Sum"; }
  Sum(ParseState parseState, Expression* val1, Expression* val2);
  void printMembers(ostream& out) override;
  void format(ostream& out, int precedence) override;

  Expression* val1 = nullptr;
  Expression* val2 = nullptr;
};

class Product: public Expression {
 public:
  string className() override { return "Product"; }
  Product(ParseState parseState, Expression* val1, Expression* val2);
  void printMembers(ostream& out) override;
  void format(ostream& out, int precedence) override;

  Expression* val1 = nullptr;
  Expression* val2 = nullptr;
};

class IntegerLiteral: public Expression {
 public:
  string className() override { return "IntegerLiteral"; }
  IntegerLiteral(ParseState parseState);
  void printMembers(ostream& out) override;
  void format(ostream& out, int precedence) override;

};
/* END CLASS DEFINITIONS */

}  // namespace prec4
#endif // prec4_INCLUDE_

/* END HEADER */
