
namespace Make_Roman {

  class Result {
    out: string = "0";
    resuido: number = 0;
  }

  let RomanLetters = [
    // 1   4    5     9
    "I", "IV", "V", "IX",
    // 10  40   50    90
    "X", "XL", "L", "XC",
    // 100 400 500  900
    "C", "CD", "D", "CM",
    // 1000
    "M",
  ];

  let RomanValue = [
    1, 4, 5, 9,
    10, 40, 50, 90,
    100, 400, 500, 900,
    1000
  ];

  enum RomanLetter {
    Roman_Letter_I = 0, Roman_Letter_IV = 1, Roman_Letter_V = 2, Roman_Letter_IX = 3,
    Roman_Letter_X = 4, Roman_Letter_XL = 5, Roman_Letter_L = 6, Roman_Letter_XC = 7,
    Roman_Letter_C = 8, Roman_Letter_CD = 9, Roman_Letter_D = 10, Roman_Letter_CM = 11,
    Roman_Letter_M = 12,
  };

  /**
   * Based on the C++ file ./Test/Roman-Test/Test.cpp
   */
  export function MakeFull(value: number, min: RomanLetter = RomanLetter.Roman_Letter_I): Result {
    let result = new Result();
    value = Math.round(Math.abs(value));
    if (value == 0) {
      throw "0 is not a Roman value";
    }
    result.out = "";
    if (value > 4999) {
      let new_value = Math.floor(value / 1000);
      let child_result = MakeFull(new_value, RomanLetter.Roman_Letter_V);
      result.out += '(' + child_result.out + ')';
      value -= (new_value - child_result.resuido) * 1000;
    }
    let current = RomanLetter.Roman_Letter_M;

    while (current >= min && value != 0) {
      let curr_val = RomanValue[current];
      let maxrepeat = (current == RomanLetter.Roman_Letter_M) ? 5 : 4;
      if (current % 2 == 0) {
        if (value < maxrepeat * curr_val) {
          while (value >= curr_val) {
            result.out += RomanLetters[current];
            value -= curr_val;
          }
        }
      } else if (value >= curr_val && value > value - curr_val) {
        result.out += RomanLetters[current];
        value -= curr_val;
      }

      if (current == min) { break; }
      --current;
    }
    result.resuido = value;

    return result;
  }
}

namespace Parse_Roman {

  class Result {
    out: number = 0;
    resuido: number = 0;
  }

  let RomanLetters = [
    // 1  5   10
    'I', 'V', 'X',
    // 50 100 500
    'L', 'C', 'D',
    // 1000
    'M',
  ];
  let RomanValue = [
    1, 5, 10,
    50, 100, 500,
    1000
  ];

  enum RomanLetter {
    Roman_Letter_I = 0, Roman_Letter_V = 1,
    Roman_Letter_X = 2, Roman_Letter_L = 3,
    Roman_Letter_C = 4, Roman_Letter_D = 5,
    Roman_Letter_M = 6,
  };

  /**
   * Based on the C++ file ./Test/Roman-Test/Test.cpp
   */
  export function ParseFull(value: string): Result {
    let result = new Result();
    if (value.length == 0) {
      return result;
    }
    let value2 = value.split("").reverse().join("");
    let itt = 0;
    let itt_end = value2.length;
    result.out = 0;
    {
      let start = value.indexOf('(');
      if (start != -1) {
        let end = value.lastIndexOf(')'/*, start*/);
        if (end == -1) {
          throw "error while parsing the string";
        }
        let child_result = ParseFull(value.substr(start + 1, end - start - 1));
        result.out += child_result.out * 1000;
        itt_end -= child_result.resuido + 2;
      }
    }

    let current = RomanLetter.Roman_Letter_I;
    while (current <= RomanLetter.Roman_Letter_M && itt != itt_end) {
      let letter = RomanLetters[current];
      while (itt != itt_end && letter == value2[itt]) {
        result.out += RomanValue[current];
        itt++;
        if (current != RomanLetter.Roman_Letter_I) {
          let last_letter: string = undefined;
          let last_pos = 0;
          switch (current) {
            case RomanLetter.Roman_Letter_V:
            case RomanLetter.Roman_Letter_X:
              last_pos = RomanLetter.Roman_Letter_I;
              last_letter = RomanLetters[last_pos];
              break;
            case RomanLetter.Roman_Letter_L:
            case RomanLetter.Roman_Letter_C:
              last_pos = RomanLetter.Roman_Letter_X;
              last_letter = RomanLetters[last_pos]; break;
            case RomanLetter.Roman_Letter_D:
            case RomanLetter.Roman_Letter_M:
              last_pos = RomanLetter.Roman_Letter_C;
              last_letter = RomanLetters[last_pos]; break;
          }
          if (last_letter !== undefined && itt != itt_end && last_letter == value2[itt]) {
            result.out -= RomanValue[last_pos];
            itt++;
          }
        }
      }
      if (current == RomanLetter.Roman_Letter_M) { break; }
      current++;
    }
    result.resuido = value.length - (itt_end - itt);
    return result;
  }

}

export namespace Roman {
  /**
   * Number -> Roman numeration
   * @param value a positive number upper to zero
   * @returns the Roman representation of the number
   */
  export function Make(value: number): string {
    return Make_Roman.MakeFull(value).out;
  }

  /**
   * Roman numeration -> Number
   * @param value the Roman representation of the number
   * @returns the natural representation of the number (base 10)
   */
  export function Parse(value: string): number {
    return Parse_Roman.ParseFull(value).out;
  }
};