class Main inherits IO {
  a: String;
  b: String;
  main(): IO {{
	let x: Int <- new Int in x + 1;
  let s: SELF_TYPE <- new SELF_TYPE in s;
    a <- in_string();
    b <- in_string();
    out_string(b.concat("\n"));
    out_string(a.concat("\n"));
    self;
  }};
};

class A {
  a: Int;
  aa(): Int {
	fa(new Int)
  };
  fa(i: Int): Int {
	a <- i
  };
  cc(k: Object): Object {
    case k of
	  a: Int => a;
      b: Bool => b;
	  c: A => a;
	  s: SELF_TYPE => s;
    esac
  };
};

class B {
  dd(): Int {
	let a: A <- new A in a.aa()
  };
};
