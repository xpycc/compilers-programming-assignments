class Main {
  io: IO <- new IO;
  main(): Main {{
    io.out_string("0123456789".substr(0, 3).concat("\n"));
    io.out_string("0123456789".substr(1, 5).concat("\n"));
    io.out_string("0123456789".substr(2, 6).concat("\n"));
    io.out_string("0123456789".substr(2, 9).concat("\n"));
	self;
  }};
};
