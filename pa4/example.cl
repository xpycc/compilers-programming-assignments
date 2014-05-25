
(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)

class Main inherits IO {
  main():SELF_TYPE { out_string("Hello!") };
  out_string(s: String): SELF_TYPE {{
    out_string("class Main: ");
	out_string(s);
    out_string("\n");
  }};
};

