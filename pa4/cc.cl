class Main {
  i: Int;
  o1: Object <- true.copy();
  o2: Object <- true.copy();
  main(): Main {{
    let x: Int <- 1 in i <- x;
	if o1 = o2 then new IO.out_string("Yes\n")
    else new IO.out_string("No\n") fi;
	self;
  }};
};
