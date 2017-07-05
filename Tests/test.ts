import * as test from "tape";
import { Roman } from "../Roman";

test("Roman(core) test", (t) => {
  t.equal("I", Roman.Make(1));
  t.equal("V", Roman.Make(5));
  t.equal("X", Roman.Make(10));
  t.equal("L", Roman.Make(50));
  t.equal("C", Roman.Make(100));
  t.equal("D", Roman.Make(500));
  t.equal("M", Roman.Make(1000));

  t.equal(1, Roman.Parse("I"));
  t.equal(5, Roman.Parse("V"));
  t.equal(10, Roman.Parse("X"));
  t.equal(50, Roman.Parse("L"));
  t.equal(100, Roman.Parse("C"));
  t.equal(500, Roman.Parse("D"));
  t.equal(1000, Roman.Parse("M"));

  t.end();
});

test("Roman(simple) test", (t) => {
  t.equal("XXXIV", Roman.Make(34));
  t.equal("CCLXVII", Roman.Make(267));
  t.equal("DCCLXIV", Roman.Make(764));
  t.equal("CMLXXXVII", Roman.Make(987));
  t.equal("MCMLXXXIII", Roman.Make(1983));
  t.equal("MMXIV", Roman.Make(2014));
  t.equal("MMMM", Roman.Make(4000));
  t.equal("MMMMCMXCIX", Roman.Make(4999));

  t.equal(34, Roman.Parse("XXXIV"));
  t.equal(267, Roman.Parse("CCLXVII"));
  t.equal(764, Roman.Parse("DCCLXIV"));
  t.equal(987, Roman.Parse("CMLXXXVII"));
  t.equal(1983, Roman.Parse("MCMLXXXIII"));
  t.equal(2014, Roman.Parse("MMXIV"));
  t.equal(4000, Roman.Parse("MMMM"));
  t.equal(4999, Roman.Parse("MMMMCMXCIX"));

  t.end();
});

test("Roman(Advanced) test", (t) => {
  t.equal("(V)", Roman.Make(5000));
  t.equal("(V)CDLXXVIII", Roman.Make(5478));
  t.equal("(V)M", Roman.Make(6000));
  t.equal("(IX)", Roman.Make(9000));
  t.equal("(X)M", Roman.Make(11000));
  t.equal("(X)MM", Roman.Make(12000));
  t.equal("(X)MMCCCXLV", Roman.Make(12345));
  t.equal("(CCCX)MMMMCLIX", Roman.Make(314159));
  t.equal("(DLXXV)MMMCCLXVII", Roman.Make(578267));
  t.equal("(MMMCCXV)CDLXVIII", Roman.Make(3215468));
  t.equal("(MMMMCCX)MMMMCDLXVIII", Roman.Make(4214468));
  t.equal("(MMMMCCXV)CDLXVIII", Roman.Make(4215468));
  t.equal("(MMMMCCXV)MMMCDLXVIII", Roman.Make(4218468));
  t.equal("(MMMMCCXIX)CDLXVIII", Roman.Make(4219468));
  t.equal("((XV)MDCCLXXV)MMCCXVI", Roman.Make(16777216));
  t.equal("((CCCX)MMMMCLIX)CCLXV", Roman.Make(314159265));
  t.equal("((MLXX)MMMDCCXL)MDCCCXXIV", Roman.Make(1073741824));

  t.equal(5000, Roman.Parse("(V)"));
  t.equal(5478, Roman.Parse("(V)CDLXXVIII"));
  t.equal(6000, Roman.Parse("(V)M"));
  t.equal(9000, Roman.Parse("(IX)"));
  t.equal(11000, Roman.Parse("(X)M"));
  t.equal(12000, Roman.Parse("(X)MM"));
  t.equal(12345, Roman.Parse("(X)MMCCCXLV"));
  t.equal(314159, Roman.Parse("(CCCX)MMMMCLIX"));
  t.equal(578267, Roman.Parse("(DLXXV)MMMCCLXVII"));
  t.equal(3215468, Roman.Parse("(MMMCCXV)CDLXVIII"));
  t.equal(4214468, Roman.Parse("(MMMMCCX)MMMMCDLXVIII"));
  t.equal(4215468, Roman.Parse("(MMMMCCXV)CDLXVIII"));
  t.equal(4218468, Roman.Parse("(MMMMCCXV)MMMCDLXVIII"));
  t.equal(4219468, Roman.Parse("(MMMMCCXIX)CDLXVIII"));
  t.equal(16777216, Roman.Parse("((XV)MDCCLXXV)MMCCXVI"));
  t.equal(314159265, Roman.Parse("((CCCX)MMMMCLIX)CCLXV"));
  t.equal(1073741824, Roman.Parse("((MLXX)MMMDCCXL)MDCCCXXIV"));

  t.end();
});