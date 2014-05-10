#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>
#include <map>
#include <vector>
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

using std::map;
using std::vector;

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

typedef vector<Symbol> Signature;

class ClassTable {
private:
  int semant_errors;
  void install_basic_classes();
  void build_members_from(Symbol super);
  void build_inherit_vectors_from(Symbol super);
  ostream& error_stream;
  map<Symbol, Class_> class_map;
  map<Symbol, vector<Symbol> > inherit_map;
  map<Symbol, map<Symbol, Symbol> > attribute_map;
  map<Symbol, map<Symbol, Signature> > signature_map;

public:
  ClassTable(Classes);
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
  Class_ find_class(Symbol name) const;
  Symbol find_lca(Symbol name1, Symbol name2) const;
  void build_inherit_vectors();
  void build_class_members();
  void check_class_members();
  Signature find_signature(Symbol name, Symbol method) const;
  Symbol find_attribute(Symbol name, Symbol attr) const;
  void add_symbol_from(Symbol name) const;
  bool check_if_A_is_B(Symbol name1, Symbol name2) const;
};

#endif

