
#include <string>
#include <vector>


// Generated from grammar/Bagi.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "BagiParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by BagiParser.
 */
class  BagiListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSource(BagiParser::SourceContext *ctx) = 0;
  virtual void exitSource(BagiParser::SourceContext *ctx) = 0;

  virtual void enterSourceItem(BagiParser::SourceItemContext *ctx) = 0;
  virtual void exitSourceItem(BagiParser::SourceItemContext *ctx) = 0;

  virtual void enterFuncDef(BagiParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(BagiParser::FuncDefContext *ctx) = 0;

  virtual void enterFuncSignature(BagiParser::FuncSignatureContext *ctx) = 0;
  virtual void exitFuncSignature(BagiParser::FuncSignatureContext *ctx) = 0;

  virtual void enterArgDefList(BagiParser::ArgDefListContext *ctx) = 0;
  virtual void exitArgDefList(BagiParser::ArgDefListContext *ctx) = 0;

  virtual void enterArgDef(BagiParser::ArgDefContext *ctx) = 0;
  virtual void exitArgDef(BagiParser::ArgDefContext *ctx) = 0;

  virtual void enterTypeRef(BagiParser::TypeRefContext *ctx) = 0;
  virtual void exitTypeRef(BagiParser::TypeRefContext *ctx) = 0;

  virtual void enterBaseType(BagiParser::BaseTypeContext *ctx) = 0;
  virtual void exitBaseType(BagiParser::BaseTypeContext *ctx) = 0;

  virtual void enterBuiltinType(BagiParser::BuiltinTypeContext *ctx) = 0;
  virtual void exitBuiltinType(BagiParser::BuiltinTypeContext *ctx) = 0;

  virtual void enterCustomType(BagiParser::CustomTypeContext *ctx) = 0;
  virtual void exitCustomType(BagiParser::CustomTypeContext *ctx) = 0;

  virtual void enterArraySuffix(BagiParser::ArraySuffixContext *ctx) = 0;
  virtual void exitArraySuffix(BagiParser::ArraySuffixContext *ctx) = 0;

  virtual void enterStatement(BagiParser::StatementContext *ctx) = 0;
  virtual void exitStatement(BagiParser::StatementContext *ctx) = 0;

  virtual void enterVarDecl(BagiParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(BagiParser::VarDeclContext *ctx) = 0;

  virtual void enterVarList(BagiParser::VarListContext *ctx) = 0;
  virtual void exitVarList(BagiParser::VarListContext *ctx) = 0;

  virtual void enterVarItem(BagiParser::VarItemContext *ctx) = 0;
  virtual void exitVarItem(BagiParser::VarItemContext *ctx) = 0;

  virtual void enterIfStatement(BagiParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(BagiParser::IfStatementContext *ctx) = 0;

  virtual void enterBlock(BagiParser::BlockContext *ctx) = 0;
  virtual void exitBlock(BagiParser::BlockContext *ctx) = 0;

  virtual void enterWhileStatement(BagiParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(BagiParser::WhileStatementContext *ctx) = 0;

  virtual void enterDoWhileStatement(BagiParser::DoWhileStatementContext *ctx) = 0;
  virtual void exitDoWhileStatement(BagiParser::DoWhileStatementContext *ctx) = 0;

  virtual void enterBreakStatement(BagiParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(BagiParser::BreakStatementContext *ctx) = 0;

  virtual void enterContinueStatement(BagiParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(BagiParser::ContinueStatementContext *ctx) = 0;

  virtual void enterExprStatement(BagiParser::ExprStatementContext *ctx) = 0;
  virtual void exitExprStatement(BagiParser::ExprStatementContext *ctx) = 0;

  virtual void enterAddSubExpr(BagiParser::AddSubExprContext *ctx) = 0;
  virtual void exitAddSubExpr(BagiParser::AddSubExprContext *ctx) = 0;

  virtual void enterOrExpr(BagiParser::OrExprContext *ctx) = 0;
  virtual void exitOrExpr(BagiParser::OrExprContext *ctx) = 0;

  virtual void enterParensExpr(BagiParser::ParensExprContext *ctx) = 0;
  virtual void exitParensExpr(BagiParser::ParensExprContext *ctx) = 0;

  virtual void enterBitXorExpr(BagiParser::BitXorExprContext *ctx) = 0;
  virtual void exitBitXorExpr(BagiParser::BitXorExprContext *ctx) = 0;

  virtual void enterIndexerExpr(BagiParser::IndexerExprContext *ctx) = 0;
  virtual void exitIndexerExpr(BagiParser::IndexerExprContext *ctx) = 0;

  virtual void enterCmpExpr(BagiParser::CmpExprContext *ctx) = 0;
  virtual void exitCmpExpr(BagiParser::CmpExprContext *ctx) = 0;

  virtual void enterShiftExpr(BagiParser::ShiftExprContext *ctx) = 0;
  virtual void exitShiftExpr(BagiParser::ShiftExprContext *ctx) = 0;

  virtual void enterPlaceExpr(BagiParser::PlaceExprContext *ctx) = 0;
  virtual void exitPlaceExpr(BagiParser::PlaceExprContext *ctx) = 0;

  virtual void enterBitOrExpr(BagiParser::BitOrExprContext *ctx) = 0;
  virtual void exitBitOrExpr(BagiParser::BitOrExprContext *ctx) = 0;

  virtual void enterEqExpr(BagiParser::EqExprContext *ctx) = 0;
  virtual void exitEqExpr(BagiParser::EqExprContext *ctx) = 0;

  virtual void enterUnaryExpr(BagiParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(BagiParser::UnaryExprContext *ctx) = 0;

  virtual void enterLiteralExpr(BagiParser::LiteralExprContext *ctx) = 0;
  virtual void exitLiteralExpr(BagiParser::LiteralExprContext *ctx) = 0;

  virtual void enterBitAndExpr(BagiParser::BitAndExprContext *ctx) = 0;
  virtual void exitBitAndExpr(BagiParser::BitAndExprContext *ctx) = 0;

  virtual void enterCallExpr(BagiParser::CallExprContext *ctx) = 0;
  virtual void exitCallExpr(BagiParser::CallExprContext *ctx) = 0;

  virtual void enterAssignExpr(BagiParser::AssignExprContext *ctx) = 0;
  virtual void exitAssignExpr(BagiParser::AssignExprContext *ctx) = 0;

  virtual void enterMulDivExpr(BagiParser::MulDivExprContext *ctx) = 0;
  virtual void exitMulDivExpr(BagiParser::MulDivExprContext *ctx) = 0;

  virtual void enterAndExpr(BagiParser::AndExprContext *ctx) = 0;
  virtual void exitAndExpr(BagiParser::AndExprContext *ctx) = 0;

  virtual void enterAssignOp(BagiParser::AssignOpContext *ctx) = 0;
  virtual void exitAssignOp(BagiParser::AssignOpContext *ctx) = 0;

  virtual void enterUnOp(BagiParser::UnOpContext *ctx) = 0;
  virtual void exitUnOp(BagiParser::UnOpContext *ctx) = 0;

  virtual void enterExprList(BagiParser::ExprListContext *ctx) = 0;
  virtual void exitExprList(BagiParser::ExprListContext *ctx) = 0;

  virtual void enterLiteral(BagiParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(BagiParser::LiteralContext *ctx) = 0;


};

