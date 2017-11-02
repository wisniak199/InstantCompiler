#ifndef COMPILE_ERROR_H
#define COMPILE_ERROR_H

#include <exception>

struct CompileError : public std::exception {
  std::string s;
  CompileError(std::string ss) : s(ss) {}
  ~CompileError() throw () {}
  const char* what() const throw() { return s.c_str(); }
};

#endif
