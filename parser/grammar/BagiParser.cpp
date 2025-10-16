
#include <string>
#include <vector>


// Generated from grammar/Bagi.g4 by ANTLR 4.13.2


#include "BagiListener.h"
#include "BagiVisitor.h"

#include "BagiParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct BagiParserStaticData final {
  BagiParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  BagiParserStaticData(const BagiParserStaticData&) = delete;
  BagiParserStaticData(BagiParserStaticData&&) = delete;
  BagiParserStaticData& operator=(const BagiParserStaticData&) = delete;
  BagiParserStaticData& operator=(BagiParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag bagiParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<BagiParserStaticData> bagiParserStaticData = nullptr;

void bagiParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (bagiParserStaticData != nullptr) {
    return;
  }
#else
  assert(bagiParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<BagiParserStaticData>(
    std::vector<std::string>{
      "source", "sourceItem", "funcDef", "funcSignature", "argDefList", 
      "argDef", "typeRef", "baseType", "builtinType", "customType", "arraySuffix", 
      "statement", "varDecl", "varList", "varItem", "ifStatement", "block", 
      "whileStatement", "doWhileStatement", "breakStatement", "continueStatement", 
      "exprStatement", "expr", "assignOp", "unOp", "exprList", "literal"
    },
    std::vector<std::string>{
      "", "';'", "'('", "')'", "','", "'bool'", "'byte'", "'int'", "'uint'", 
      "'long'", "'ulong'", "'char'", "'string'", "'['", "']'", "'='", "'if'", 
      "'else'", "'{'", "'}'", "'while'", "'do'", "'break'", "'continue'", 
      "'||'", "'&&'", "'|'", "'^'", "'&'", "'=='", "'!='", "'<'", "'<='", 
      "'>'", "'>='", "'<<'", "'>>'", "'+'", "'-'", "'*'", "'/'", "'%'", 
      "'+='", "'-='", "'*='", "'/='", "'%='", "'!'", "'~'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "IDENTIFIER", 
      "STRING", "CHAR", "HEX", "BITS", "DEC", "BOOL", "WS", "COMMENT", "MULTICOMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,58,271,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,5,0,56,8,0,10,
  	0,12,0,59,9,0,1,1,1,1,1,2,1,2,1,2,3,2,66,8,2,1,3,3,3,69,8,3,1,3,1,3,1,
  	3,3,3,74,8,3,1,3,1,3,1,4,1,4,1,4,5,4,81,8,4,10,4,12,4,84,9,4,1,5,3,5,
  	87,8,5,1,5,1,5,1,6,1,6,5,6,93,8,6,10,6,12,6,96,9,6,1,7,1,7,3,7,100,8,
  	7,1,8,1,8,1,9,1,9,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,3,11,117,8,11,1,12,3,12,120,8,12,1,12,1,12,1,12,3,12,125,8,12,1,12,
  	1,12,1,12,1,12,3,12,131,8,12,5,12,133,8,12,10,12,12,12,136,9,12,1,12,
  	1,12,1,13,1,13,1,13,5,13,143,8,13,10,13,12,13,146,9,13,1,14,1,14,1,14,
  	3,14,151,8,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,160,8,15,1,16,1,
  	16,5,16,164,8,16,10,16,12,16,167,9,16,1,16,1,16,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,20,1,
  	20,1,20,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,3,22,208,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,243,
  	8,22,1,22,1,22,1,22,1,22,3,22,249,8,22,1,22,5,22,252,8,22,10,22,12,22,
  	255,9,22,1,23,1,23,1,24,1,24,1,25,1,25,1,25,5,25,264,8,25,10,25,12,25,
  	267,9,25,1,26,1,26,1,26,0,1,44,27,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,0,9,1,0,5,12,1,0,29,30,1,0,31,
  	34,1,0,35,36,1,0,37,38,1,0,39,41,2,0,15,15,42,46,2,0,37,38,47,48,1,0,
  	50,55,285,0,57,1,0,0,0,2,60,1,0,0,0,4,62,1,0,0,0,6,68,1,0,0,0,8,77,1,
  	0,0,0,10,86,1,0,0,0,12,90,1,0,0,0,14,99,1,0,0,0,16,101,1,0,0,0,18,103,
  	1,0,0,0,20,105,1,0,0,0,22,116,1,0,0,0,24,119,1,0,0,0,26,139,1,0,0,0,28,
  	147,1,0,0,0,30,152,1,0,0,0,32,161,1,0,0,0,34,170,1,0,0,0,36,176,1,0,0,
  	0,38,184,1,0,0,0,40,187,1,0,0,0,42,190,1,0,0,0,44,207,1,0,0,0,46,256,
  	1,0,0,0,48,258,1,0,0,0,50,260,1,0,0,0,52,268,1,0,0,0,54,56,3,2,1,0,55,
  	54,1,0,0,0,56,59,1,0,0,0,57,55,1,0,0,0,57,58,1,0,0,0,58,1,1,0,0,0,59,
  	57,1,0,0,0,60,61,3,4,2,0,61,3,1,0,0,0,62,65,3,6,3,0,63,66,3,32,16,0,64,
  	66,5,1,0,0,65,63,1,0,0,0,65,64,1,0,0,0,66,5,1,0,0,0,67,69,3,12,6,0,68,
  	67,1,0,0,0,68,69,1,0,0,0,69,70,1,0,0,0,70,71,5,49,0,0,71,73,5,2,0,0,72,
  	74,3,8,4,0,73,72,1,0,0,0,73,74,1,0,0,0,74,75,1,0,0,0,75,76,5,3,0,0,76,
  	7,1,0,0,0,77,82,3,10,5,0,78,79,5,4,0,0,79,81,3,10,5,0,80,78,1,0,0,0,81,
  	84,1,0,0,0,82,80,1,0,0,0,82,83,1,0,0,0,83,9,1,0,0,0,84,82,1,0,0,0,85,
  	87,3,12,6,0,86,85,1,0,0,0,86,87,1,0,0,0,87,88,1,0,0,0,88,89,5,49,0,0,
  	89,11,1,0,0,0,90,94,3,14,7,0,91,93,3,20,10,0,92,91,1,0,0,0,93,96,1,0,
  	0,0,94,92,1,0,0,0,94,95,1,0,0,0,95,13,1,0,0,0,96,94,1,0,0,0,97,100,3,
  	16,8,0,98,100,3,18,9,0,99,97,1,0,0,0,99,98,1,0,0,0,100,15,1,0,0,0,101,
  	102,7,0,0,0,102,17,1,0,0,0,103,104,5,49,0,0,104,19,1,0,0,0,105,106,5,
  	13,0,0,106,107,5,14,0,0,107,21,1,0,0,0,108,117,3,24,12,0,109,117,3,30,
  	15,0,110,117,3,32,16,0,111,117,3,34,17,0,112,117,3,36,18,0,113,117,3,
  	38,19,0,114,117,3,40,20,0,115,117,3,42,21,0,116,108,1,0,0,0,116,109,1,
  	0,0,0,116,110,1,0,0,0,116,111,1,0,0,0,116,112,1,0,0,0,116,113,1,0,0,0,
  	116,114,1,0,0,0,116,115,1,0,0,0,117,23,1,0,0,0,118,120,3,12,6,0,119,118,
  	1,0,0,0,119,120,1,0,0,0,120,121,1,0,0,0,121,124,5,49,0,0,122,123,5,15,
  	0,0,123,125,3,44,22,0,124,122,1,0,0,0,124,125,1,0,0,0,125,134,1,0,0,0,
  	126,127,5,4,0,0,127,130,5,49,0,0,128,129,5,15,0,0,129,131,3,44,22,0,130,
  	128,1,0,0,0,130,131,1,0,0,0,131,133,1,0,0,0,132,126,1,0,0,0,133,136,1,
  	0,0,0,134,132,1,0,0,0,134,135,1,0,0,0,135,137,1,0,0,0,136,134,1,0,0,0,
  	137,138,5,1,0,0,138,25,1,0,0,0,139,144,3,28,14,0,140,141,5,4,0,0,141,
  	143,3,28,14,0,142,140,1,0,0,0,143,146,1,0,0,0,144,142,1,0,0,0,144,145,
  	1,0,0,0,145,27,1,0,0,0,146,144,1,0,0,0,147,150,5,49,0,0,148,149,5,15,
  	0,0,149,151,3,44,22,0,150,148,1,0,0,0,150,151,1,0,0,0,151,29,1,0,0,0,
  	152,153,5,16,0,0,153,154,5,2,0,0,154,155,3,44,22,0,155,156,5,3,0,0,156,
  	159,3,22,11,0,157,158,5,17,0,0,158,160,3,22,11,0,159,157,1,0,0,0,159,
  	160,1,0,0,0,160,31,1,0,0,0,161,165,5,18,0,0,162,164,3,22,11,0,163,162,
  	1,0,0,0,164,167,1,0,0,0,165,163,1,0,0,0,165,166,1,0,0,0,166,168,1,0,0,
  	0,167,165,1,0,0,0,168,169,5,19,0,0,169,33,1,0,0,0,170,171,5,20,0,0,171,
  	172,5,2,0,0,172,173,3,44,22,0,173,174,5,3,0,0,174,175,3,22,11,0,175,35,
  	1,0,0,0,176,177,5,21,0,0,177,178,3,32,16,0,178,179,5,20,0,0,179,180,5,
  	2,0,0,180,181,3,44,22,0,181,182,5,3,0,0,182,183,5,1,0,0,183,37,1,0,0,
  	0,184,185,5,22,0,0,185,186,5,1,0,0,186,39,1,0,0,0,187,188,5,23,0,0,188,
  	189,5,1,0,0,189,41,1,0,0,0,190,191,3,44,22,0,191,192,5,1,0,0,192,43,1,
  	0,0,0,193,194,6,22,-1,0,194,195,5,49,0,0,195,196,3,46,23,0,196,197,3,
  	44,22,7,197,208,1,0,0,0,198,199,3,48,24,0,199,200,3,44,22,6,200,208,1,
  	0,0,0,201,202,5,2,0,0,202,203,3,44,22,0,203,204,5,3,0,0,204,208,1,0,0,
  	0,205,208,5,49,0,0,206,208,3,52,26,0,207,193,1,0,0,0,207,198,1,0,0,0,
  	207,201,1,0,0,0,207,205,1,0,0,0,207,206,1,0,0,0,208,253,1,0,0,0,209,210,
  	10,17,0,0,210,211,5,24,0,0,211,252,3,44,22,18,212,213,10,16,0,0,213,214,
  	5,25,0,0,214,252,3,44,22,17,215,216,10,15,0,0,216,217,5,26,0,0,217,252,
  	3,44,22,16,218,219,10,14,0,0,219,220,5,27,0,0,220,252,3,44,22,15,221,
  	222,10,13,0,0,222,223,5,28,0,0,223,252,3,44,22,14,224,225,10,12,0,0,225,
  	226,7,1,0,0,226,252,3,44,22,13,227,228,10,11,0,0,228,229,7,2,0,0,229,
  	252,3,44,22,12,230,231,10,10,0,0,231,232,7,3,0,0,232,252,3,44,22,11,233,
  	234,10,9,0,0,234,235,7,4,0,0,235,252,3,44,22,10,236,237,10,8,0,0,237,
  	238,7,5,0,0,238,252,3,44,22,9,239,240,10,4,0,0,240,242,5,2,0,0,241,243,
  	3,50,25,0,242,241,1,0,0,0,242,243,1,0,0,0,243,244,1,0,0,0,244,252,5,3,
  	0,0,245,246,10,3,0,0,246,248,5,13,0,0,247,249,3,50,25,0,248,247,1,0,0,
  	0,248,249,1,0,0,0,249,250,1,0,0,0,250,252,5,14,0,0,251,209,1,0,0,0,251,
  	212,1,0,0,0,251,215,1,0,0,0,251,218,1,0,0,0,251,221,1,0,0,0,251,224,1,
  	0,0,0,251,227,1,0,0,0,251,230,1,0,0,0,251,233,1,0,0,0,251,236,1,0,0,0,
  	251,239,1,0,0,0,251,245,1,0,0,0,252,255,1,0,0,0,253,251,1,0,0,0,253,254,
  	1,0,0,0,254,45,1,0,0,0,255,253,1,0,0,0,256,257,7,6,0,0,257,47,1,0,0,0,
  	258,259,7,7,0,0,259,49,1,0,0,0,260,265,3,44,22,0,261,262,5,4,0,0,262,
  	264,3,44,22,0,263,261,1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,266,
  	1,0,0,0,266,51,1,0,0,0,267,265,1,0,0,0,268,269,7,8,0,0,269,53,1,0,0,0,
  	23,57,65,68,73,82,86,94,99,116,119,124,130,134,144,150,159,165,207,242,
  	248,251,253,265
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  bagiParserStaticData = std::move(staticData);
}

}

BagiParser::BagiParser(TokenStream *input) : BagiParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

BagiParser::BagiParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  BagiParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *bagiParserStaticData->atn, bagiParserStaticData->decisionToDFA, bagiParserStaticData->sharedContextCache, options);
}

BagiParser::~BagiParser() {
  delete _interpreter;
}

const atn::ATN& BagiParser::getATN() const {
  return *bagiParserStaticData->atn;
}

std::string BagiParser::getGrammarFileName() const {
  return "Bagi.g4";
}

const std::vector<std::string>& BagiParser::getRuleNames() const {
  return bagiParserStaticData->ruleNames;
}

const dfa::Vocabulary& BagiParser::getVocabulary() const {
  return bagiParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView BagiParser::getSerializedATN() const {
  return bagiParserStaticData->serializedATN;
}


//----------------- SourceContext ------------------------------------------------------------------

BagiParser::SourceContext::SourceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BagiParser::SourceItemContext *> BagiParser::SourceContext::sourceItem() {
  return getRuleContexts<BagiParser::SourceItemContext>();
}

BagiParser::SourceItemContext* BagiParser::SourceContext::sourceItem(size_t i) {
  return getRuleContext<BagiParser::SourceItemContext>(i);
}


size_t BagiParser::SourceContext::getRuleIndex() const {
  return BagiParser::RuleSource;
}

void BagiParser::SourceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSource(this);
}

void BagiParser::SourceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSource(this);
}


std::any BagiParser::SourceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitSource(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::SourceContext* BagiParser::source() {
  SourceContext *_localctx = _tracker.createInstance<SourceContext>(_ctx, getState());
  enterRule(_localctx, 0, BagiParser::RuleSource);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 562949953429472) != 0)) {
      setState(54);
      sourceItem();
      setState(59);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceItemContext ------------------------------------------------------------------

BagiParser::SourceItemContext::SourceItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::FuncDefContext* BagiParser::SourceItemContext::funcDef() {
  return getRuleContext<BagiParser::FuncDefContext>(0);
}


size_t BagiParser::SourceItemContext::getRuleIndex() const {
  return BagiParser::RuleSourceItem;
}

void BagiParser::SourceItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceItem(this);
}

void BagiParser::SourceItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceItem(this);
}


std::any BagiParser::SourceItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitSourceItem(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::SourceItemContext* BagiParser::sourceItem() {
  SourceItemContext *_localctx = _tracker.createInstance<SourceItemContext>(_ctx, getState());
  enterRule(_localctx, 2, BagiParser::RuleSourceItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    funcDef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

BagiParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::FuncSignatureContext* BagiParser::FuncDefContext::funcSignature() {
  return getRuleContext<BagiParser::FuncSignatureContext>(0);
}

BagiParser::BlockContext* BagiParser::FuncDefContext::block() {
  return getRuleContext<BagiParser::BlockContext>(0);
}


size_t BagiParser::FuncDefContext::getRuleIndex() const {
  return BagiParser::RuleFuncDef;
}

void BagiParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void BagiParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


std::any BagiParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::FuncDefContext* BagiParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 4, BagiParser::RuleFuncDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    funcSignature();
    setState(65);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BagiParser::T__17: {
        setState(63);
        block();
        break;
      }

      case BagiParser::T__0: {
        setState(64);
        match(BagiParser::T__0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncSignatureContext ------------------------------------------------------------------

BagiParser::FuncSignatureContext::FuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BagiParser::FuncSignatureContext::IDENTIFIER() {
  return getToken(BagiParser::IDENTIFIER, 0);
}

BagiParser::TypeRefContext* BagiParser::FuncSignatureContext::typeRef() {
  return getRuleContext<BagiParser::TypeRefContext>(0);
}

BagiParser::ArgDefListContext* BagiParser::FuncSignatureContext::argDefList() {
  return getRuleContext<BagiParser::ArgDefListContext>(0);
}


size_t BagiParser::FuncSignatureContext::getRuleIndex() const {
  return BagiParser::RuleFuncSignature;
}

void BagiParser::FuncSignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncSignature(this);
}

void BagiParser::FuncSignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncSignature(this);
}


std::any BagiParser::FuncSignatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitFuncSignature(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::FuncSignatureContext* BagiParser::funcSignature() {
  FuncSignatureContext *_localctx = _tracker.createInstance<FuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 6, BagiParser::RuleFuncSignature);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(67);
      typeRef();
      break;
    }

    default:
      break;
    }
    setState(70);
    match(BagiParser::IDENTIFIER);
    setState(71);
    match(BagiParser::T__1);
    setState(73);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 562949953429472) != 0)) {
      setState(72);
      argDefList();
    }
    setState(75);
    match(BagiParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgDefListContext ------------------------------------------------------------------

BagiParser::ArgDefListContext::ArgDefListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BagiParser::ArgDefContext *> BagiParser::ArgDefListContext::argDef() {
  return getRuleContexts<BagiParser::ArgDefContext>();
}

BagiParser::ArgDefContext* BagiParser::ArgDefListContext::argDef(size_t i) {
  return getRuleContext<BagiParser::ArgDefContext>(i);
}


size_t BagiParser::ArgDefListContext::getRuleIndex() const {
  return BagiParser::RuleArgDefList;
}

void BagiParser::ArgDefListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgDefList(this);
}

void BagiParser::ArgDefListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgDefList(this);
}


std::any BagiParser::ArgDefListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitArgDefList(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ArgDefListContext* BagiParser::argDefList() {
  ArgDefListContext *_localctx = _tracker.createInstance<ArgDefListContext>(_ctx, getState());
  enterRule(_localctx, 8, BagiParser::RuleArgDefList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    argDef();
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BagiParser::T__3) {
      setState(78);
      match(BagiParser::T__3);
      setState(79);
      argDef();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgDefContext ------------------------------------------------------------------

BagiParser::ArgDefContext::ArgDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BagiParser::ArgDefContext::IDENTIFIER() {
  return getToken(BagiParser::IDENTIFIER, 0);
}

BagiParser::TypeRefContext* BagiParser::ArgDefContext::typeRef() {
  return getRuleContext<BagiParser::TypeRefContext>(0);
}


size_t BagiParser::ArgDefContext::getRuleIndex() const {
  return BagiParser::RuleArgDef;
}

void BagiParser::ArgDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgDef(this);
}

void BagiParser::ArgDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgDef(this);
}


std::any BagiParser::ArgDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitArgDef(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ArgDefContext* BagiParser::argDef() {
  ArgDefContext *_localctx = _tracker.createInstance<ArgDefContext>(_ctx, getState());
  enterRule(_localctx, 10, BagiParser::RuleArgDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(85);
      typeRef();
      break;
    }

    default:
      break;
    }
    setState(88);
    match(BagiParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeRefContext ------------------------------------------------------------------

BagiParser::TypeRefContext::TypeRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::BaseTypeContext* BagiParser::TypeRefContext::baseType() {
  return getRuleContext<BagiParser::BaseTypeContext>(0);
}

std::vector<BagiParser::ArraySuffixContext *> BagiParser::TypeRefContext::arraySuffix() {
  return getRuleContexts<BagiParser::ArraySuffixContext>();
}

BagiParser::ArraySuffixContext* BagiParser::TypeRefContext::arraySuffix(size_t i) {
  return getRuleContext<BagiParser::ArraySuffixContext>(i);
}


size_t BagiParser::TypeRefContext::getRuleIndex() const {
  return BagiParser::RuleTypeRef;
}

void BagiParser::TypeRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeRef(this);
}

void BagiParser::TypeRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeRef(this);
}


std::any BagiParser::TypeRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitTypeRef(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::TypeRefContext* BagiParser::typeRef() {
  TypeRefContext *_localctx = _tracker.createInstance<TypeRefContext>(_ctx, getState());
  enterRule(_localctx, 12, BagiParser::RuleTypeRef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    baseType();
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BagiParser::T__12) {
      setState(91);
      arraySuffix();
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BaseTypeContext ------------------------------------------------------------------

BagiParser::BaseTypeContext::BaseTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::BuiltinTypeContext* BagiParser::BaseTypeContext::builtinType() {
  return getRuleContext<BagiParser::BuiltinTypeContext>(0);
}

BagiParser::CustomTypeContext* BagiParser::BaseTypeContext::customType() {
  return getRuleContext<BagiParser::CustomTypeContext>(0);
}


size_t BagiParser::BaseTypeContext::getRuleIndex() const {
  return BagiParser::RuleBaseType;
}

void BagiParser::BaseTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBaseType(this);
}

void BagiParser::BaseTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBaseType(this);
}


std::any BagiParser::BaseTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBaseType(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::BaseTypeContext* BagiParser::baseType() {
  BaseTypeContext *_localctx = _tracker.createInstance<BaseTypeContext>(_ctx, getState());
  enterRule(_localctx, 14, BagiParser::RuleBaseType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case BagiParser::T__4:
      case BagiParser::T__5:
      case BagiParser::T__6:
      case BagiParser::T__7:
      case BagiParser::T__8:
      case BagiParser::T__9:
      case BagiParser::T__10:
      case BagiParser::T__11: {
        enterOuterAlt(_localctx, 1);
        setState(97);
        builtinType();
        break;
      }

      case BagiParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(98);
        customType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BuiltinTypeContext ------------------------------------------------------------------

BagiParser::BuiltinTypeContext::BuiltinTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::BuiltinTypeContext::getRuleIndex() const {
  return BagiParser::RuleBuiltinType;
}

void BagiParser::BuiltinTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBuiltinType(this);
}

void BagiParser::BuiltinTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBuiltinType(this);
}


std::any BagiParser::BuiltinTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBuiltinType(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::BuiltinTypeContext* BagiParser::builtinType() {
  BuiltinTypeContext *_localctx = _tracker.createInstance<BuiltinTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, BagiParser::RuleBuiltinType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8160) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomTypeContext ------------------------------------------------------------------

BagiParser::CustomTypeContext::CustomTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BagiParser::CustomTypeContext::IDENTIFIER() {
  return getToken(BagiParser::IDENTIFIER, 0);
}


size_t BagiParser::CustomTypeContext::getRuleIndex() const {
  return BagiParser::RuleCustomType;
}

void BagiParser::CustomTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomType(this);
}

void BagiParser::CustomTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomType(this);
}


std::any BagiParser::CustomTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitCustomType(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::CustomTypeContext* BagiParser::customType() {
  CustomTypeContext *_localctx = _tracker.createInstance<CustomTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, BagiParser::RuleCustomType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    match(BagiParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArraySuffixContext ------------------------------------------------------------------

BagiParser::ArraySuffixContext::ArraySuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::ArraySuffixContext::getRuleIndex() const {
  return BagiParser::RuleArraySuffix;
}

void BagiParser::ArraySuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArraySuffix(this);
}

void BagiParser::ArraySuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArraySuffix(this);
}


std::any BagiParser::ArraySuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitArraySuffix(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ArraySuffixContext* BagiParser::arraySuffix() {
  ArraySuffixContext *_localctx = _tracker.createInstance<ArraySuffixContext>(_ctx, getState());
  enterRule(_localctx, 20, BagiParser::RuleArraySuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    match(BagiParser::T__12);
    setState(106);
    match(BagiParser::T__13);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

BagiParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::VarDeclContext* BagiParser::StatementContext::varDecl() {
  return getRuleContext<BagiParser::VarDeclContext>(0);
}

BagiParser::IfStatementContext* BagiParser::StatementContext::ifStatement() {
  return getRuleContext<BagiParser::IfStatementContext>(0);
}

BagiParser::BlockContext* BagiParser::StatementContext::block() {
  return getRuleContext<BagiParser::BlockContext>(0);
}

BagiParser::WhileStatementContext* BagiParser::StatementContext::whileStatement() {
  return getRuleContext<BagiParser::WhileStatementContext>(0);
}

BagiParser::DoWhileStatementContext* BagiParser::StatementContext::doWhileStatement() {
  return getRuleContext<BagiParser::DoWhileStatementContext>(0);
}

BagiParser::BreakStatementContext* BagiParser::StatementContext::breakStatement() {
  return getRuleContext<BagiParser::BreakStatementContext>(0);
}

BagiParser::ContinueStatementContext* BagiParser::StatementContext::continueStatement() {
  return getRuleContext<BagiParser::ContinueStatementContext>(0);
}

BagiParser::ExprStatementContext* BagiParser::StatementContext::exprStatement() {
  return getRuleContext<BagiParser::ExprStatementContext>(0);
}


size_t BagiParser::StatementContext::getRuleIndex() const {
  return BagiParser::RuleStatement;
}

void BagiParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void BagiParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any BagiParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::StatementContext* BagiParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 22, BagiParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(116);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(108);
      varDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(109);
      ifStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(110);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(111);
      whileStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(112);
      doWhileStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(113);
      breakStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(114);
      continueStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(115);
      exprStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

BagiParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BagiParser::VarDeclContext::IDENTIFIER() {
  return getTokens(BagiParser::IDENTIFIER);
}

tree::TerminalNode* BagiParser::VarDeclContext::IDENTIFIER(size_t i) {
  return getToken(BagiParser::IDENTIFIER, i);
}

BagiParser::TypeRefContext* BagiParser::VarDeclContext::typeRef() {
  return getRuleContext<BagiParser::TypeRefContext>(0);
}

std::vector<BagiParser::ExprContext *> BagiParser::VarDeclContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::VarDeclContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}


size_t BagiParser::VarDeclContext::getRuleIndex() const {
  return BagiParser::RuleVarDecl;
}

void BagiParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void BagiParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


std::any BagiParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::VarDeclContext* BagiParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 24, BagiParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(118);
      typeRef();
      break;
    }

    default:
      break;
    }
    setState(121);
    match(BagiParser::IDENTIFIER);
    setState(124);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BagiParser::T__14) {
      setState(122);
      match(BagiParser::T__14);
      setState(123);
      expr(0);
    }
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BagiParser::T__3) {
      setState(126);
      match(BagiParser::T__3);
      setState(127);
      match(BagiParser::IDENTIFIER);
      setState(130);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == BagiParser::T__14) {
        setState(128);
        match(BagiParser::T__14);
        setState(129);
        expr(0);
      }
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(137);
    match(BagiParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarListContext ------------------------------------------------------------------

BagiParser::VarListContext::VarListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BagiParser::VarItemContext *> BagiParser::VarListContext::varItem() {
  return getRuleContexts<BagiParser::VarItemContext>();
}

BagiParser::VarItemContext* BagiParser::VarListContext::varItem(size_t i) {
  return getRuleContext<BagiParser::VarItemContext>(i);
}


size_t BagiParser::VarListContext::getRuleIndex() const {
  return BagiParser::RuleVarList;
}

void BagiParser::VarListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarList(this);
}

void BagiParser::VarListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarList(this);
}


std::any BagiParser::VarListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitVarList(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::VarListContext* BagiParser::varList() {
  VarListContext *_localctx = _tracker.createInstance<VarListContext>(_ctx, getState());
  enterRule(_localctx, 26, BagiParser::RuleVarList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    varItem();
    setState(144);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BagiParser::T__3) {
      setState(140);
      match(BagiParser::T__3);
      setState(141);
      varItem();
      setState(146);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarItemContext ------------------------------------------------------------------

BagiParser::VarItemContext::VarItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BagiParser::VarItemContext::IDENTIFIER() {
  return getToken(BagiParser::IDENTIFIER, 0);
}

BagiParser::ExprContext* BagiParser::VarItemContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}


size_t BagiParser::VarItemContext::getRuleIndex() const {
  return BagiParser::RuleVarItem;
}

void BagiParser::VarItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarItem(this);
}

void BagiParser::VarItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarItem(this);
}


std::any BagiParser::VarItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitVarItem(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::VarItemContext* BagiParser::varItem() {
  VarItemContext *_localctx = _tracker.createInstance<VarItemContext>(_ctx, getState());
  enterRule(_localctx, 28, BagiParser::RuleVarItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(BagiParser::IDENTIFIER);
    setState(150);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BagiParser::T__14) {
      setState(148);
      match(BagiParser::T__14);
      setState(149);
      expr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

BagiParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::ExprContext* BagiParser::IfStatementContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

std::vector<BagiParser::StatementContext *> BagiParser::IfStatementContext::statement() {
  return getRuleContexts<BagiParser::StatementContext>();
}

BagiParser::StatementContext* BagiParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<BagiParser::StatementContext>(i);
}


size_t BagiParser::IfStatementContext::getRuleIndex() const {
  return BagiParser::RuleIfStatement;
}

void BagiParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void BagiParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


std::any BagiParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::IfStatementContext* BagiParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, BagiParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(BagiParser::T__15);
    setState(153);
    match(BagiParser::T__1);
    setState(154);
    expr(0);
    setState(155);
    match(BagiParser::T__2);
    setState(156);
    statement();
    setState(159);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(157);
      match(BagiParser::T__16);
      setState(158);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

BagiParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BagiParser::StatementContext *> BagiParser::BlockContext::statement() {
  return getRuleContexts<BagiParser::StatementContext>();
}

BagiParser::StatementContext* BagiParser::BlockContext::statement(size_t i) {
  return getRuleContext<BagiParser::StatementContext>(i);
}


size_t BagiParser::BlockContext::getRuleIndex() const {
  return BagiParser::RuleBlock;
}

void BagiParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void BagiParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any BagiParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::BlockContext* BagiParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 32, BagiParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(BagiParser::T__17);
    setState(165);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 71917268882497508) != 0)) {
      setState(162);
      statement();
      setState(167);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(168);
    match(BagiParser::T__18);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

BagiParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::ExprContext* BagiParser::WhileStatementContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

BagiParser::StatementContext* BagiParser::WhileStatementContext::statement() {
  return getRuleContext<BagiParser::StatementContext>(0);
}


size_t BagiParser::WhileStatementContext::getRuleIndex() const {
  return BagiParser::RuleWhileStatement;
}

void BagiParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}

void BagiParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}


std::any BagiParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::WhileStatementContext* BagiParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, BagiParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(BagiParser::T__19);
    setState(171);
    match(BagiParser::T__1);
    setState(172);
    expr(0);
    setState(173);
    match(BagiParser::T__2);
    setState(174);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoWhileStatementContext ------------------------------------------------------------------

BagiParser::DoWhileStatementContext::DoWhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::BlockContext* BagiParser::DoWhileStatementContext::block() {
  return getRuleContext<BagiParser::BlockContext>(0);
}

BagiParser::ExprContext* BagiParser::DoWhileStatementContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}


size_t BagiParser::DoWhileStatementContext::getRuleIndex() const {
  return BagiParser::RuleDoWhileStatement;
}

void BagiParser::DoWhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoWhileStatement(this);
}

void BagiParser::DoWhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoWhileStatement(this);
}


std::any BagiParser::DoWhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitDoWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::DoWhileStatementContext* BagiParser::doWhileStatement() {
  DoWhileStatementContext *_localctx = _tracker.createInstance<DoWhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, BagiParser::RuleDoWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    match(BagiParser::T__20);
    setState(177);
    block();
    setState(178);
    match(BagiParser::T__19);
    setState(179);
    match(BagiParser::T__1);
    setState(180);
    expr(0);
    setState(181);
    match(BagiParser::T__2);
    setState(182);
    match(BagiParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

BagiParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::BreakStatementContext::getRuleIndex() const {
  return BagiParser::RuleBreakStatement;
}

void BagiParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void BagiParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}


std::any BagiParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::BreakStatementContext* BagiParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 38, BagiParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(BagiParser::T__21);
    setState(185);
    match(BagiParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

BagiParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::ContinueStatementContext::getRuleIndex() const {
  return BagiParser::RuleContinueStatement;
}

void BagiParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void BagiParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}


std::any BagiParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ContinueStatementContext* BagiParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 40, BagiParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    match(BagiParser::T__22);
    setState(188);
    match(BagiParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprStatementContext ------------------------------------------------------------------

BagiParser::ExprStatementContext::ExprStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BagiParser::ExprContext* BagiParser::ExprStatementContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}


size_t BagiParser::ExprStatementContext::getRuleIndex() const {
  return BagiParser::RuleExprStatement;
}

void BagiParser::ExprStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprStatement(this);
}

void BagiParser::ExprStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprStatement(this);
}


std::any BagiParser::ExprStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitExprStatement(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ExprStatementContext* BagiParser::exprStatement() {
  ExprStatementContext *_localctx = _tracker.createInstance<ExprStatementContext>(_ctx, getState());
  enterRule(_localctx, 42, BagiParser::RuleExprStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    expr(0);
    setState(191);
    match(BagiParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

BagiParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::ExprContext::getRuleIndex() const {
  return BagiParser::RuleExpr;
}

void BagiParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AddSubExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::AddSubExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::AddSubExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::AddSubExprContext::AddSubExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::AddSubExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddSubExpr(this);
}
void BagiParser::AddSubExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddSubExpr(this);
}

std::any BagiParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::OrExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::OrExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::OrExprContext::OrExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::OrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpr(this);
}
void BagiParser::OrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpr(this);
}

std::any BagiParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParensExprContext ------------------------------------------------------------------

BagiParser::ExprContext* BagiParser::ParensExprContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

BagiParser::ParensExprContext::ParensExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::ParensExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParensExpr(this);
}
void BagiParser::ParensExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParensExpr(this);
}

std::any BagiParser::ParensExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitParensExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitXorExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::BitXorExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::BitXorExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::BitXorExprContext::BitXorExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::BitXorExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitXorExpr(this);
}
void BagiParser::BitXorExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitXorExpr(this);
}

std::any BagiParser::BitXorExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBitXorExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IndexerExprContext ------------------------------------------------------------------

BagiParser::ExprContext* BagiParser::IndexerExprContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

BagiParser::ExprListContext* BagiParser::IndexerExprContext::exprList() {
  return getRuleContext<BagiParser::ExprListContext>(0);
}

BagiParser::IndexerExprContext::IndexerExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::IndexerExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndexerExpr(this);
}
void BagiParser::IndexerExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndexerExpr(this);
}

std::any BagiParser::IndexerExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitIndexerExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::CmpExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::CmpExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::CmpExprContext::CmpExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::CmpExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCmpExpr(this);
}
void BagiParser::CmpExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCmpExpr(this);
}

std::any BagiParser::CmpExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitCmpExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShiftExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::ShiftExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::ShiftExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::ShiftExprContext::ShiftExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::ShiftExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpr(this);
}
void BagiParser::ShiftExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpr(this);
}

std::any BagiParser::ShiftExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitShiftExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PlaceExprContext ------------------------------------------------------------------

tree::TerminalNode* BagiParser::PlaceExprContext::IDENTIFIER() {
  return getToken(BagiParser::IDENTIFIER, 0);
}

BagiParser::PlaceExprContext::PlaceExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::PlaceExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlaceExpr(this);
}
void BagiParser::PlaceExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlaceExpr(this);
}

std::any BagiParser::PlaceExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitPlaceExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitOrExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::BitOrExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::BitOrExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::BitOrExprContext::BitOrExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::BitOrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitOrExpr(this);
}
void BagiParser::BitOrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitOrExpr(this);
}

std::any BagiParser::BitOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::EqExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::EqExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::EqExprContext::EqExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::EqExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqExpr(this);
}
void BagiParser::EqExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqExpr(this);
}

std::any BagiParser::EqExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitEqExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

BagiParser::UnOpContext* BagiParser::UnaryExprContext::unOp() {
  return getRuleContext<BagiParser::UnOpContext>(0);
}

BagiParser::ExprContext* BagiParser::UnaryExprContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

BagiParser::UnaryExprContext::UnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void BagiParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

std::any BagiParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExprContext ------------------------------------------------------------------

BagiParser::LiteralContext* BagiParser::LiteralExprContext::literal() {
  return getRuleContext<BagiParser::LiteralContext>(0);
}

BagiParser::LiteralExprContext::LiteralExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::LiteralExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpr(this);
}
void BagiParser::LiteralExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpr(this);
}

std::any BagiParser::LiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitLiteralExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitAndExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::BitAndExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::BitAndExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::BitAndExprContext::BitAndExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::BitAndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitAndExpr(this);
}
void BagiParser::BitAndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitAndExpr(this);
}

std::any BagiParser::BitAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitBitAndExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallExprContext ------------------------------------------------------------------

BagiParser::ExprContext* BagiParser::CallExprContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

BagiParser::ExprListContext* BagiParser::CallExprContext::exprList() {
  return getRuleContext<BagiParser::ExprListContext>(0);
}

BagiParser::CallExprContext::CallExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::CallExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallExpr(this);
}
void BagiParser::CallExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallExpr(this);
}

std::any BagiParser::CallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignExprContext ------------------------------------------------------------------

tree::TerminalNode* BagiParser::AssignExprContext::IDENTIFIER() {
  return getToken(BagiParser::IDENTIFIER, 0);
}

BagiParser::AssignOpContext* BagiParser::AssignExprContext::assignOp() {
  return getRuleContext<BagiParser::AssignOpContext>(0);
}

BagiParser::ExprContext* BagiParser::AssignExprContext::expr() {
  return getRuleContext<BagiParser::ExprContext>(0);
}

BagiParser::AssignExprContext::AssignExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::AssignExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignExpr(this);
}
void BagiParser::AssignExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignExpr(this);
}

std::any BagiParser::AssignExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitAssignExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::MulDivExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::MulDivExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::MulDivExprContext::MulDivExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::MulDivExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulDivExpr(this);
}
void BagiParser::MulDivExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulDivExpr(this);
}

std::any BagiParser::MulDivExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitMulDivExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<BagiParser::ExprContext *> BagiParser::AndExprContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::AndExprContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}

BagiParser::AndExprContext::AndExprContext(ExprContext *ctx) { copyFrom(ctx); }

void BagiParser::AndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpr(this);
}
void BagiParser::AndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpr(this);
}

std::any BagiParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ExprContext* BagiParser::expr() {
   return expr(0);
}

BagiParser::ExprContext* BagiParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  BagiParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  BagiParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, BagiParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(207);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<AssignExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(194);
      match(BagiParser::IDENTIFIER);
      setState(195);
      assignOp();
      setState(196);
      expr(7);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(198);
      unOp();
      setState(199);
      expr(6);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ParensExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(201);
      match(BagiParser::T__1);
      setState(202);
      expr(0);
      setState(203);
      match(BagiParser::T__2);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PlaceExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(205);
      match(BagiParser::IDENTIFIER);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(206);
      literal();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(253);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(251);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(209);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(210);
          match(BagiParser::T__23);
          setState(211);
          expr(18);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(212);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(213);
          match(BagiParser::T__24);
          setState(214);
          expr(17);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BitOrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(215);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(216);
          match(BagiParser::T__25);
          setState(217);
          expr(16);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BitXorExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(218);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(219);
          match(BagiParser::T__26);
          setState(220);
          expr(15);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BitAndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(221);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(222);
          match(BagiParser::T__27);
          setState(223);
          expr(14);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<EqExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(224);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(225);
          _la = _input->LA(1);
          if (!(_la == BagiParser::T__28

          || _la == BagiParser::T__29)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(226);
          expr(13);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<CmpExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(227);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(228);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 32212254720) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(229);
          expr(12);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ShiftExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(230);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(231);
          _la = _input->LA(1);
          if (!(_la == BagiParser::T__34

          || _la == BagiParser::T__35)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(232);
          expr(11);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(233);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(234);
          _la = _input->LA(1);
          if (!(_la == BagiParser::T__36

          || _la == BagiParser::T__37)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(235);
          expr(10);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<MulDivExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(236);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(237);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 3848290697216) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(238);
          expr(9);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<CallExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(239);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(240);
          match(BagiParser::T__1);
          setState(242);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 71917268866433028) != 0)) {
            setState(241);
            exprList();
          }
          setState(244);
          match(BagiParser::T__2);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<IndexerExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(245);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(246);
          match(BagiParser::T__12);
          setState(248);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 71917268866433028) != 0)) {
            setState(247);
            exprList();
          }
          setState(250);
          match(BagiParser::T__13);
          break;
        }

        default:
          break;
        } 
      }
      setState(255);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AssignOpContext ------------------------------------------------------------------

BagiParser::AssignOpContext::AssignOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::AssignOpContext::getRuleIndex() const {
  return BagiParser::RuleAssignOp;
}

void BagiParser::AssignOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignOp(this);
}

void BagiParser::AssignOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignOp(this);
}


std::any BagiParser::AssignOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitAssignOp(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::AssignOpContext* BagiParser::assignOp() {
  AssignOpContext *_localctx = _tracker.createInstance<AssignOpContext>(_ctx, getState());
  enterRule(_localctx, 46, BagiParser::RuleAssignOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 136339441876992) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnOpContext ------------------------------------------------------------------

BagiParser::UnOpContext::UnOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t BagiParser::UnOpContext::getRuleIndex() const {
  return BagiParser::RuleUnOp;
}

void BagiParser::UnOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnOp(this);
}

void BagiParser::UnOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnOp(this);
}


std::any BagiParser::UnOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitUnOp(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::UnOpContext* BagiParser::unOp() {
  UnOpContext *_localctx = _tracker.createInstance<UnOpContext>(_ctx, getState());
  enterRule(_localctx, 48, BagiParser::RuleUnOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 422624781926400) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprListContext ------------------------------------------------------------------

BagiParser::ExprListContext::ExprListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BagiParser::ExprContext *> BagiParser::ExprListContext::expr() {
  return getRuleContexts<BagiParser::ExprContext>();
}

BagiParser::ExprContext* BagiParser::ExprListContext::expr(size_t i) {
  return getRuleContext<BagiParser::ExprContext>(i);
}


size_t BagiParser::ExprListContext::getRuleIndex() const {
  return BagiParser::RuleExprList;
}

void BagiParser::ExprListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprList(this);
}

void BagiParser::ExprListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprList(this);
}


std::any BagiParser::ExprListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitExprList(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::ExprListContext* BagiParser::exprList() {
  ExprListContext *_localctx = _tracker.createInstance<ExprListContext>(_ctx, getState());
  enterRule(_localctx, 50, BagiParser::RuleExprList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    expr(0);
    setState(265);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BagiParser::T__3) {
      setState(261);
      match(BagiParser::T__3);
      setState(262);
      expr(0);
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

BagiParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BagiParser::LiteralContext::BOOL() {
  return getToken(BagiParser::BOOL, 0);
}

tree::TerminalNode* BagiParser::LiteralContext::STRING() {
  return getToken(BagiParser::STRING, 0);
}

tree::TerminalNode* BagiParser::LiteralContext::CHAR() {
  return getToken(BagiParser::CHAR, 0);
}

tree::TerminalNode* BagiParser::LiteralContext::HEX() {
  return getToken(BagiParser::HEX, 0);
}

tree::TerminalNode* BagiParser::LiteralContext::BITS() {
  return getToken(BagiParser::BITS, 0);
}

tree::TerminalNode* BagiParser::LiteralContext::DEC() {
  return getToken(BagiParser::DEC, 0);
}


size_t BagiParser::LiteralContext::getRuleIndex() const {
  return BagiParser::RuleLiteral;
}

void BagiParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void BagiParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<BagiListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any BagiParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<BagiVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

BagiParser::LiteralContext* BagiParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 52, BagiParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(268);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 70931694131085312) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool BagiParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 22: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool BagiParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 17);
    case 1: return precpred(_ctx, 16);
    case 2: return precpred(_ctx, 15);
    case 3: return precpred(_ctx, 14);
    case 4: return precpred(_ctx, 13);
    case 5: return precpred(_ctx, 12);
    case 6: return precpred(_ctx, 11);
    case 7: return precpred(_ctx, 10);
    case 8: return precpred(_ctx, 9);
    case 9: return precpred(_ctx, 8);
    case 10: return precpred(_ctx, 4);
    case 11: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void BagiParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  bagiParserInitialize();
#else
  ::antlr4::internal::call_once(bagiParserOnceFlag, bagiParserInitialize);
#endif
}
