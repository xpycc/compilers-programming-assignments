#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <algorithm>
#include <set>
#include <typeinfo>
#include "semant.h"
#include "utilities.h"

using std::make_pair;
using std::set;
using std::map;

extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
  arg         = idtable.add_string("arg");
  arg2        = idtable.add_string("arg2");
  Bool        = idtable.add_string("Bool");
  concat      = idtable.add_string("concat");
  cool_abort  = idtable.add_string("abort");
  copy        = idtable.add_string("copy");
  Int         = idtable.add_string("Int");
  in_int      = idtable.add_string("in_int");
  in_string   = idtable.add_string("in_string");
  IO          = idtable.add_string("IO");
  length      = idtable.add_string("length");
  Main        = idtable.add_string("Main");
  main_meth   = idtable.add_string("main");
  //   _no_class is a symbol that can't be the name of any 
  //   user-defined class.
  No_class    = idtable.add_string("_no_class");
  No_type     = idtable.add_string("_no_type");
  Object      = idtable.add_string("Object");
  out_int     = idtable.add_string("out_int");
  out_string  = idtable.add_string("out_string");
  prim_slot   = idtable.add_string("_prim_slot");
  self        = idtable.add_string("self");
  SELF_TYPE   = idtable.add_string("SELF_TYPE");
  Str         = idtable.add_string("String");
  str_field   = idtable.add_string("_str_field");
  substr      = idtable.add_string("substr");
  type_name   = idtable.add_string("type_name");
  val         = idtable.add_string("_val");
}

ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr) {
  // class inheritance checking
//  using std::map; using std::set;

  Symbol Cycle = No_class;
  install_basic_classes();
  map<Symbol, Symbol> ancestor;
  ancestor[Int] = Object;
  ancestor[Str] = Object;
  ancestor[IO]  = Object;
  for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
    Class_ c = classes->nth(i);
    if (c->get_name() == SELF_TYPE) {
      semant_error(c) << "Class name cannot be SELF_TYPE.\n";
    } else if (c->get_parent() == SELF_TYPE) {
      semant_error(c) << "Class " << c->get_name() << " cannot inherit SELF_TYPE.\n";
    } else if (c->get_parent() == Bool || c->get_parent() == Int || c->get_parent() == Str) {
      semant_error(c) << "Class " << c->get_name() << " cannot inherit class " << c->get_parent() << ".\n";
    } else if (class_map.find(c->get_name()) == class_map.end()) {
      class_map[c->get_name()] = c;
      ancestor[c->get_name()] = c->get_parent();
    } else {
      semant_error(c) << "Redefinition of class " << c->get_name()  << ".\n";
    }
  }
  if (semant_errors > 0)
    return;
  // END OF FIRST PASS: make sure there's no redefinition
  for (map<Symbol, Symbol>::iterator it = ancestor.begin(); it != ancestor.end(); ++it) {
    if (it->second == Cycle || it->second == Object)
      continue;
    set<Symbol> visited;
    Symbol c = it->first, p = it->second;
    visited.insert(c);
    while (p != Object && p != Cycle && visited.find(p) == visited.end()) {
      map<Symbol, Symbol>::iterator k = ancestor.find(p);
      if (k == ancestor.end()) {
        break;
      } else {
        c = p;
        p = k->second;
        visited.insert(c);
      }
    }
    if (p == Cycle) {
      c = it->first; p = it->second;
      ancestor[c] = Cycle;
      while (p != Cycle) {
        semant_error(class_map[c]) << "Class " << c << ", or an ancestor of "
            << c << ", is involved in an inheritance cycle.\n";
        c = p;
        p = ancestor[p];
        ancestor[c] = Cycle;
      }
    } else if (visited.find(p) != visited.end()) {
      c = it->first; p = it->second;
      visited.clear(); visited.insert(c);
      semant_error(class_map[c]) << "Class " << c << ", or an ancestor of "
          << c << ", is involved in an inheritance cycle.\n";
      ancestor[c] = Cycle;
      while (visited.find(p) == visited.end()) {
        c = p;
        p = ancestor[p];
        visited.insert(c);
        ancestor[c] = Cycle;
        semant_error(class_map[c]) << "Class " << c << ", or an ancestor of "
            << c << ", is involved in an inheritance cycle.\n";
      }
    } else if (p != Object) { // ancestor undefined
      c = it->first; p = it->second;
      ancestor[c] = Object;
      while (class_map.find(p) != class_map.end()) {
        c = p;
        p = ancestor[p];
        ancestor[c] = Object;
      }
      semant_error(class_map[c]) << "Class " << c << " inherits from an undefined class " << p << ".\n";
    } else { // if p == Object, it's OK!
      c = it->first; p = it->second;
      ancestor[c] = Object;
      while (p != Object) {
        c = p;
        p = ancestor[p];
        ancestor[c] = Object;
      }
    }
  }
  // END OF SECOND PASS: make sure the classes inherit correctly
}

Class_ ClassTable::find_class(Symbol name) const {
  map<Symbol, Class_>::const_iterator p = class_map.find(name);
  if (p != class_map.end()) {
    return p->second;
  } else {
    return NULL;
  }
}

void ClassTable::install_basic_classes() {

  // The tree package uses these globals to annotate the classes built below.
  // curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");

  // The following demonstrates how to create dummy parse trees to
  // refer to basic Cool classes.  There's no need for method
  // bodies -- these are already built into the runtime system.

  // IMPORTANT: The results of the following expressions are
  // stored in local variables.  You will want to do something
  // with those variables at the end of this method to make this
  // code meaningful.

  // 
  // The Object class has no parent class. Its methods are
  //        abort() : Object    aborts the program
  //        type_name() : Str   returns a string representation of class name
  //        copy() : SELF_TYPE  returns a copy of the object
  //
  // There is no need for method bodies in the basic classes---these
  // are already built in to the runtime system.

  Class_ Object_class =
    class_(Object, 
        No_class,
        append_Features(
          append_Features(
            single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
            single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
          single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
        filename);

  // 
  // The IO class inherits from Object. Its methods are
  //        out_string(Str) : SELF_TYPE       writes a string to the output
  //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
  //        in_string() : Str                 reads a string from the input
  //        in_int() : Int                      "   an int     "  "     "
  //
  Class_ IO_class = 
    class_(IO, 
        Object,
        append_Features(
          append_Features(
            append_Features(
              single_Features(method(out_string, single_Formals(formal(arg, Str)),
                  SELF_TYPE, no_expr())),
              single_Features(method(out_int, single_Formals(formal(arg, Int)),
                  SELF_TYPE, no_expr()))),
            single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
          single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
        filename);  

  //
  // The Int class has no methods and only a single attribute, the
  // "val" for the integer. 
  //
  Class_ Int_class =
    class_(Int, 
        Object,
        single_Features(attr(val, prim_slot, no_expr())),
        filename);

  //
  // Bool also has only the "val" slot.
  //
  Class_ Bool_class =
    class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

  //
  // The class Str has a number of slots and operations:
  //       val                                  the length of the string
  //       str_field                            the string itself
  //       length() : Int                       returns length of the string
  //       concat(arg: Str) : Str               performs string concatenation
  //       substr(arg: Int, arg2: Int): Str     substring selection
  //       
  Class_ Str_class =
    class_(Str, 
        Object,
        append_Features(
          append_Features(
            append_Features(
              append_Features(
                single_Features(attr(val, Int, no_expr())),
                single_Features(attr(str_field, prim_slot, no_expr()))),
              single_Features(method(length, nil_Formals(), Int, no_expr()))),
            single_Features(method(concat, 
                single_Formals(formal(arg, Str)),
                Str, 
                no_expr()))),
          single_Features(method(substr, 
              append_Formals(single_Formals(formal(arg, Int)), 
                single_Formals(formal(arg2, Int))),
              Str, 
              no_expr()))),
        filename);
  // 
  // insert into class_map
  //
  class_map[Object] = Object_class;
  class_map[IO]     = IO_class;
  class_map[Bool]   = Bool_class;
  class_map[Int]    = Int_class;
  class_map[Str]    = Str_class;
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
  return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
  error_stream << filename << ":" << t->get_line_number() << ": ";
  return semant_error();
}

ostream& ClassTable::semant_error()
{
  semant_errors++;
  return error_stream;
}

Symbol ClassTable::find_lca(Symbol name1, Symbol name2) const {
  const vector<Symbol> &v1 = inherit_map.find(name1)->second;
  const vector<Symbol> &v2 = inherit_map.find(name2)->second;
  int i = std::min(v1.size(), v2.size()) - 1;
  while (v1[i] != v2[i])
    --i;
  return v1[i];
}

void ClassTable::build_inherit_vectors_from(Symbol super) {
  if (inherit_map.find(super) != inherit_map.end()) return;
  Symbol parent = class_map[super]->get_parent();
  build_inherit_vectors_from(parent);
  vector<Symbol> &vec = inherit_map[super] = inherit_map[parent];
  vec.push_back(super);
}

void ClassTable::build_inherit_vectors() {
  inherit_map[Object].push_back(Object);
  for (map<Symbol, Class_>::iterator it = class_map.begin(); it != class_map.end(); ++it) {
    build_inherit_vectors_from(it->first);
  }
}

void ClassTable::build_members_from(Symbol super) {
  if (attribute_map.find(super) != attribute_map.end()) return;
  Class_ c = class_map[super];
  Symbol parent = c->get_parent();
  build_members_from(parent);

  attribute_map[super] = attribute_map[parent];
  signature_map[super] = signature_map[parent];
  Features fea = c->get_features();
  map<Symbol, Symbol> curr_attr,
      &pare_attr = attribute_map[parent],
      &supe_attr = (attribute_map[super] = pare_attr);
  map<Symbol, Signature> curr_sign,
      &pare_sign = signature_map[parent],
      &supe_sign = (signature_map[super] = pare_sign);

  for (int i = fea->first(); fea->more(i); i = fea->next(i)) {
    Feature f = fea->nth(i);
    if (typeid(*f) == typeid(method_class)) {
      method_class *meth = (method_class*)f;
      Formals formals = meth->get_formals();
      
      Signature sign(formals->len() + 1);
      sign.back() = meth->get_return_type();

      set<Symbol> formal_set;
      for (int j = formals->first(); formals->more(j); j = formals->next(j)) {
        Formal ff = formals->nth(j);
        sign[j] = ff->get_type_decl();

        if (ff->get_name() == self) {
          semant_error(c) << "Method cannot have any formal parameter named self.\n";
        }
        if (sign[j] == SELF_TYPE) {
          semant_error(c) << "Formal parameter '" << ff->get_name() << "' cannot have type SELF_TYPE.\n";
        }
        if (formal_set.find(ff->get_name()) != formal_set.end()) {
          semant_error(c) << "Formal parameter '" << ff->get_name()
              << "' is multiply defined in method '" << meth->get_name() << "'.\n";
        } else {
          formal_set.insert(ff->get_name());
        }
      }
      
      if (curr_sign.find(meth->get_name()) != curr_sign.end()) {
        semant_error(c) << "Redefinition of method '" << meth->get_name() << "' in class " << super << ".\n";
      } else if (pare_sign.find(meth->get_name()) != pare_sign.end() && pare_sign[meth->get_name()] != sign) {
        semant_error(c) << "Definition of override method '" << meth->get_name() << "' in class " << super
            << " has different method signature from an inherited class.\n";
      } else {
        curr_sign.insert(make_pair(meth->get_name(), sign));
        supe_sign.insert(make_pair(meth->get_name(), sign));
      }
    } else {
      attr_class *attr = (attr_class*)f;

      if (attr->get_name() == self) {
        semant_error(c) << "Class cannot have any attribute named self.\n";
      } else if (curr_attr.find(attr->get_name()) != curr_attr.end()) {
        semant_error(c) << "Redefinition of attribute '" << attr->get_name() << "' in class " << super << ".\n";
      } else if (pare_attr.find(attr->get_name()) != pare_attr.end()) {
        semant_error(c) << "Attribute '" << attr->get_name() << "' in class "
            << super << " is an attribute of an inherited class.\n";
      } else {
        curr_attr.insert(make_pair(attr->get_name(), attr->get_type_decl()));
        supe_attr.insert(make_pair(attr->get_name(), attr->get_type_decl()));
      }
    }
  }
}

void ClassTable::build_class_members() {
  attribute_map.insert(make_pair(Object, map<Symbol, Symbol>()));
  signature_map[Object][cool_abort].push_back(Object);
  signature_map[Object][type_name].push_back(Str);
  signature_map[Object][copy].push_back(SELF_TYPE);
  for (map<Symbol, Class_>::iterator it = class_map.begin(); it != class_map.end(); ++it) {
    build_members_from(it->first);
  }
  check_class_members();
}

void ClassTable::check_class_members() {
  for (map<Symbol, map<Symbol, Symbol> >::iterator i = attribute_map.begin(); i != attribute_map.end(); ++i) {
    if (i->first == Int || i->first == Str || i->first == Bool)
      continue;
    Class_ c = class_map[i->first];
    for (map<Symbol, Symbol>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
      if (j->second != SELF_TYPE && class_map.find(j->second) == class_map.end()) {
        semant_error(c) << "Undefined type " << j->second << " for attribute '" << j->first
            << "' in class " << i->first << ".\n";
      }
    }
  }
  for (map<Symbol, map<Symbol, Signature> >::iterator i = signature_map.begin(); i != signature_map.end(); ++i) {
    Class_ c = class_map[i->first];
    for (map<Symbol, Signature>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
      if (j->second.back() != SELF_TYPE && class_map.find(j->second.back()) == class_map.end()) {
        semant_error(c) << "Undefined return type " << j->second.back() << " of method '" << j->first
            << "' in class " << i->first << ".\n";
      }
      for (size_t k = 0; k + 1 < j->second.size(); ++j) {
        if (j->second[k] != SELF_TYPE && class_map.find(j->second[k]) == class_map.end()) {
          semant_error(c) << "Undefined type " << j->second[k] << " for " << k + 1
             << "th formal parameter in method '" << j->first << "'.\n";
        }
      }
    }
  }
}


Symbol ClassTable::find_attribute(Symbol name, Symbol attr) const {
  const map<Symbol, Symbol> &mp = attribute_map.find(name)->second;
  map<Symbol, Symbol>::const_iterator it = mp.find(attr);
  return it != mp.end() ? it->second : NULL;
}

Signature ClassTable::find_signature(Symbol name, Symbol method) const {
  const std::map<Symbol, Signature> &mp = signature_map.find(name)->second;
  std::map<Symbol, Signature>::const_iterator it = mp.find(method);
  return it != mp.end() ? it->second : Signature();
}

static ClassTable *classtable;
static SymbolTable<Symbol, Entry> *symboltable;
static Class_ curr_class;

bool ClassTable::check_if_A_is_B(Symbol name1, Symbol name2) const {
  const vector<Symbol> &vec = inherit_map.find(name1)->second;
  return std::find(vec.begin(), vec.end(), name2) != vec.end();
}

static bool new_check_if_A_is_B(Symbol name1, Symbol name2) {
  if (name1 == SELF_TYPE || name2 == SELF_TYPE) {
    if (name1 == name2) {
      return true;
    } else if (name1 == SELF_TYPE) {
      return classtable->check_if_A_is_B(curr_class->get_name(), name2);
    } else { // name2 == SELF_TYPE
      return false;
    }
  } else {
    return classtable->check_if_A_is_B(name1, name2);
  }
}

static Symbol new_find_lca(Symbol name1, Symbol name2) {
  if (name1 == SELF_TYPE && name2 == SELF_TYPE) {
    return SELF_TYPE;
  } else {
    return classtable->find_lca(
        name1 == SELF_TYPE ? curr_class->get_name() : name1,
        name2 == SELF_TYPE ? curr_class->get_name() : name2
    );
  }
}

#define SEMANT_ERROR classtable->semant_error(curr_class)

/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
     by setting the `type' field in each Expression node.
     (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
     */
void program_class::semant()
{
  initialize_constants();

  /* ClassTable constructor may do some semantic analysis */
  classtable = new ClassTable(classes);

  if (classtable->errors() > 0) {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }

  /* some semantic analysis code may go here */
  classtable->build_inherit_vectors();
  classtable->build_class_members();

  if (classtable->errors() > 0) {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }

  symboltable = new SymbolTable<Symbol, Entry>;
  symboltable->enterscope();
  symboltable->addid(self, SELF_TYPE);    // adding self here

  for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
    curr_class = classes->nth(i);
    // entering class scope
    symboltable->enterscope();
    classtable->add_symbol_from(curr_class->get_name());

    Features fea = curr_class->get_features();
    for (int j = fea->first(); fea->more(j); j = fea->next(j)) {
      Feature f = fea->nth(j);
      if (typeid(*f) == typeid(method_class)) {
        method_class *meth = (method_class*)f;
        Formals fs = meth->get_formals();
        // enter scope with parameters
        symboltable->enterscope();
        for (int k = fs->first(); fs->more(k); k = fs->next(k)) {
          Formal fo = fs->nth(k);
          symboltable->addid(fo->get_name(), fo->get_type_decl());
        }

        if (!new_check_if_A_is_B(meth->get_expr()->check_type(), meth->get_return_type())) {
          SEMANT_ERROR << "Inferred method body expression type " << meth->get_expr()->get_type()
              << " does not conform to declared method return type " << meth->get_return_type() << ".\n";
        }

        // exit method scope
        symboltable->exitscope();
      } else {
        attr_class *attr = (attr_class*)f;
        Symbol init_type = attr->get_init()->check_type();
        if (init_type != No_type && !new_check_if_A_is_B(init_type, attr->get_type_decl())) {
          SEMANT_ERROR << "Inferred attribute initializing expression type " << attr->get_init()->get_type()
              << " does not conform to declared attribute type " << attr->get_type_decl() << ".\n";
        }
      }
    }

    // exiting class scope
    symboltable->exitscope();
  }

  symboltable->exitscope();

  if (classtable->find_class(Main) == NULL) {
    classtable->semant_error() << "Class Main is not defined.\n";
  } else {
    const Signature &sign = classtable->find_signature(Main, main_meth); 
    if (sign.size() == 0) {
      classtable->semant_error() << "Method 'main' is not defined in Class Main.\n";
    } else if (sign.size() != 1) {
      classtable->semant_error() << "Method 'main' in Class Main must have no parameter.\n";
    }
  }

  if (classtable->errors() > 0) {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }
}

void ClassTable::add_symbol_from(Symbol name) const {
  const map<Symbol, Symbol> &mp = attribute_map.find(name)->second;
  for (map<Symbol, Symbol>::const_iterator it = mp.begin(); it != mp.end(); ++it) {
    symboltable->addid(it->first, it->second);
  }
}

// BEGIN: Expressions type checking routines

Symbol assign_class::check_type() {
  Symbol id_type = symboltable->lookup(name),
      expr_type = expr->check_type();
  if (name == self) {
    classtable->semant_error(curr_class) << "Cannot assign object to self.\n";
    return type = expr_type;
  }
  if (id_type == NULL) {
    classtable->semant_error(curr_class) << "Undefined identifier " << name << ".\n";
    id_type = Object;
  }
  if (!new_check_if_A_is_B(expr_type, id_type)) {
    classtable->semant_error(curr_class) << "Inferred expression type " << expr_type
        << " does not conform to declared identifier type " << id_type << " in the assignment expression.\n";
  }
  return type = expr_type;
}

Symbol dispatch_class::check_type() {
  Symbol expr_type = expr->check_type();

  vector<Symbol> actual_type(actual->len());
  for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
    actual_type[i] = actual->nth(i)->check_type();
  }
  
  Symbol disp_type = expr_type == SELF_TYPE ? curr_class->get_name() : expr_type; 
  const Signature &sign = classtable->find_signature(disp_type, name);
  if (sign.size() == 0) {
    classtable->semant_error(curr_class) << "Dispatch to undefined method " << name << " for class " << disp_type << ".\n";
    return type = Object;
  }

  // return type is expression type if it is SELF_TYPE
  type = sign.back() == SELF_TYPE ? expr_type : sign.back();
  if (sign.size() != actual_type.size() + 1) {
    classtable->semant_error(curr_class) << "Unmatched numbers of actual and formal parameters in dispatching " << name << ".\n";
    return type;
  }
  for (size_t i = 0; i < actual_type.size(); ++i) {
    if (!new_check_if_A_is_B(actual_type[i], sign[i])) {
      classtable->semant_error(curr_class) << "The inferred " << i + 1 << "th actual parameter type " << actual_type[i]
          << "does not conform to the declared corresponding formal parameter type " << sign[i] << ".\n";
    }
  }
  return type;
}

Symbol static_dispatch_class::check_type() {
  Symbol expr_type = expr->check_type();

  vector<Symbol> actual_type(actual->len());
  for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
    actual_type[i] = actual->nth(i)->check_type();
  }

  if (type_name == SELF_TYPE) {
    classtable->semant_error(curr_class) << "Static dispatching type cannot be SELF_TYPE.\n";
    return type = Object;
  }

  if (!new_check_if_A_is_B(expr_type, type_name)) {
    classtable->semant_error(curr_class) << "Inferred expression type " << expr_type
        << " does not conform to static dispatch type " << type_name << ".\n";
  }

  const Signature &sign = classtable->find_signature(type_name, name);
  if (sign.size() == 0) {
    classtable->semant_error(curr_class) << "Dispatch to undefined method " << name << " for class " << type_name << ".\n";
    return type = Object;
  }

  // return type is expression type if it is SELF_TYPE
  type = sign.back() == SELF_TYPE ? expr_type : sign.back();
  if (sign.size() != actual_type.size() + 1) {
    classtable->semant_error(curr_class) << "Unmatched numbers of actual and formal parameters in dispatching " << name << ".\n";
    return type;
  }
  for (size_t i = 0; i < actual_type.size(); ++i) {
    if (!new_check_if_A_is_B(actual_type[i], sign[i])) {
      classtable->semant_error(curr_class) << "The inferred " << i + 1 << "th actual parameter type " << actual_type[i]
          << "does not conform to the declared corresponding formal parameter type " << sign[i] << ".\n";
    }
  }
  return type;
}

Symbol cond_class::check_type() {
  Symbol pred_type = pred->check_type(),
         then_type = then_exp->check_type(),
         else_type = else_exp->check_type();
  if (pred_type != Bool) {
    classtable->semant_error(curr_class) << "Predictive expression type must be Bool in 'if-else' expressions.\n";
  }
  return type = new_find_lca(then_type, else_type);
}

Symbol loop_class::check_type() {
  if (pred->check_type() != Bool) {
    classtable->semant_error(curr_class) << "Predictive expression type must be Bool in 'while-loop' expressions.\n";
  }
  body->check_type();
  return type = Object;
}

Symbol block_class::check_type() {
  for (int i = body->first(); body->more(i); i = body->next(i)) {
    type = body->nth(i)->check_type();
  }
  return type;
}

Symbol let_class::check_type() {
  Symbol init_type = init->check_type();
  if (init_type != No_type && !new_check_if_A_is_B(init_type, type_decl)) {
    classtable->semant_error(curr_class) << "The inferred initializing expression type " << init_type
        << " does not conform to declared identifier type " << type_decl << " in 'let' exprssion.\n";
  }
  symboltable->enterscope();
  if (identifier != self) {
    symboltable->addid(identifier, type_decl);
  } else {
    SEMANT_ERROR << "'self' cannot be bound in a 'let' expression.\n";
  }
  type = body->check_type();
  symboltable->exitscope();
  return type;
}

Symbol typcase_class::check_type() {
  expr->check_type();
  std::set<Symbol> branch_types;
  type = NULL;
  for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
    Case ca = cases->nth(i);
    symboltable->enterscope();
    if (branch_types.find(ca->get_type_decl()) != branch_types.end()) {
      SEMANT_ERROR << "Duplicate branch type " << ca->get_type_decl() << " in 'case' statement.\n";
      symboltable->addid(ca->get_name(), ca->get_type_decl());
    } else if (classtable->find_class(ca->get_type_decl()) == NULL) {
      SEMANT_ERROR << "Undefined branch type " << ca->get_type_decl() << " in 'case' statement.\n";
      symboltable->addid(ca->get_name(), Object);
    } else {
      branch_types.insert(ca->get_type_decl());
      symboltable->addid(ca->get_name(), ca->get_type_decl());
    }
    
    Symbol expr_type = ca->get_expr()->check_type();
    type = type == NULL ? expr_type : new_find_lca(expr_type, type);

    symboltable->exitscope();
  }
  return type;
}

Symbol new__class::check_type() {
  if (type_name != SELF_TYPE && classtable->find_class(type_name) == NULL) {
    classtable->semant_error(curr_class) << "Undefined type " << type_name << " for 'new' expresssions.\n";
    return type = Object;
  } else {
    return type = type_name;
  }
}

Symbol isvoid_class::check_type() {
  e1->check_type();
  return type = Bool;
}

Symbol plus_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (e1_type != Int || e2_type != Int) {
    SEMANT_ERROR << "Arithmetical operators is only valid for Int expressions.\n";
  }
  return type = Int;
}

Symbol sub_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (e1_type != Int || e2_type != Int) {
    SEMANT_ERROR << "Arithmetical operators is only valid for Int expressions.\n";
  }
  return type = Int;
}

Symbol mul_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (e1_type != Int || e2_type != Int) {
    SEMANT_ERROR << "Arithmetical operators is only valid for Int expressions.\n";
  }
  return type = Int;
}

Symbol divide_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (e1_type != Int || e2_type != Int) {
    SEMANT_ERROR << "Arithmetical operators is only valid for Int expressions.\n";
  }
  return type = Int;
}

Symbol neg_class::check_type() {
  if (e1->check_type() != Int) {
    SEMANT_ERROR << "Negative operator is only valid for Int expressions.\n";
  }
  return type = Int;
}

Symbol lt_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (e1_type != Int || e2_type != Int) {
    SEMANT_ERROR << "Comparative operators is only valid for Int expressions.\n";
  }
  return type = Bool;
}

Symbol leq_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (e1_type != Int || e2_type != Int) {
    SEMANT_ERROR << "Comparative operators is only valid for Int expressions.\n";
  }
  return type = Bool;
}

Symbol eq_class::check_type() {
  Symbol e1_type = e1->check_type(),
         e2_type = e2->check_type();
  if (
    (e1_type == Int || e1_type == Bool || e1_type == Str ||
    e2_type == Int || e2_type == Bool || e2_type == Str) && e1_type != e2_type
  ) {
    SEMANT_ERROR << "Int, Bool and String expressions can only compared to the same type respectively.\n";
  }
  return type = Bool;
}

Symbol comp_class::check_type() {
  if (e1->check_type() != Bool) {
    SEMANT_ERROR << "Not operator is only valid for Bool expressions.\n";
  }
  return type = Bool;
}

Symbol object_class::check_type() {
  type = symboltable->lookup(name);
  if (type == NULL) {
    classtable->semant_error(curr_class) << "Undefined identifier " << name << ".\n";
    type = Object;
  }
  return type;
}

Symbol int_const_class::check_type() {
  return type = Int;
}

Symbol string_const_class::check_type() {
  return type = Str;
}

Symbol bool_const_class::check_type() {
  return type = Bool;
}

// only appears in let-no-init or attr-no-init
Symbol no_expr_class::check_type() {
  return type = No_type;
}

// END:   EXpressions type checking routines
