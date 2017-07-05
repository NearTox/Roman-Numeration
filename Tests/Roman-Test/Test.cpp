#include "gtest/gtest.h"
#include <array>

namespace Roman_Make {

  std::array<std::string, 13> RomanLetters = {
    // 1   4    5     9
    "I", "IV", "V", "IX",
    // 10  40   50    90
    "X", "XL", "L", "XC",
    // 100 400 500  900
    "C", "CD", "D", "CM",
    // 1000
    "M",
  };
  std::array<uint64_t, 13> RomanValue = {
    1, 4, 5, 9,
    10, 40, 50, 90,
    100, 400, 500, 900,
    1000
  };

  enum RomanLetter : uint8_t {
    Roman_Letter_I = 0, Roman_Letter_IV = 1, Roman_Letter_V = 2, Roman_Letter_IX = 3,
    Roman_Letter_X = 4, Roman_Letter_XL = 5, Roman_Letter_L = 6, Roman_Letter_XC = 7,
    Roman_Letter_C = 8, Roman_Letter_CD = 9, Roman_Letter_D = 10, Roman_Letter_CM = 11,
    Roman_Letter_M = 12,
  };

  static std::string Make(uint64_t value, RomanLetter min = Roman_Letter_I, uint64_t *resuido = nullptr) {
    if(value == 0) {
      throw std::exception("0 is not a Roman value");
    }
    std::string out;
    if(value > 4999) {
      uint64_t new_value = (value / 1000);
      uint64_t result = 0;
      out += '(' + Make(new_value, Roman_Letter_V, &result) + ')';
      value -= (new_value - result) * 1000;
    }
    uint8_t current = Roman_Letter_M;

    while(current >= min && value != 0) {
      uint64_t curr_val = RomanValue[current];
      const uint64_t maxrepeat = current == Roman_Letter_M ? 5 : 4;
      if(current % 2 == 0) {
        if(value < maxrepeat * curr_val) {
          while(value >= curr_val) {
            out += RomanLetters[current];
            value -= curr_val;
          }
        }
      } else if(value >= curr_val && value > value - curr_val) {
        out += RomanLetters[current];
        value -= curr_val;
      }

      if(current == min) { break; }
      --current;
    }
    if(resuido != nullptr) {
      *resuido = value;
    }

    return out;
  }
}

namespace Roman_Parse {
  std::array<char, 7> RomanLetters= {
    // 1  5   10
    'I', 'V', 'X',
    // 50 100 500
    'L', 'C', 'D',
    // 1000
    'M',
  };
  std::array<uint64_t, 7> RomanValue= {
    1, 5, 10,
    50, 100, 500,
    1000
  };

  enum RomanLetter: uint8_t {
    Roman_Letter_I = 0, Roman_Letter_V = 1,
    Roman_Letter_X = 2, Roman_Letter_L = 3,
    Roman_Letter_C = 4, Roman_Letter_D = 5,
    Roman_Letter_M = 6,
  };

  uint64_t Parse(const std::string &value, size_t *resuido = nullptr) {

    if(value.size() == 0) {
      return 0;
    }
    std::string value2(value.rbegin(), value.rend());
    std::string::const_iterator itt = value2.begin();
    std::string::const_iterator itt_end = value2.end();
    uint64_t out = 0;
    {
      size_t start = value.find('(');
      if(start != std::string::npos) {
        size_t end = value.rfind(')'/*, start*/);
        if(end == std::string::npos) {
          throw std::exception("error while parsing the string");
        }
        size_t worked = 0;
        out += (Parse(value.substr(start + 1, end - start - 1), &worked) * 1000);
        itt_end -= worked + 2;
      }
    }

    uint8_t current = Roman_Letter_I;
    while(current <= Roman_Letter_M && itt != itt_end) {
      char letter = RomanLetters[current];
      while(itt != itt_end && letter == *itt) {
        out += RomanValue[current];
        itt++;
        if(current != Roman_Letter_I) {
          char last_letter = '\0';
          uint8_t last_pos = 0;
          switch(current) {
            case Roman_Letter_V:
            case Roman_Letter_X:
              last_pos = Roman_Letter_I; last_letter = RomanLetters[last_pos]; break;
            case Roman_Letter_L:
            case Roman_Letter_C:
              last_pos = Roman_Letter_X; last_letter = RomanLetters[last_pos]; break;
            case Roman_Letter_D:
            case Roman_Letter_M:
              last_pos = Roman_Letter_C; last_letter = RomanLetters[last_pos]; break;
          }
          if(last_letter != '\0' && itt != itt_end && last_letter == *itt) {
            out -= RomanValue[last_pos];
            itt++;
          }
        }
      }
      if(current == Roman_Letter_M) {
        break;
      }
      current++;
    }
    if(resuido != nullptr) {
      *resuido = value.size() - (itt_end - itt);
    } else if(itt != itt_end) {
      throw std::exception("error while parsing the string");
    }
    return out;
  }
}

TEST(Roman, Core) {
  EXPECT_EQ("I", Roman_Make::Make(1));
  EXPECT_EQ("V", Roman_Make::Make(5));
  EXPECT_EQ("X", Roman_Make::Make(10));
  EXPECT_EQ("L", Roman_Make::Make(50));
  EXPECT_EQ("C", Roman_Make::Make(100));
  EXPECT_EQ("D", Roman_Make::Make(500));
  EXPECT_EQ("M", Roman_Make::Make(1000));

  EXPECT_EQ(1, Roman_Parse::Parse("I"));
  EXPECT_EQ(5, Roman_Parse::Parse("V"));
  EXPECT_EQ(10, Roman_Parse::Parse("X"));
  EXPECT_EQ(50, Roman_Parse::Parse("L"));
  EXPECT_EQ(100, Roman_Parse::Parse("C"));
  EXPECT_EQ(500, Roman_Parse::Parse("D"));
  EXPECT_EQ(1000, Roman_Parse::Parse("M"));
}

TEST(Roman, Simple) {
  EXPECT_EQ("XXXIV", Roman_Make::Make(34));
  EXPECT_EQ("CCLXVII", Roman_Make::Make(267));
  EXPECT_EQ("DCCLXIV", Roman_Make::Make(764));
  EXPECT_EQ("CMLXXXVII", Roman_Make::Make(987));
  EXPECT_EQ("MCMLXXXIII", Roman_Make::Make(1983));
  EXPECT_EQ("MMXIV", Roman_Make::Make(2014));
  EXPECT_EQ("MMMM", Roman_Make::Make(4000));
  EXPECT_EQ("MMMMCMXCIX", Roman_Make::Make(4999));

  EXPECT_EQ(34, Roman_Parse::Parse("XXXIV"));
  EXPECT_EQ(267, Roman_Parse::Parse("CCLXVII"));
  EXPECT_EQ(764, Roman_Parse::Parse("DCCLXIV"));
  EXPECT_EQ(987, Roman_Parse::Parse("CMLXXXVII"));
  EXPECT_EQ(1983, Roman_Parse::Parse("MCMLXXXIII"));
  EXPECT_EQ(2014, Roman_Parse::Parse("MMXIV"));
  EXPECT_EQ(4000, Roman_Parse::Parse("MMMM"));
  EXPECT_EQ(4999, Roman_Parse::Parse("MMMMCMXCIX"));
}

TEST(Roman, Advanced) {
  EXPECT_EQ("(V)", Roman_Make::Make(5000));
  EXPECT_EQ("(V)CDLXXVIII", Roman_Make::Make(5478));
  EXPECT_EQ("(V)M", Roman_Make::Make(6000));
  EXPECT_EQ("(IX)", Roman_Make::Make(9000));
  EXPECT_EQ("(X)M", Roman_Make::Make(11000));
  EXPECT_EQ("(X)MM", Roman_Make::Make(12000));
  EXPECT_EQ("(X)MMCCCXLV", Roman_Make::Make(12345));
  EXPECT_EQ("(CCCX)MMMMCLIX", Roman_Make::Make(314159));
  EXPECT_EQ("(DLXXV)MMMCCLXVII", Roman_Make::Make(578267));
  EXPECT_EQ("(MMMCCXV)CDLXVIII", Roman_Make::Make(3215468));
  EXPECT_EQ("(MMMMCCX)MMMMCDLXVIII", Roman_Make::Make(4214468));
  EXPECT_EQ("(MMMMCCXV)CDLXVIII", Roman_Make::Make(4215468));
  EXPECT_EQ("(MMMMCCXV)MMMCDLXVIII", Roman_Make::Make(4218468));
  EXPECT_EQ("(MMMMCCXIX)CDLXVIII", Roman_Make::Make(4219468));
  EXPECT_EQ("((XV)MDCCLXXV)MMCCXVI", Roman_Make::Make(16777216));
  EXPECT_EQ("((CCCX)MMMMCLIX)CCLXV", Roman_Make::Make(314159265));
  EXPECT_EQ("((MLXX)MMMDCCXL)MDCCCXXIV", Roman_Make::Make(1073741824));

  EXPECT_EQ(5000, Roman_Parse::Parse("(V)"));
  EXPECT_EQ(5478, Roman_Parse::Parse("(V)CDLXXVIII"));
  EXPECT_EQ(6000, Roman_Parse::Parse("(V)M"));
  EXPECT_EQ(9000, Roman_Parse::Parse("(IX)"));
  EXPECT_EQ(11000, Roman_Parse::Parse("(X)M"));
  EXPECT_EQ(12000, Roman_Parse::Parse("(X)MM"));
  EXPECT_EQ(12345, Roman_Parse::Parse("(X)MMCCCXLV"));
  EXPECT_EQ(314159, Roman_Parse::Parse("(CCCX)MMMMCLIX"));
  EXPECT_EQ(578267, Roman_Parse::Parse("(DLXXV)MMMCCLXVII"));
  EXPECT_EQ(3215468, Roman_Parse::Parse("(MMMCCXV)CDLXVIII"));
  EXPECT_EQ(4214468, Roman_Parse::Parse("(MMMMCCX)MMMMCDLXVIII"));
  EXPECT_EQ(4215468, Roman_Parse::Parse("(MMMMCCXV)CDLXVIII"));
  EXPECT_EQ(4218468, Roman_Parse::Parse("(MMMMCCXV)MMMCDLXVIII"));
  EXPECT_EQ(4219468, Roman_Parse::Parse("(MMMMCCXIX)CDLXVIII"));
  EXPECT_EQ(16777216, Roman_Parse::Parse("((XV)MDCCLXXV)MMCCXVI"));
  EXPECT_EQ(314159265, Roman_Parse::Parse("((CCCX)MMMMCLIX)CCLXV"));
  EXPECT_EQ(1073741824, Roman_Parse::Parse("((MLXX)MMMDCCXL)MDCCCXXIV"));
}
