class C (* inherits A *) {
	self(): Int { 1 };
	a : Int;
	b : Bool;
	init : IO;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		self;
           }
	};
};

class Main {
	main():C {
	 {
(*	  (new C).init(1,1);
	  (new C).init(1,true,3);
	  (new C).iinit(1,true); *)
	  self <- new C;
	  (new C).self();
	 }
	};
};

class A inherits C {
	init(x: Int, y:Bool): C {
		self
	};
};
(*
class D inherits A {
};

class E inherits D {
};

class F inherits D {
};
*)
