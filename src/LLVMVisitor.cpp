/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "LLVMVisitor.h"

LLVMVisitor::LLVMVisitor()
{
  builder = llvm::make_unique<llvm::IRBuilder<true, llvm::NoFolder>>(context);
  module = llvm::make_unique<llvm::Module>("main module", context);
}

void LLVMVisitor::visitProgram(Program* t) {} //abstract class
void LLVMVisitor::visitStmt(Stmt* t) {} //abstract class
void LLVMVisitor::visitExp(Exp* t) {} //abstract class

void LLVMVisitor::visitProg(Prog *prog)
{
  llvm::FunctionType *funcType = llvm::FunctionType::get(builder->getVoidTy(), false);
  llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module.get());
  llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
  builder->SetInsertPoint(entry);

  prog->liststmt_->accept(this);

  builder->CreateRet(nullptr);
}

void LLVMVisitor::visitSAss(SAss *sass)
{
  sass->exp_->accept(this);
  named_values[sass->ident_] = stack.front();
  stack.pop_front();
}

void LLVMVisitor::visitSExp(SExp *sexp)
{
  /* Code For SExp Goes Here */

  sexp->exp_->accept(this);
  generatePrintf(stack.front());
  stack.pop_front();
}

void LLVMVisitor::visitExpAdd(ExpAdd *expadd)
{
  expadd->exp_1->accept(this);
  expadd->exp_2->accept(this);
  llvm::Value *rval = stack.front();
  stack.pop_front();
  llvm::Value *lval = stack.front();
  stack.pop_front();
  stack.push_front(builder->CreateAdd(lval, rval, "add_res"));
}

void LLVMVisitor::visitExpSub(ExpSub *expsub)
{
  /* Code For ExpSub Goes Here */

  expsub->exp_1->accept(this);
  expsub->exp_2->accept(this);
  llvm::Value *rval = stack.front();
  stack.pop_front();
  llvm::Value *lval = stack.front();
  stack.pop_front();
  stack.push_front(builder->CreateSub(lval, rval, "add_res"));
}

void LLVMVisitor::visitExpMul(ExpMul *expmul)
{
  /* Code For ExpMul Goes Here */

  expmul->exp_1->accept(this);
  expmul->exp_2->accept(this);
  llvm::Value *rval = stack.front();
  stack.pop_front();
  llvm::Value *lval = stack.front();
  stack.pop_front();
  stack.push_front(builder->CreateMul(lval, rval, "add_res"));
}

void LLVMVisitor::visitExpDiv(ExpDiv *expdiv)
{
  /* Code For ExpDiv Goes Here */

  expdiv->exp_1->accept(this);
  expdiv->exp_2->accept(this);
  llvm::Value *rval = stack.front();
  stack.pop_front();
  llvm::Value *lval = stack.front();
  stack.pop_front();
  stack.push_front(builder->CreateSDiv(lval, rval, "add_res"));
}

void LLVMVisitor::visitExpLit(ExpLit *explit)
{
  visitInteger(explit->integer_);
}

void LLVMVisitor::visitExpVar(ExpVar *expvar)
{
  stack.push_front(named_values[expvar->ident_]);
}


void LLVMVisitor::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void LLVMVisitor::visitInteger(Integer x)
{
   stack.push_front(llvm::ConstantInt::get(context, llvm::APInt(32, x, true)));
}

void LLVMVisitor::visitChar(Char x)
{
  /* Not used */
}

void LLVMVisitor::visitDouble(Double x)
{
  /* Not used*/
}

void LLVMVisitor::visitString(String x)
{
  /* Not used */
}

void LLVMVisitor::visitIdent(Ident x)
{
  stack.push_front(named_values[x]);
}

void LLVMVisitor::generatePrintf(llvm::Value *value) {
  llvm::Function *func_printf = module->getFunction("printf");
  if (!func_printf) {
    llvm::FunctionType *FuncTy9 = llvm::FunctionType::get(llvm::IntegerType::get(module->getContext(), 32), true);
    func_printf = llvm::Function::Create(FuncTy9, llvm::GlobalValue::ExternalLinkage, "printf", module.get());
    func_printf->setCallingConv(llvm::CallingConv::C);
  }

  llvm::Value *str = builder->CreateGlobalStringPtr("%d\n");
  std::vector <llvm::Value *> int32_call_params;
  int32_call_params.push_back(str);
  int32_call_params.push_back(value);
  builder->CreateCall(func_printf, int32_call_params, "calltmp");

}

void LLVMVisitor::generateIR() {
  module->print(llvm::outs(), nullptr);
}
