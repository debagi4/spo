
#include <string>
#include <vector>


// Generated from grammar/Bagi.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "BagiListener.h"


/**
 * This class provides an empty implementation of BagiListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  BagiBaseListener : public BagiListener {
public:

  virtual void enterSource(BagiParser::SourceContext * /*ctx*/) override { }
  virtual void exitSource(BagiParser::SourceContext * /*ctx*/) override { }

  virtual void enterSourceItem(BagiParser::SourceItemContext * /*ctx*/) override { }
  virtual void exitSourceItem(BagiParser::SourceItemContext * /*ctx*/) override { }

  virtual void enterFuncDef(BagiParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(BagiParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncSignature(BagiParser::FuncSignatureContext * /*ctx*/) override { }
  virtual void exitFuncSignature(BagiParser::FuncSignatureContext * /*ctx*/) override { }

  virtual void enterArgDefList(BagiParser::ArgDefListContext * /*ctx*/) override { }
  virtual void exitArgDefList(BagiParser::ArgDefListContext * /*ctx*/) override { }

  virtual void enterArgDef(BagiParser::ArgDefContext * /*ctx*/) override { }
  virtual void exitArgDef(BagiParser::ArgDefContext * /*ctx*/) override { }

  virtual void enterTypeRef(BagiParser::TypeRefContext * /*ctx*/) override { }
  virtual void exitTypeRef(BagiParser::TypeRefContext * /*ctx*/) override { }

  virtual void enterBaseType(BagiParser::BaseTypeContext * /*ctx*/) override { }
  virtual void exitBaseType(BagiParser::BaseTypeContext * /*ctx*/) override { }

  virtual void enterBuiltinType(BagiParser::BuiltinTypeContext * /*ctx*/) override { }
  virtual void exitBuiltinType(BagiParser::BuiltinTypeContext * /*ctx*/) override { }

  virtual void enterCustomType(BagiParser::CustomTypeContext * /*ctx*/) override { }
  virtual void exitCustomType(BagiParser::CustomTypeContext * /*ctx*/) override { }

  virtual void enterArraySuffix(BagiParser::ArraySuffixContext * /*ctx*/) override { }
  virtual void exitArraySuffix(BagiParser::ArraySuffixContext * /*ctx*/) override { }

  virtual void enterStatement(BagiParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(BagiParser::StatementContext * /*ctx*/) override { }

  virtual void enterVarDecl(BagiParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(BagiParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterVarList(BagiParser::VarListContext * /*ctx*/) override { }
  virtual void exitVarList(BagiParser::VarListContext * /*ctx*/) override { }

  virtual void enterVarItem(BagiParser::VarItemContext * /*ctx*/) override { }
  virtual void exitVarItem(BagiParser::VarItemContext * /*ctx*/) override { }

  virtual void enterIfStatement(BagiParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(BagiParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterBlock(BagiParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(BagiParser::BlockContext * /*ctx*/) override { }

  virtual void enterWhileStatement(BagiParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(BagiParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterDoWhileStatement(BagiParser::DoWhileStatementContext * /*ctx*/) override { }
  virtual void exitDoWhileStatement(BagiParser::DoWhileStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(BagiParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(BagiParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(BagiParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(BagiParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterExprStatement(BagiParser::ExprStatementContext * /*ctx*/) override { }
  virtual void exitExprStatement(BagiParser::ExprStatementContext * /*ctx*/) override { }

  virtual void enterAddSubExpr(BagiParser::AddSubExprContext * /*ctx*/) override { }
  virtual void exitAddSubExpr(BagiParser::AddSubExprContext * /*ctx*/) override { }

  virtual void enterOrExpr(BagiParser::OrExprContext * /*ctx*/) override { }
  virtual void exitOrExpr(BagiParser::OrExprContext * /*ctx*/) override { }

  virtual void enterParensExpr(BagiParser::ParensExprContext * /*ctx*/) override { }
  virtual void exitParensExpr(BagiParser::ParensExprContext * /*ctx*/) override { }

  virtual void enterBitXorExpr(BagiParser::BitXorExprContext * /*ctx*/) override { }
  virtual void exitBitXorExpr(BagiParser::BitXorExprContext * /*ctx*/) override { }

  virtual void enterIndexerExpr(BagiParser::IndexerExprContext * /*ctx*/) override { }
  virtual void exitIndexerExpr(BagiParser::IndexerExprContext * /*ctx*/) override { }

  virtual void enterCmpExpr(BagiParser::CmpExprContext * /*ctx*/) override { }
  virtual void exitCmpExpr(BagiParser::CmpExprContext * /*ctx*/) override { }

  virtual void enterShiftExpr(BagiParser::ShiftExprContext * /*ctx*/) override { }
  virtual void exitShiftExpr(BagiParser::ShiftExprContext * /*ctx*/) override { }

  virtual void enterPlaceExpr(BagiParser::PlaceExprContext * /*ctx*/) override { }
  virtual void exitPlaceExpr(BagiParser::PlaceExprContext * /*ctx*/) override { }

  virtual void enterBitOrExpr(BagiParser::BitOrExprContext * /*ctx*/) override { }
  virtual void exitBitOrExpr(BagiParser::BitOrExprContext * /*ctx*/) override { }

  virtual void enterEqExpr(BagiParser::EqExprContext * /*ctx*/) override { }
  virtual void exitEqExpr(BagiParser::EqExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(BagiParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(BagiParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterLiteralExpr(BagiParser::LiteralExprContext * /*ctx*/) override { }
  virtual void exitLiteralExpr(BagiParser::LiteralExprContext * /*ctx*/) override { }

  virtual void enterBitAndExpr(BagiParser::BitAndExprContext * /*ctx*/) override { }
  virtual void exitBitAndExpr(BagiParser::BitAndExprContext * /*ctx*/) override { }

  virtual void enterCallExpr(BagiParser::CallExprContext * /*ctx*/) override { }
  virtual void exitCallExpr(BagiParser::CallExprContext * /*ctx*/) override { }

  virtual void enterAssignExpr(BagiParser::AssignExprContext * /*ctx*/) override { }
  virtual void exitAssignExpr(BagiParser::AssignExprContext * /*ctx*/) override { }

  virtual void enterMulDivExpr(BagiParser::MulDivExprContext * /*ctx*/) override { }
  virtual void exitMulDivExpr(BagiParser::MulDivExprContext * /*ctx*/) override { }

  virtual void enterAndExpr(BagiParser::AndExprContext * /*ctx*/) override { }
  virtual void exitAndExpr(BagiParser::AndExprContext * /*ctx*/) override { }

  virtual void enterAssignOp(BagiParser::AssignOpContext * /*ctx*/) override { }
  virtual void exitAssignOp(BagiParser::AssignOpContext * /*ctx*/) override { }

  virtual void enterUnOp(BagiParser::UnOpContext * /*ctx*/) override { }
  virtual void exitUnOp(BagiParser::UnOpContext * /*ctx*/) override { }

  virtual void enterExprList(BagiParser::ExprListContext * /*ctx*/) override { }
  virtual void exitExprList(BagiParser::ExprListContext * /*ctx*/) override { }

  virtual void enterLiteral(BagiParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(BagiParser::LiteralContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

