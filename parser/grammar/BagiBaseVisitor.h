
#include <string>
#include <vector>


// Generated from grammar/Bagi.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "BagiVisitor.h"


/**
 * This class provides an empty implementation of BagiVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  BagiBaseVisitor : public BagiVisitor {
public:

  virtual std::any visitSource(BagiParser::SourceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSourceItem(BagiParser::SourceItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(BagiParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncSignature(BagiParser::FuncSignatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgDefList(BagiParser::ArgDefListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgDef(BagiParser::ArgDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeRef(BagiParser::TypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseType(BagiParser::BaseTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltinType(BagiParser::BuiltinTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomType(BagiParser::CustomTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArraySuffix(BagiParser::ArraySuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(BagiParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(BagiParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarList(BagiParser::VarListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarItem(BagiParser::VarItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(BagiParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(BagiParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(BagiParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoWhileStatement(BagiParser::DoWhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(BagiParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(BagiParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStatement(BagiParser::ExprStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSubExpr(BagiParser::AddSubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(BagiParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParensExpr(BagiParser::ParensExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitXorExpr(BagiParser::BitXorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexerExpr(BagiParser::IndexerExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCmpExpr(BagiParser::CmpExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftExpr(BagiParser::ShiftExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlaceExpr(BagiParser::PlaceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitOrExpr(BagiParser::BitOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExpr(BagiParser::EqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(BagiParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpr(BagiParser::LiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitAndExpr(BagiParser::BitAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallExpr(BagiParser::CallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignExpr(BagiParser::AssignExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDivExpr(BagiParser::MulDivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(BagiParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignOp(BagiParser::AssignOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnOp(BagiParser::UnOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprList(BagiParser::ExprListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(BagiParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

