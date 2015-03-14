/*
 * This file is a part of the Classp parser, formatter, and AST generator.
 * Description: Class LexerBase --the lexer that is passed to the parser.
 *
 * Copyright 2015 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef LEXER_BASE_H_
#define LEXER_BASE_H_

// If this is being included from classp.lex.c, then FlexLexer.h has already been
// included.  Otherwise, we have to include it now.  This is how FlexLexer.h
// says to do things
#ifndef CLASSP_LEX_CC_
#include <FlexLexer.h>
#endif

#include <memory>
#include <string>
#include <stdio.h>

#include "classp.yacc.hh"
#include "parser-base.h"

class classpFlexLexer;

namespace classp {

class NumericValue;
class ParserBase;

class LexerBase : public yyFlexLexer {
 public:
  LexerBase(FILE* source, ParserBase* parser);
  ~LexerBase() override;

  // The actual lexical analyzer, whose implementation is generated by flex.
  virtual yyParser::symbol_type NextToken(ParserBase* parser);

  // The error reporting routines.
  void LexerError(const char* msg) override;

  // The name of the underlying file, if any.
  const std::string* file_name();

  // Flex doesn't revert the location when calling unput. This function
  // does unput and resets the location endpoint back to what it was before.
  virtual void UnputAndResetLocation(char c);

  // Bison doesn't support multiple start states, so the recommended way to deal
  // with this limitation is to have an initial token that directs to parser to
  // look for a particular nonterminal (see the rules for start in the grammar).
  // This initial token is managed by these two functions: set_initial_token
  // is called to store the initial token in the lexer state, and
  // consume_initial_token is used to retrieve it.  If there is no initial
  // token, consume_initial_token return TOK_EOF.  See classp::class_plex in
  // parser_base.cc for details regarding the handling of the initial token.
  void set_initial_token(yyParser::token_type token) { initial_token_ = token; }

  void consume_initial_token(yyParser::token_type* token) {
    *token = initial_token_;
    initial_token_ = yyParser::token::TOK_EOF;
  }

 protected:
  int LexerInput(char* buf, int max_size) override;
  const yyParser::location_type* location() { return &location_; }

 private:
  ParserBase* const parser_;  // Not owned.
  FILE* source_;  // Not owned.
  std::unique_ptr<std::string> file_name_;
  yyParser::location_type location_;
  yyParser::token_type initial_token_;
  std::stringstream current_token_;  // a string token being built up

  // Disallow copy and assign.
  LexerBase(const LexerBase&) = delete;
  void operator=(const LexerBase&) = delete;
};

}  // namespace classp

#endif  // LEXER_BASE_H_