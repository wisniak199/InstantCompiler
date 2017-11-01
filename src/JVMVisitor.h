#ifndef JVM_VISITOR_H
#define JVM_VISITOR_H
/* You might want to change the above name. */
#include <list>
#include <iostream>
#include <map>

#include "JVMInstruction.h"

#include <parser/Absyn.H>


class JVMVisitor : public Visitor
{
public:
  JVMVisitor();
  void generateIR();

  void visitProgram(Program* p);
  void visitStmt(Stmt* p);
  void visitExp(Exp* p);
  void visitProg(Prog* p);
  void visitSAss(SAss* p);
  void visitSExp(SExp* p);
  void visitExpAdd(ExpAdd* p);
  void visitExpSub(ExpSub* p);
  void visitExpMul(ExpMul* p);
  void visitExpDiv(ExpDiv* p);
  void visitExpLit(ExpLit* p);
  void visitExpVar(ExpVar* p);
  void visitListStmt(ListStmt* p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);
private:
  typedef JVMInstructionBuilder::InstructionType InstructionType;
  std::list<InstructionType> stack;
  std::vector<InstructionType> instructions;
  JVMInstructionBuilder instruction_builder;
  std::map<std::string, int> variables;
};


#endif
