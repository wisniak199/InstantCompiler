/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "JVMVisitor.h"

JVMVisitor::JVMVisitor()
{

}

void JVMVisitor::visitProgram(Program* t) {} //abstract class
void JVMVisitor::visitStmt(Stmt* t) {} //abstract class
void JVMVisitor::visitExp(Exp* t) {} //abstract class

void JVMVisitor::visitProg(Prog *prog)
{
  prog->liststmt_->accept(this);
}

void JVMVisitor::visitSAss(SAss *sass)
{

  int index;
  if (variables.count(sass->ident_) > 0) {
    index = variables.at(sass->ident_);
  } else {
    index = variables.size();
    variables[sass->ident_] = index;
  }
  sass->exp_->accept(this);
  instructions.push_back(instruction_builder.getAssignInstruction(index, stack.front()));
  stack.pop_front();
}

void JVMVisitor::visitSExp(SExp *sexp)
{
  /* Code For SExp Goes Here */

  sexp->exp_->accept(this);
  instructions.push_back(instruction_builder.getPrintInstruction(stack.front()));
  stack.pop_front();
}

void JVMVisitor::visitExpAdd(ExpAdd *expadd)
{
  expadd->exp_1->accept(this);
  expadd->exp_2->accept(this);
  InstructionType rinstr = stack.front();
  stack.pop_front();
  InstructionType linstr = stack.front();
  stack.pop_front();
  stack.push_front(instruction_builder.getAddInstruction(linstr, rinstr));
}

void JVMVisitor::visitExpSub(ExpSub *expsub)
{
  /* Code For ExpSub Goes Here */

  expsub->exp_1->accept(this);
  expsub->exp_2->accept(this);
  InstructionType rinstr = stack.front();
  stack.pop_front();
  InstructionType linstr = stack.front();
  stack.pop_front();
  stack.push_front(instruction_builder.getSubInstruction(linstr, rinstr));
}

void JVMVisitor::visitExpMul(ExpMul *expmul)
{
  /* Code For ExpMul Goes Here */

  expmul->exp_1->accept(this);
  expmul->exp_2->accept(this);
  InstructionType rinstr = stack.front();
  stack.pop_front();
  InstructionType linstr = stack.front();
  stack.pop_front();
  stack.push_front(instruction_builder.getMulInstruction(linstr, rinstr));
}

void JVMVisitor::visitExpDiv(ExpDiv *expdiv)
{
  /* Code For ExpDiv Goes Here */

  expdiv->exp_1->accept(this);
  expdiv->exp_2->accept(this);
  InstructionType rinstr = stack.front();
  stack.pop_front();
  InstructionType linstr = stack.front();
  stack.pop_front();
  stack.push_front(instruction_builder.getDivInstruction(linstr, rinstr));
}

void JVMVisitor::visitExpLit(ExpLit *explit)
{
  visitInteger(explit->integer_);
}

void JVMVisitor::visitExpVar(ExpVar *expvar)
{
  stack.push_front(instruction_builder.getLoadVariableInstruction(variables.at(expvar->ident_)));
}


void JVMVisitor::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void JVMVisitor::visitInteger(Integer x)
{
   stack.push_front(instruction_builder.getConstInstruction(x));
}

void JVMVisitor::visitChar(Char x)
{
  /* Not used */
}

void JVMVisitor::visitDouble(Double x)
{
  /* Not used*/
}

void JVMVisitor::visitString(String x)
{
  /* Not used */
}

void JVMVisitor::visitIdent(Ident x)
{

}


void JVMVisitor::generateIR() {
  int stack_needed = 0;
  for (auto& instr : this->instructions) {
    stack_needed = std::max(stack_needed, instr->getStackSizeUsed());
  }

  std::cout << ".class public Test" << std::endl
            << ".super java/lang/Object" << std::endl
            << ";" << std::endl
            << "; standard initializer" << std::endl
            << ".method public <init>()V" << std::endl
            << "aload_0" << std::endl
            << "invokenonvirtual java/lang/Object/<init>()V" << std::endl
            << "return" << std::endl
            << ".end method" << std::endl
            << ".method public static main([Ljava/lang/String;)V" << std::endl
            << ".limit stack " << stack_needed << std::endl;
  if (!this->variables.empty()) {
    std::cout << ".limit locals " << this->variables.size() << std::endl;
  }

  for (auto& instr : this->instructions) {
    instr->generateCode(std::cout);
  }

  std::cout << "return" << std::endl
            << ".end method" << std::endl;
}
