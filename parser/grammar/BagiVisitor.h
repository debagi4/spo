
#include <string>
#include <vector>


// Generated from grammar/Bagi.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "BagiParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by BagiParser.
 */
class  BagiVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by BagiParser.
   */
    virtual std::any visitSource(BagiParser::SourceContext *context) = 0;

    virtual std::any visitSourceItem(BagiParser::SourceItemContext *context) = 0;

    virtual std::any visitFuncDef(BagiParser::FuncDefContext *context) = 0;

    virtual std::any visitFuncSignature(BagiParser::FuncSignatureContext *context) = 0;

    virtual std::any visitArgDefList(BagiParser::ArgDefListContext *context) = 0;

    virtual std::any visitArgDef(BagiParser::ArgDefContext *context) = 0;

    virtual std::any visitTypeRef(BagiParser::TypeRefContext *context) = 0;

    virtual std::any visitBaseType(BagiParser::BaseTypeContext *context) = 0;

    virtual std::any visitBuiltinType(BagiParser::BuiltinTypeContext *context) = 0;

    virtual std::any visitCustomType(BagiParser::CustomTypeContext *context) = 0;

    virtual std::any visitArraySuffix(BagiParser::ArraySuffixContext *context) = 0;

    virtual std::any visitStatement(BagiParser::StatementContext *context) = 0;

    virtual std::any visitVarDecl(BagiParser::VarDeclContext *context) = 0;

    virtual std::any visitVarList(BagiParser::VarListContext *context) = 0;

    virtual std::any visitVarItem(BagiParser::VarItemContext *context) = 0;

    virtual std::any visitIfStatement(BagiParser::IfStatementContext *context) = 0;

    virtual std::any visitBlock(BagiParser::BlockContext *context) = 0;

    virtual std::any visitWhileStatement(BagiParser::WhileStatementContext *context) = 0;

    virtual std::any visitDoWhileStatement(BagiParser::DoWhileStatementContext *context) = 0;

    virtual std::any visitBreakStatement(BagiParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(BagiParser::ContinueStatementContext *context) = 0;

    virtual std::any visitExprStatement(BagiParser::ExprStatementContext *context) = 0;

    virtual std::any visitAddSubExpr(BagiParser::AddSubExprContext *context) = 0;

    virtual std::any visitOrExpr(BagiParser::OrExprContext *context) = 0;

    virtual std::any visitParensExpr(BagiParser::ParensExprContext *context) = 0;

    virtual std::any visitBitXorExpr(BagiParser::BitXorExprContext *context) = 0;

    virtual std::any visitIndexerExpr(BagiParser::IndexerExprContext *context) = 0;

    virtual std::any visitCmpExpr(BagiParser::CmpExprContext *context) = 0;

    virtual std::any visitShiftExpr(BagiParser::ShiftExprContext *context) = 0;

    virtual std::any visitPlaceExpr(BagiParser::PlaceExprContext *context) = 0;

    virtual std::any visitBitOrExpr(BagiParser::BitOrExprContext *context) = 0;

    virtual std::any visitEqExpr(BagiParser::EqExprContext *context) = 0;

    virtual std::any visitUnaryExpr(BagiParser::UnaryExprContext *context) = 0;

    virtual std::any visitLiteralExpr(BagiParser::LiteralExprContext *context) = 0;

    virtual std::any visitBitAndExpr(BagiParser::BitAndExprContext *context) = 0;

    virtual std::any visitCallExpr(BagiParser::CallExprContext *context) = 0;

    virtual std::any visitAssignExpr(BagiParser::AssignExprContext *context) = 0;

    virtual std::any visitMulDivExpr(BagiParser::MulDivExprContext *context) = 0;

    virtual std::any visitAndExpr(BagiParser::AndExprContext *context) = 0;

    virtual std::any visitAssignOp(BagiParser::AssignOpContext *context) = 0;

    virtual std::any visitUnOp(BagiParser::UnOpContext *context) = 0;

    virtual std::any visitExprList(BagiParser::ExprListContext *context) = 0;

    virtual std::any visitLiteral(BagiParser::LiteralContext *context) = 0;


};

