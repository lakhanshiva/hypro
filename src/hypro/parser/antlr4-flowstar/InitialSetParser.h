
// Generated from InitialSet.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"


	#include <map>
	#include <string>




class  InitialSetParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, IN = 2, PAR = 3, JUMPS = 4, URGENT = 5, GUARD = 6, RESET = 7, 
    PARALLELOTOPE = 8, BOX = 9, JUMP = 10, DEFINE = 11, COMMENT = 12, EQUALS = 13, 
    BOOLRELATION = 14, PLUS = 15, MINUS = 16, TIMES = 17, SBOPEN = 18, SBCLOSE = 19, 
    CBOPEN = 20, CBCLOSE = 21, COMMA = 22, NUMBER = 23, CONSTANT = 24, VARIABLE = 25, 
    WS = 26
  };

  enum {
    RuleInit = 0, RuleInitstate = 1, RuleReplacedexpr = 2, RuleConstantexpr = 3, 
    RuleConnector = 4, RuleTerm = 5, RulePolynom = 6, RuleInterval = 7, 
    RuleEquation = 8, RuleConstraint = 9, RuleIntervalexpr = 10, RuleConstrset = 11
  };

  InitialSetParser(antlr4::TokenStream *input);
  ~InitialSetParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  	inline const std::map<std::string, std::string>& getConstants() const { return constants; }


  class InitContext;
  class InitstateContext;
  class ReplacedexprContext;
  class ConstantexprContext;
  class ConnectorContext;
  class TermContext;
  class PolynomContext;
  class IntervalContext;
  class EquationContext;
  class ConstraintContext;
  class IntervalexprContext;
  class ConstrsetContext; 

  class  InitContext : public antlr4::ParserRuleContext {
  public:
    InitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitstateContext *> initstate();
    InitstateContext* initstate(size_t i);

   
  };

  InitContext* init();

  class  InitstateContext : public antlr4::ParserRuleContext {
  public:
    InitstateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    ConstrsetContext *constrset();

   
  };

  InitstateContext* initstate();

  class  ReplacedexprContext : public antlr4::ParserRuleContext {
  public:
    ReplacedexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    antlr4::tree::TerminalNode *EQUALS();
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

   
  };

  ReplacedexprContext* replacedexpr();

  class  ConstantexprContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *constantToken = nullptr;;
    antlr4::Token *minusToken = nullptr;;
    antlr4::Token *numberToken = nullptr;;
    ConstantexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONSTANT();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *MINUS();

   
  };

  ConstantexprContext* constantexpr();

  class  ConnectorContext : public antlr4::ParserRuleContext {
  public:
    ConnectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

   
  };

  ConnectorContext* connector();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TIMES();
    antlr4::tree::TerminalNode* TIMES(size_t i);
    std::vector<ConnectorContext *> connector();
    ConnectorContext* connector(size_t i);

   
  };

  TermContext* term();

  class  PolynomContext : public antlr4::ParserRuleContext {
  public:
    PolynomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    std::vector<ConnectorContext *> connector();
    ConnectorContext* connector(size_t i);

   
  };

  PolynomContext* polynom();

  class  IntervalContext : public antlr4::ParserRuleContext {
  public:
    IntervalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

   
  };

  IntervalContext* interval();

  class  EquationContext : public antlr4::ParserRuleContext {
  public:
    EquationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUALS();
    PolynomContext *polynom();
    ConnectorContext *connector();
    IntervalContext *interval();

   
  };

  EquationContext* equation();

  class  ConstraintContext : public antlr4::ParserRuleContext {
  public:
    ConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PolynomContext *> polynom();
    PolynomContext* polynom(size_t i);
    antlr4::tree::TerminalNode *BOOLRELATION();
    antlr4::tree::TerminalNode *EQUALS();

   
  };

  ConstraintContext* constraint();

  class  IntervalexprContext : public antlr4::ParserRuleContext {
  public:
    IntervalexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *IN();
    IntervalContext *interval();

   
  };

  IntervalexprContext* intervalexpr();

  class  ConstrsetContext : public antlr4::ParserRuleContext {
  public:
    ConstrsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConstraintContext *> constraint();
    ConstraintContext* constraint(size_t i);
    std::vector<IntervalexprContext *> intervalexpr();
    IntervalexprContext* intervalexpr(size_t i);

   
  };

  ConstrsetContext* constrset();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  	std::map<std::string, std::string> constants;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};
