
(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)

class Main inherits IO {
  main():SELF_TYPE { out_string("Hello!") };
  out_string(s: String): SELF_TYPE {{
    self@IO.out_string("class Main: ");
	self@IO.out_string(s);
    self@IO.out_string("\n");
  }};
};

