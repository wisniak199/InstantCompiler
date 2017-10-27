#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */
#include <list>
#include <iostream>

#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/NoFolder.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/Support/raw_ostream.h>


#include <parser/Absyn.H>


class LLVMVisitor : public Visitor
{
public:
  LLVMVisitor();
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
  void generatePrintf(llvm::Value *value);

  llvm::LLVMContext context;
  std::unique_ptr<llvm::IRBuilder<true, llvm::NoFolder>> builder;
  std::unique_ptr<llvm::Module> module;
  std::map<Ident, llvm::Value*> named_values;
  std::list<llvm::Value*> stack;
};


#endif
