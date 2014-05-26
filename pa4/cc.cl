class Main {
  i: Int;
  o1: Object <- true;
  o2: Object <- true;
  main(): Main {{
    let x: Int <- 1 in i <- x;
	if o1 = o2 then new IO.out_string("Yes\n")
    else new IO.out_string("No\n") fi;
	self;
  }};
};
