/* BEGIN HEADER */
#ifndef t11_INCLUDE_
#define t11_INCLUDE_

#include <assert.h>
#include <unordered_map>
#include <utility>

#include "classp.h"

// Include files generated by bison
#include "t11.yacc.hh"
#include "location.hh"
#include "position.hh"

namespace t11 {
using std::istream;
using std::ostream;
using classp::classpPrint;
using classp::classpFormat;
using classp::AttributeMap;

// Location and state information from the parser.
typedef location ParseState;

class AstNode;
/* BEGIN FORWARD DECLARATIONS */
class A;
/* END FORWARD DECLARATIONS */

// Base class for t11 AST nodes
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
class A: public AstNode {
 public:
  string className() override { return "A"; }
  A(ParseState parseState, AttributeMap& keyword_args);
  static A* parse(istream& input, ostream& errors);
  void printMembers(ostream& out) override;
  void format(ostream& out, int precedence) override;

  bool b;
};
/* END CLASS DEFINITIONS */

}  // namespace t11
#endif // t11_INCLUDE_

/* END HEADER */
