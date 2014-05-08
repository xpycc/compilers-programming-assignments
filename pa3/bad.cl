class C inherits A {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		self;
           }
	};
};

class Object {
};

class Main {
	main():C {
	 {
	  (new C).init(1,1);
	  (new C).init(1,true,3);
	  (new C).iinit(1,true);
	  (new C);
	 }
	};
};

class A inherits C {
	init(s: String): C {
		self
	};
};

class D inherits A {
};

class E inherits D {
};

class F inherits D {
};
