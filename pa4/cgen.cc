
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include <algorithm>
#include <typeinfo>
#include "cgen.h"
#include "cgen_gc.h"

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol 
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

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


//  BoolConst is a class that implements code generation for operations
//  on the two booleans, which are given global names here.
BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void program_class::cgen(ostream &os) 
{
  // spim wants comments to start with '#'
  os << "# start of generated code\n";

  initialize_constants();
  CgenClassTable *codegen_classtable = new CgenClassTable(classes,os);

  os << "\n# end of generated code\n";
}

Symbol method_class::get_name() const {
  return name;
}

Symbol attr_class::get_name() const {
  return name;
}

Symbol formal_class::get_name() const {
  return name;
}

//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_load(char *dest_reg, int offset, char *source_reg, ostream& s)
{
  s << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" 
    << endl;
}

static void emit_store(char *source_reg, int offset, char *dest_reg, ostream& s)
{
  s << SW << source_reg << " " << offset * WORD_SIZE << "(" << dest_reg << ")"
      << endl;
}

static void emit_load_imm(char *dest_reg, int val, ostream& s)
{ s << LI << dest_reg << " " << val << endl; }

static void emit_load_address(char *dest_reg, char *address, ostream& s)
{ s << LA << dest_reg << " " << address << endl; }

static void emit_partial_load_address(char *dest_reg, ostream& s)
{ s << LA << dest_reg << " "; }

static void emit_load_bool(char *dest, const BoolConst& b, ostream& s)
{
  emit_partial_load_address(dest,s);
  b.code_ref(s);
  s << endl;
}

static void emit_load_string(char *dest, StringEntry *str, ostream& s)
{
  emit_partial_load_address(dest,s);
  str->code_ref(s);
  s << endl;
}

static void emit_load_int(char *dest, IntEntry *i, ostream& s)
{
  emit_partial_load_address(dest,s);
  i->code_ref(s);
  s << endl;
}

static void emit_move(char *dest_reg, char *source_reg, ostream& s)
{ s << MOVE << dest_reg << " " << source_reg << endl; }

static void emit_neg(char *dest, char *src1, ostream& s)
{ s << NEG << dest << " " << src1 << endl; }

static void emit_add(char *dest, char *src1, char *src2, ostream& s)
{ s << ADD << dest << " " << src1 << " " << src2 << endl; }

static void emit_addu(char *dest, char *src1, char *src2, ostream& s)
{ s << ADDU << dest << " " << src1 << " " << src2 << endl; }

static void emit_addiu(char *dest, char *src1, int imm, ostream& s)
{ s << ADDIU << dest << " " << src1 << " " << imm << endl; }

static void emit_div(char *dest, char *src1, char *src2, ostream& s)
{ s << DIV << dest << " " << src1 << " " << src2 << endl; }

static void emit_mul(char *dest, char *src1, char *src2, ostream& s)
{ s << MUL << dest << " " << src1 << " " << src2 << endl; }

static void emit_sub(char *dest, char *src1, char *src2, ostream& s)
{ s << SUB << dest << " " << src1 << " " << src2 << endl; }

static void emit_sll(char *dest, char *src1, int num, ostream& s)
{ s << SLL << dest << " " << src1 << " " << num << endl; }

static void emit_jalr(char *dest, ostream& s)
{ s << JALR << "\t" << dest << endl; }

static void emit_jal(char *address,ostream &s)
{ s << JAL << address << endl; }

static void emit_return(ostream& s)
{ s << RET << endl; }

static void emit_gc_assign(ostream& s)
{ s << JAL << "_GenGC_Assign" << endl; }

static void emit_disptable_ref(Symbol sym, ostream& s)
{  s << sym << DISPTAB_SUFFIX; }

static inline void emit_disptable_def(Symbol sym, ostream &s) {
  emit_disptable_ref(sym, s); s << LABEL;
}

static inline void emit_load_disptable(char *dist, Symbol sym, ostream &s) {
  emit_partial_load_address(dist, s);
  emit_disptable_ref(sym, s);
  s << '\n';
}

static void emit_init_ref(Symbol sym, ostream& s)
{ s << sym << CLASSINIT_SUFFIX; }

static void emit_init_def(Symbol sym, ostream& s)
{ emit_init_ref(sym, s); s << LABEL; }

static inline void emit_call_init(Symbol sym, ostream &s) {
  s << JAL;
  emit_init_ref(sym, s);
  s << '\n';
}

static void emit_label_ref(int l, ostream &s)
{ s << "label" << l; }

static void emit_protobj_ref(Symbol sym, ostream& s)
{ s << sym << PROTOBJ_SUFFIX; }

static inline void emit_protobj_def(Symbol sym, ostream& s)
{ emit_protobj_ref(sym, s); s << LABEL; }

static inline void emit_load_protobj(char *dist, Symbol sym, ostream &s) {
  emit_partial_load_address(dist, s);
  emit_protobj_ref(sym, s);
  s << '\n';
}

static void emit_method_ref(Symbol classname, Symbol methodname, ostream& s)
{ s << classname << METHOD_SEP << methodname; }

static void inline emit_method_def(Symbol classname, Symbol methodname, ostream& s)
{ emit_method_ref(classname, methodname, s); s << LABEL; }

static void inline emit_call_method(Symbol classname, Symbol methodname, ostream &s) {
  s << JAL;
  emit_method_ref(classname, methodname, s);
  s << '\n';
}

static void emit_label_def(int l, ostream &s)
{
  emit_label_ref(l,s);
  s << ":" << endl;
}

static void emit_beqz(char *source, int label, ostream &s)
{
  s << BEQZ << source << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_beq(char *src1, char *src2, int label, ostream &s)
{
  s << BEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bne(char *src1, char *src2, int label, ostream &s)
{
  s << BNE << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bleq(char *src1, char *src2, int label, ostream &s)
{
  s << BLEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blt(char *src1, char *src2, int label, ostream &s)
{
  s << BLT << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blti(char *src1, int imm, int label, ostream &s)
{
  s << BLT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bgti(char *src1, int imm, int label, ostream &s)
{
  s << BGT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_branch(int l, ostream& s)
{
  s << BRANCH;
  emit_label_ref(l,s);
  s << endl;
}

//
// Push a register on the stack. The stack grows towards smaller addresses.
//
static void emit_push(char *reg, ostream& str)
{
  emit_store(reg,0,SP,str);
  emit_addiu(SP,SP,-4,str);
}

//
// Fetch the integer value in an Int object.
// Emits code to fetch the integer value of the Integer object pointed
// to by register source into the register dest
//
static void emit_fetch_int(char *dest, char *source, ostream& s)
{ emit_load(dest, DEFAULT_OBJFIELDS, source, s); }

//
// Emits code to store the integer value contained in register source
// into the Integer object pointed to by dest.
//
static void emit_store_int(char *source, char *dest, ostream& s)
{ emit_store(source, DEFAULT_OBJFIELDS, dest, s); }


static void emit_test_collector(ostream &s)
{
  emit_push(ACC, s);
  emit_move(ACC, SP, s); // stack end
  emit_move(A1, ZERO, s); // allocate nothing
  s << JAL << gc_collect_names[cgen_Memmgr] << endl;
  emit_addiu(SP,SP,4,s);
  emit_load(ACC,0,SP,s);
}

static void emit_gc_check(char *source, ostream &s)
{
  if (source != (char*)A1) emit_move(A1, source, s);
  s << JAL << "_gc_check" << endl;
}

static void emit_enter_function(ostream &s) {
  emit_addiu(SP, SP, -3 * WORD_SIZE, s);
  emit_store(FP, 3, SP, s);
  emit_store(SELF, 2, SP, s);
  emit_store(RA, 1, SP, s);
  emit_addiu(FP, SP, WORD_SIZE, s);
  emit_move(SELF, ACC, s);
}

static void emit_exit_function(int cc, ostream &s) {
  // there is no need to copy self to acc
  // the result can be other value than self
  emit_load(FP, 3, SP, s);
  emit_load(SELF, 2, SP, s);
  emit_load(RA, 1, SP, s);
  emit_addiu(SP, SP, (3 + cc) * WORD_SIZE, s);
  emit_return(s);
}

///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type StringEntry.  StringEntry methods are defined both for String
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream& s)
{
  s << STRCONST_PREFIX << index;
}

//
// Emit code for a constant String.
// You should fill in the code naming the dispatch table.
//

void StringEntry::code_def(ostream& s, int stringclasstag)
{
  IntEntryP lensym = inttable.add_int(len);

  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s  << LABEL                                             // label
      << WORD << stringclasstag << endl                                 // tag
      << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len+4)/4) << endl // size
      << WORD;

 /***** Add dispatch information for class String ******/
      emit_disptable_ref(Str, s);

      s << endl;                                              // dispatch table
      s << WORD;  lensym->code_ref(s);  s << endl;            // string length
  emit_string_constant(s,str);                                // ascii string
  s << ALIGN;                                                 // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the 
// stringtable.
//
void StrTable::code_string_table(ostream& s, int stringclasstag)
{  
  for (List<StringEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,stringclasstag);
}

//
// Ints
//
void IntEntry::code_ref(ostream &s)
{
  s << INTCONST_PREFIX << index;
}

//
// Emit code for a constant Integer.
// You should fill in the code naming the dispatch table.
//

void IntEntry::code_def(ostream &s, int intclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                // label
      << WORD << intclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl  // object size
      << WORD; 

 /***** Add dispatch information for class Int ******/
      emit_disptable_ref(Int, s);

      s << endl;                                          // dispatch table
      s << WORD << str << endl;                           // integer value
}


//
// IntTable::code_string_table
// Generate an Int object definition for every Int constant in the
// inttable.
//
void IntTable::code_string_table(ostream &s, int intclasstag)
{
  for (List<IntEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,intclasstag);
}


//
// Bools
//
BoolConst::BoolConst(int i) : val(i) { assert(i == 0 || i == 1); }

void BoolConst::code_ref(ostream& s) const
{
  s << BOOLCONST_PREFIX << val;
}
  
//
// Emit code for a constant Bool.
// You should fill in the code naming the dispatch table.
//

void BoolConst::code_def(ostream& s, int boolclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                  // label
      << WORD << boolclasstag << endl                       // class tag
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl   // object size
      << WORD;

 /***** Add dispatch information for class Bool ******/
      emit_disptable_ref(Bool, s);

      s << endl;                                            // dispatch table
      s << WORD << val << endl;                             // value (0 or 1)
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//***************************************************
//
//  Emit code to start the .data segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_data()
{
  Symbol main    = idtable.lookup_string(MAINNAME);
  Symbol string  = idtable.lookup_string(STRINGNAME);
  Symbol integer = idtable.lookup_string(INTNAME);
  Symbol boolc   = idtable.lookup_string(BOOLNAME);

  str << "\t.data\n" << ALIGN;
  //
  // The following global names must be defined first.
  //
  str << GLOBAL << CLASSNAMETAB << endl;
  str << GLOBAL; emit_protobj_ref(main,str);    str << endl;
  str << GLOBAL; emit_protobj_ref(integer,str); str << endl;
  str << GLOBAL; emit_protobj_ref(string,str);  str << endl;
  str << GLOBAL; falsebool.code_ref(str);  str << endl;
  str << GLOBAL; truebool.code_ref(str);   str << endl;
  str << GLOBAL << INTTAG << endl;
  str << GLOBAL << BOOLTAG << endl;
  str << GLOBAL << STRINGTAG << endl;

  //
  // We also need to know the tag of the Int, String, and Bool classes
  // during code generation.
  //
  str << INTTAG << LABEL
      << WORD << intclasstag << endl;
  str << BOOLTAG << LABEL 
      << WORD << boolclasstag << endl;
  str << STRINGTAG << LABEL 
      << WORD << stringclasstag << endl;    
}


//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_text()
{
  str << GLOBAL << HEAP_START << endl
      << HEAP_START << LABEL 
      << WORD << 0 << endl
      << "\t.text" << endl
      << GLOBAL;
  emit_init_ref(idtable.add_string("Main"), str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Int"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("String"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Bool"),str);
  str << endl << GLOBAL;
  emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
  str << endl;
}

void CgenClassTable::code_bools(int boolclasstag)
{
  falsebool.code_def(str,boolclasstag);
  truebool.code_def(str,boolclasstag);
}

void CgenClassTable::code_select_gc()
{
  //
  // Generate GC choice constants (pointers to GC functions)
  //
  str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
  str << "_MemMgr_INITIALIZER:" << endl;
  str << WORD << gc_init_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
  str << "_MemMgr_COLLECTOR:" << endl;
  str << WORD << gc_collect_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_TEST" << endl;
  str << "_MemMgr_TEST:" << endl;
  str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}


//********************************************************
//
// Emit code to reserve space for and initialize all of
// the constants.  Class names should have been added to
// the string table (in the supplied code, is is done
// during the construction of the inheritance graph), and
// code for emitting string constants as a side effect adds
// the string's length to the integer table.  The constants
// are emmitted by running through the stringtable and inttable
// and producing code for each entry.
//
//********************************************************

void CgenClassTable::code_constants()
{
  //
  // Add constants that are required by the code generator.
  //
  stringtable.add_string("");
  inttable.add_string("0");

  stringtable.code_string_table(str,stringclasstag);
  inttable.code_string_table(str,intclasstag);
  code_bools(boolclasstag);
}


CgenClassTable::CgenClassTable(Classes classes, ostream& s) : nds(NULL) , str(s)
{
   // Object IO Int Bool String ...
   stringclasstag = 4 /* Change to your String class tag here */;
   intclasstag =    2 /* Change to your Int class tag here */;
   boolclasstag =   3 /* Change to your Bool class tag here */;

   enterscope();
   if (cgen_debug) cout << "Building CgenClassTable" << endl;
   install_basic_classes();
   install_classes(classes);
   build_inheritance_tree();

   code();
   exitscope();
}

void CgenClassTable::install_basic_classes()
{

// The tree package uses these globals to annotate the classes built below.
  //curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");

//
// A few special class names are installed in the lookup table but not
// the class list.  Thus, these classes exist, but are not part of the
// inheritance hierarchy.
// No_class serves as the parent of Object and the other special classes.
// SELF_TYPE is the self class; it cannot be redefined or inherited.
// prim_slot is a class known to the code generator.

/* DO NOT NEED
  addid(No_class,
	new CgenNode(class_(No_class,No_class,nil_Features(),filename),
			    Basic,this));
  addid(SELF_TYPE,
	new CgenNode(class_(SELF_TYPE,No_class,nil_Features(),filename),
			    Basic,this));
  addid(prim_slot,
	new CgenNode(class_(prim_slot,No_class,nil_Features(),filename),
			    Basic,this));
*/

// 
// The Object class has no parent class. Its methods are
//        cool_abort() : Object    aborts the program
//        type_name() : Str        returns a string representation of class name
//        copy() : SELF_TYPE       returns a copy of the object
//
// There is no need for method bodies in the basic classes---these
// are already built in to the runtime system.
//
  install_class(
   new CgenNode(
    class_(Object, 
	   No_class,
	   append_Features(
           append_Features(
           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
           single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	   filename),
    Basic,this));

// 
// The IO class inherits from Object. Its methods are
//        out_string(Str) : SELF_TYPE          writes a string to the output
//        out_int(Int) : SELF_TYPE               "    an int    "  "     "
//        in_string() : Str                    reads a string from the input
//        in_int() : Int                         "   an int     "  "     "
//
   install_class(
    new CgenNode(
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
	   filename),	    
    Basic,this));

//
// The Int class has no methods and only a single attribute, the
// "val" for the integer. 
//
   install_class(
    new CgenNode(
     class_(Int, 
	    Object,
            single_Features(attr(val, prim_slot, no_expr())),
	    filename),
     Basic,this));

//
// Bool also has only the "val" slot.
//
    install_class(
     new CgenNode(
      class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename),
      Basic,this));

//
// The class Str has a number of slots and operations:
//       val                                  ???
//       str_field                            the string itself
//       length() : Int                       length of the string
//       concat(arg: Str) : Str               string concatenation
//       substr(arg: Int, arg2: Int): Str     substring
//       
   install_class(
    new CgenNode(
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
	     filename),
        Basic,this));

}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_class(CgenNodeP nd)
{
  Symbol name = nd->get_name();

  if (probe(name))
    {
      return;
    }

  // The class name is legal, so add it to the list of classes
  // and the symbol table.
  nds = new List<CgenNode>(nd,nds);
  addid(name,nd);
}

void CgenClassTable::install_classes(Classes cs)
{
  for(int i = cs->first(); cs->more(i); i = cs->next(i))
    install_class(new CgenNode(cs->nth(i),NotBasic,this));
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree()
{
  for(List<CgenNode> *l = nds; l; l = l->tl())
      set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd)
{
  CgenNode *parent_node = probe(nd->get_parent());
  if (parent_node != NULL) {
    nd->set_parentnd(parent_node);
    parent_node->add_child(nd);
  }
}

void CgenNode::add_child(CgenNodeP n)
{
  children = new List<CgenNode>(n,children);
}

void CgenNode::set_parentnd(CgenNodeP p)
{
  assert(parentnd == NULL);
  assert(p != NULL);
  parentnd = p;
}

struct SymInfo {
  Symbol type;
  int offset;
  SymInfo(Symbol t = NULL, int o = 0): type(t), offset(o) {}
};

static SymbolTable<Symbol, SymInfo> *symtab;
static CgenClassTable *classtable;
static CgenNode *curr_class;        // for dispatching

void CgenClassTable::code()
{
  if (cgen_debug) cout << "coding global data" << endl;
  code_global_data();

  if (cgen_debug) cout << "choosing gc" << endl;
  code_select_gc();

  std::vector<StringEntry*> nametab;
  nametab.push_back(stringtable.add_string("Object"));
  nametab.push_back(stringtable.add_string("IO"));
  nametab.push_back(stringtable.add_string("Int"));
  nametab.push_back(stringtable.add_string("Bool"));
  nametab.push_back(stringtable.add_string("String"));
  for (List<CgenNode>* l = nds; l; l = l->tl()) {
    int i; Symbol name = l->hd()->name;
    for (i = 0; i < 5; ++i)
      if (strcmp(nametab[i]->get_string(), name->get_string()) == 0)
        break;
    if (i != 5) continue;
    nametab.push_back(stringtable.add_string(name->get_string()));
  }

  if (cgen_debug) cout << "coding constants" << endl;
  code_constants();

//                 Add your code to emit
//                   - prototype objects
//                   - class_nameTab
//                   - dispatch tables
  
  int curr_class_tag = 4;
  for (List<CgenNode>* l = nds; l; l = l->tl()) {
    int i; Symbol name = l->hd()->name;
    for (i = 0; i < 5; ++i)
      if (strcmp(nametab[i]->get_string(), name->get_string()) == 0)
        break;
    if (i != 5) {
      l->hd()->set_class_tag(i);
    } else {
      l->hd()->set_class_tag(++curr_class_tag);
    }
    l->hd()->build_offset_tables();
  }

  if (cgen_debug) cout << "coding class name table\n";
  str << CLASSNAMETAB << LABEL;
  for (int i = 0; (size_t)i < nametab.size(); ++i) {
    str << WORD;
    nametab[i]->code_ref(str);
    str << "\n";
  }

  if (cgen_debug) cout << "coding class prototype object table\n";    // for new SELF_TYPE
  str << CLASSOBJTAB << LABEL;
  for (int i = 0; (size_t)i < nametab.size(); ++i) {
    str << WORD; emit_protobj_ref(nametab[i], str); str << "\n";
    str << WORD; emit_init_ref(nametab[i], str); str << "\n";
  }  

  if (cgen_debug) cout << "coding dispatch tables\n";
  for (List<CgenNode>* l = nds; l; l = l->tl()) {
    l->hd()->generate_dispatch_table(str);
  }

  if (cgen_debug) cout << "coding class prototype objects\n";
  for (List<CgenNode>* l = nds; l; l = l->tl()) {
    l->hd()->generate_prototype_object(str);
  }

  if (cgen_debug) cout << "coding global text" << endl;
  code_global_text();

//                 Add your code to emit
//                   - object initializer
//                   - the class methods
//                   - etc...
  
  // basic class init routines
  emit_init_def(Object, str);
  emit_return(str);
  emit_init_def(IO, str);
  emit_return(str);
  emit_init_def(Int, str);
  emit_return(str);
  emit_init_def(Bool, str);
  emit_return(str);
  emit_init_def(Str, str);
  emit_return(str);
  str << "main:\n";     // a working around for grading system, which is a useless label

  classtable = this;
  symtab = new SymbolTable<Symbol, SymInfo>;

  for (List<CgenNode>* l = nds; l; l = l->tl()) {
    if (l->hd()->basic()) continue;
    symtab->enterscope();
    curr_class = l->hd();
    l->hd()->generate_initializing_routine(str);
    l->hd()->generate_method_code(str);
    symtab->exitscope();
  }
  
}

CgenNodeP CgenClassTable::root()
{
   return probe(Object);
}


///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) :
   class__class((const class__class &) *nd),
   parentnd(NULL),
   children(NULL),
   basic_status(bstatus)
{ 
   stringtable.add_string(name->get_string());          // Add class name to string table
}

void CgenNode::build_offset_tables() {
  if (method_table.size() > 0) return;
  if (name != Object) {
    parentnd->build_offset_tables();
    attr_table = parentnd->attr_table;
    attr_type_table = parentnd->attr_type_table;
    method_table = parentnd->method_table;
    method_class_table = parentnd->method_class_table;
  }
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    Feature f = features->nth(i);
    if (typeid(*f) == typeid(attr_class)) {
      attr_table.push_back(f->get_name());
      attr_type_table.push_back(((attr_class*)f)->type_decl);
    } else {
      std::vector<Symbol>::iterator it = std::find(method_table.begin(), method_table.end(), f->get_name());
      if (it == method_table.end()) {
        method_table.push_back(f->get_name());
        method_class_table.push_back(name);
        method_class *meth = (method_class*)f;
      } else {
        method_class_table[it - method_table.begin()] = name;
      }
    }
  }
}

void CgenNode::generate_dispatch_table(ostream &s) const {
  emit_disptable_def(name, s);
  for (int i = 0; (size_t)i < method_table.size(); ++i) {
    s << WORD;
    emit_method_ref(method_class_table[i], method_table[i], s);
    s << "\n";
  }
}

void CgenNode::generate_prototype_object(ostream &s) const {
  s << WORD << "-1" << endl;                                  // -1 eye tag
  emit_protobj_def(name, s);                                  // Lable
  s << WORD << class_tag << endl                              // tag
    << WORD << (DEFAULT_OBJFIELDS + attr_table.size()) << endl   // size
    << WORD;
  emit_disptable_ref(name, s);
  s << endl;                                                  // dispatch table
  for (int i = 0; (size_t)i < attr_table.size(); ++i) {
    if (attr_type_table[i] == Str) {
      s << WORD;
      stringtable.lookup_string("")->code_ref(s);
      s << '\n';
    } else if (attr_type_table[i] == Int) {
      s << WORD;
      inttable.lookup_string("0")->code_ref(s);
      s << '\n';
    } else if (attr_type_table[i] == Bool) {
      s << WORD;
      falsebool.code_ref(s);
      s << '\n';
    } else {
      s << WORD << "0\n";
    }
  }
}

static int curr_temp_offset;

static inline int self_offset(int i) {
  return (0 << 24) | (i + DEFAULT_OBJFIELDS);
}

void CgenNode::generate_initializing_routine(ostream &s) {
  // notice: emit_gc_assign when cgen_Memmgr != GC_NOGC
  for (int i = 0; (size_t)i < attr_table.size(); ++i) {
    symtab->addid(attr_table[i], new SymInfo(attr_type_table[i], self_offset(i)));
  }
  emit_init_def(name, s);
  emit_enter_function(s);
  curr_temp_offset = 1;

  // emit_move(ACC, SELF, s);   // acc is already self
  emit_call_init(parent, s);
  // emit_move(SELF, ACC);      // self is already restored

  int cc = (int)parentnd->attr_table.size();
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    Feature f = features->nth(i);
    if (typeid(*f) == typeid(attr_class)) {
      attr_class *attr = (attr_class*)f;
      if (attr->init->type != No_type && attr->init->type != NULL) {
        attr->init->code(s);
        emit_store(ACC, cc + DEFAULT_OBJFIELDS, SELF, s);
        if (cgen_Memmgr != GC_NOGC) {
          emit_addiu(A1, SELF, (cc + DEFAULT_OBJFIELDS) * WORD_SIZE, s);
          emit_gc_assign(s);
        }
      }
      ++cc;
    }
  }
  emit_move(ACC, SELF, s);
  emit_exit_function(0, s);
  // emit_return(s);
}

static int curr_label_number;         // used for LABELXX:

static inline int para_offset(int i) {  // range from 0 to n - 1, $fp offset
  return (1 << 24) | i;
}

static int count_formals(Formals formals) {
  int cc = 0;
  for (int i = formals->first(); formals->more(i); i = formals->next(i))
    ++cc;
  for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
    formal_class* f = (formal_class*)formals->nth(i);
    symtab->addid(f->name, new SymInfo(f->type_decl, para_offset(cc - 1 - i + 3)));
  }
  return cc;
}

static inline int temp_offset(int i) {  // starting from 1, $fp offset
  return -i;
}

void CgenNode::generate_method_code(ostream &s) {
  // notice: emit_gc_assign when cgen_Memmgr != GC_NOGC
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    Feature f = features->nth(i);
    if (typeid(*f) == typeid(method_class)) {
      method_class *meth = (method_class*)f;
      symtab->enterscope();
      int formal_cnt = count_formals(meth->formals);

      emit_method_def(name, meth->name, s);
      emit_enter_function(s);
      curr_temp_offset = 1;

      meth->expr->code(s);

      emit_exit_function(formal_cnt, s);
      // emit_return(s);
      symtab->exitscope();
    }
  }
}

int CgenNode::find_method_offset(Symbol sym) const {
  return std::find(method_table.begin(), method_table.end(), sym) - method_table.begin();
}

Symbol CgenNode::find_method_defining_class(Symbol sym) const {
  int i = find_method_offset(sym);
  if (i == (int)method_class_table.size()) {
    return NULL;
  } else {
    return method_class_table[i];
  }
}

//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************

void assign_class::code(ostream &s) {
  expr->code(s);

  int offset = symtab->lookup(name)->offset;
  switch (offset >> 24) {
   case 0:
    emit_store(ACC, offset &= ~(0xff << 24), SELF, s);
    if (cgen_Memmgr != GC_NOGC) {
      emit_addiu(A1, SELF, offset * WORD_SIZE, s);
      emit_gc_assign(s);
    }
    break;
   case 1:
    emit_store(ACC, offset &= ~(0xff << 24), FP, s);
/*    if (cgen_Memmgr != GC_NOGC) {
      emit_addiu(A1, FP, offset * WORD_SIZE, s);
      emit_gc_assign(s);
    }*/
    break;
   default:
    emit_store(ACC, offset, FP, s);
/*    if (cgen_Memmgr != GC_NOGC) {
      emit_addiu(A1, FP, offset * WORD_SIZE, s);
      emit_gc_assign(s);
    } */
    break;
  }
  // ACC is already stored value
}

void static_dispatch_class::code(ostream &s) {
  int cc = 0;
  for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
    actual->nth(i)->code(s);
    emit_push(ACC, s);
    ++curr_temp_offset; ++cc;
  }
  expr->code(s);
  emit_bne(ACC, ZERO, curr_label_number, s);  // goto call_fun
  emit_load_string(ACC, (StringEntry*)curr_class->filename, s);
  emit_load_imm(T1, 1, s);
  emit_jal("_dispatch_abort", s);
  emit_label_def(curr_label_number++, s);     // call_fun:
  // notice: `type_name' may be not the class defining method `name', but `name'
  //         can be defined by one of the super classes
  Symbol class_name = classtable->lookup(type_name)->find_method_defining_class(name);
  emit_call_method(class_name, name, s);     // will pop automatically
  curr_temp_offset -= cc;   // restore curr_temp_offset manually
}

void dispatch_class::code(ostream &s) {
  int cc = 0;
  for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
    actual->nth(i)->code(s);
    emit_push(ACC, s);
    ++curr_temp_offset; ++cc;
  }
  expr->code(s);
  emit_bne(ACC, ZERO, curr_label_number, s);  // goto call_fun
  emit_load_string(ACC, (StringEntry*)curr_class->filename, s);
  emit_load_imm(T1, 1, s);
  emit_jal("_dispatch_abort", s);
  emit_label_def(curr_label_number++, s);     // call_fun:
  emit_load(T1, DISPTABLE_OFFSET, ACC, s);
  int offset;
  if (expr->type != SELF_TYPE) {
    offset = classtable->lookup(expr->type)->find_method_offset(name);
  } else {
    offset = curr_class->find_method_offset(name);
  }

  emit_load(T1, offset, T1, s);
  emit_jalr(T1, s);
  curr_temp_offset -= cc;
}

void cond_class::code(ostream &s) {
  pred->code(s);
  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);
  emit_beq(ACC, ZERO, base_label_number, s);    // goto false_brach
  then_exp->code(s);
  emit_branch(base_label_number + 1, s);        // goto end_if
  emit_label_def(base_label_number, s);         // false_branch:
  else_exp->code(s);
  emit_label_def(base_label_number + 1, s);     // end_if:
}

void loop_class::code(ostream &s) {
  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_label_def(base_label_number, s);         // begin_loop:
  pred->code(s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);
  emit_beq(ACC, ZERO, base_label_number + 1, s);// goto end_loop
  body->code(s);
  emit_branch(base_label_number, s);            // goto begin_loop
  emit_label_def(base_label_number + 1, s);     // end_loop:
}

struct CaseInfo {
  int temp_offset;
  int exit_point;
  ostream *sp;
};

struct BranchComp {
  Symbol type_decl;
  bool operator () (branch_class *bc) {
    return bc->type_decl == type_decl;
  }
  BranchComp(Symbol t): type_decl(t) {}
};

void CgenNode::travel(const std::vector<branch_class*> &case_vector, int case_index, struct CaseInfo* ci) {
  int i = std::find_if(case_vector.begin(), case_vector.end(), BranchComp(name)) - case_vector.begin();
  if (i != (int)case_vector.size()) {
    case_index = i;
  }
  if (case_index != (int)case_vector.size()) {
    symtab->enterscope();
    symtab->addid(case_vector[case_index]->name,
        new SymInfo(case_vector[case_index]->type_decl, ci->temp_offset));

    emit_load_imm(T1, class_tag, *ci->sp);
    emit_load(T2, TAG_OFFSET, ACC, *ci->sp);
    int base_label_number = curr_label_number++;      // assign a label number for not_matched
    emit_bne(T1, T2, base_label_number, *ci->sp);     // goto not_matched

    case_vector[case_index]->expr->code(*ci->sp);     // matched code here
    emit_branch(ci->exit_point, *ci->sp);             // goto exit_point

    emit_label_def(base_label_number, *ci->sp);       // not_matched: next_class or exception code

    symtab->exitscope();
  }
  for (List<CgenNode> *l = children; l; l = l->tl()) {
    l->hd()->travel(case_vector, case_index, ci);
  }
}

void typcase_class::code(ostream &s) {
  expr->code(s);
  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_bne(ACC, ZERO, base_label_number, s);    // goto cases
  emit_load_string(ACC, (StringEntry*)curr_class->filename, s);
  emit_load_imm(T1, 1, s);
  emit_jal("_case_abort2", s);

  emit_label_def(base_label_number, s);         // cases:
  emit_push(ACC, s);       // store to the stack
  std::vector<branch_class*> case_vector;
  for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
    case_vector.push_back((branch_class*)cases->nth(i));
  }
  struct CaseInfo ci = { temp_offset(curr_temp_offset++), base_label_number + 1, &s };
  if (expr->type != SELF_TYPE) {
    classtable->lookup(expr->type)->travel(case_vector, (int)case_vector.size(), &ci);
  } else {
    classtable->lookup(curr_class->name)->travel(case_vector, (int)case_vector.size(), &ci);
  }

  // travel has defined no_match
  emit_jal("_case_abort", s);
  emit_label_def(base_label_number + 1, s);     // exit_point:
  emit_addiu(SP, SP, 4, s);             // pop stack
  --curr_temp_offset;
}

void block_class::code(ostream &s) {
  for (int i = body->first(); body->more(i); i = body->next(i))
    body->nth(i)->code(s);
}

void let_class::code(ostream &s) {
  if (type_decl == Int && (init->type == No_type || init->type == NULL)) {      // default built in objects
    emit_load_int(ACC, inttable.lookup_string("0"), s);
  } else if (type_decl == Str && (init->type == No_type || init->type == NULL)) {
    emit_load_string(ACC, stringtable.lookup_string(""), s);
  } else if (type_decl == Bool && (init->type == No_type || init->type == NULL)) {
    emit_load_bool(ACC, falsebool, s);
  } else {
    init->code(s);
  }
  emit_push(ACC, s);
  symtab->enterscope();
  symtab->addid(identifier, new SymInfo(type_decl, temp_offset(curr_temp_offset++)));

  body->code(s);

  symtab->exitscope();
  emit_addiu(SP, SP, 4, s);   // pop stack
  --curr_temp_offset;
}

void plus_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_call_method(Object, ::copy, s);
  emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_load(T2, 1, SP, s);
  emit_load(T2, DEFAULT_OBJFIELDS, T2, s);
  emit_add(T1, T2, T1, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_addiu(SP, SP, 4, s);      // pop stack;
  --curr_temp_offset;
}

void sub_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_call_method(Object, ::copy, s);
  emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_load(T2, 1, SP, s);
  emit_load(T2, DEFAULT_OBJFIELDS, T2, s);
  emit_sub(T1, T2, T1, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_addiu(SP, SP, 4, s);      // pop stack;
  --curr_temp_offset;
}

void mul_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_call_method(Object, ::copy, s);
  emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_load(T2, 1, SP, s);
  emit_load(T2, DEFAULT_OBJFIELDS, T2, s);
  emit_mul(T1, T2, T1, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_addiu(SP, SP, 4, s);      // pop stack;
  --curr_temp_offset;
}

void divide_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_call_method(Object, ::copy, s);
  emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_load(T2, 1, SP, s);
  emit_load(T2, DEFAULT_OBJFIELDS, T2, s);
  emit_div(T1, T2, T1, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
  emit_addiu(SP, SP, 4, s);      // pop stack;
  --curr_temp_offset;
}

void neg_class::code(ostream &s) {
  e1->code(s);
  emit_call_method(Object, ::copy, s);
  emit_load(T1, 3, ACC, s);
  emit_neg(T1, T1, s);
  emit_store(T1, 3, ACC, s);
}

void lt_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(ACC, 3, ACC, s);

  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_blt(T1, ACC, base_label_number, s);    // goto true_branch
  emit_load_bool(ACC, falsebool, s);
  emit_branch(base_label_number + 1, s);      // goto end_if
  emit_label_def(base_label_number, s);       // true_branch:
  emit_load_bool(ACC, truebool, s);
  emit_label_def(base_label_number + 1, s);   // end_if:

  emit_addiu(SP, SP, 4, s);   // pop stack
  --curr_temp_offset;
}

void eq_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_load(T1, 1, SP, s);

  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_beq(T1, ACC, base_label_number, s);    // goto true_branch
  emit_move(T2, ACC, s);
  emit_load_bool(ACC, truebool, s);
  emit_load_bool(A1, falsebool, s);
  s << JAL << "equality_test\n";
  emit_branch(base_label_number + 1, s);      // goto end_if
  emit_label_def(base_label_number, s);       // true_branch:
  emit_load_bool(ACC, truebool, s);
  emit_label_def(base_label_number + 1, s);   // end_if:

  emit_addiu(SP, SP, 4, s);   // pop stack
  --curr_temp_offset;
}

void leq_class::code(ostream &s) {
  e1->code(s);
  emit_push(ACC, s);
  ++curr_temp_offset;
  e2->code(s);
  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(ACC, 3, ACC, s);

  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_bleq(T1, ACC, base_label_number, s);    // goto true_branch
  emit_load_bool(ACC, falsebool, s);
  emit_branch(base_label_number + 1, s);      // goto end_if
  emit_label_def(base_label_number, s);       // true_branch:
  emit_load_bool(ACC, truebool, s);
  emit_label_def(base_label_number + 1, s);   // end_if:

  emit_addiu(SP, SP, 4, s);   // pop stack
  --curr_temp_offset;
}

void comp_class::code(ostream &s) {
  e1->code(s);
  emit_load(ACC, 3, ACC, s);
  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_bne(ACC, ZERO, base_label_number, s);    // goto true_branch
  emit_load_bool(ACC, truebool, s);
  emit_branch(base_label_number + 1, s);        // goto end_if
  emit_label_def(base_label_number, s);         // true_branch:
  emit_load_bool(ACC, falsebool, s);
  emit_label_def(base_label_number + 1, s);     // end_if:
}

void int_const_class::code(ostream& s)  
{ 
  //
  // Need to be sure we have an IntEntry *, not an arbitrary Symbol
  //
  emit_load_int(ACC,inttable.lookup_string(token->get_string()),s);
}

void string_const_class::code(ostream& s)
{
  emit_load_string(ACC,stringtable.lookup_string(token->get_string()),s);
}

void bool_const_class::code(ostream& s)
{
  emit_load_bool(ACC, BoolConst(val), s);
}

void new__class::code(ostream &s) {
  if (type_name == SELF_TYPE) {
    emit_load(T1, TAG_OFFSET, SELF, s);
    emit_sll(T1, T1, 3, s);
    emit_load_address(T2, CLASSOBJTAB, s);
    emit_add(T1, T1, T2, s);                    // CLASSOBJTAB + TAGOFFSET * 2 * 4
    emit_load(ACC, 0, T1, s);                   // prototype object
    emit_move("$s1", T1, s);
    emit_call_method(Object, ::copy, s);        // call Object.copy
    emit_load(T1, 1, "$s1", s);                  // object initializing function
    emit_jalr(T1, s);                           // call init
  } else {
    emit_load_protobj(ACC, type_name, s);
    emit_call_method(Object, ::copy, s);        // call Object.copy
    emit_call_init(type_name, s);               // call init
                                                // ACC is already SELF
  }
}

void isvoid_class::code(ostream &s) {
  e1->code(s);
  int base_label_number = curr_label_number;
  curr_label_number += 2;
  emit_beq(ACC, ZERO, base_label_number, s);    // goto true_branch
  emit_load_bool(ACC, falsebool, s);
  emit_branch(base_label_number + 1, s);        // goto end_if
  emit_label_def(base_label_number, s);         // true_branch:
  emit_load_bool(ACC, truebool, s);
  emit_label_def(base_label_number + 1, s);     // end_if:
}

void no_expr_class::code(ostream &s) {
  emit_move(ACC, ZERO, s);
}

void object_class::code(ostream &s) {
  if (name == self) {
    emit_move(ACC, SELF, s);
  } else {
    int offset = symtab->lookup(name)->offset;
    switch (offset >> 24) {
     case 0:
      emit_load(ACC, offset & ~(0xff << 24), SELF, s);
      break;
     case 1:
      emit_load(ACC, offset & ~(0xff << 24), FP, s);
      break;
     default:
      emit_load(ACC, offset, FP, s);
      break;
    }
  }
}
