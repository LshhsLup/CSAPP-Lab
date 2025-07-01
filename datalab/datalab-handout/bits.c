/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    // 思路：x ^ y = (~x)&y | x&(~y)
    // return ((~x) & y) | (x & (~y));
    // 不允许使用 |
    // 思路：x ^ y = ~(~(x & ~y) & ~(~x & y))
    return ~(~(x & ~y) & ~(~x & y));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    // 整数补码的最小值: 1000 0000 0000 0000 0000 0000 0000 0000
    return 1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    // 0111 1111 1111 1111 1111 1111 1111 1111 --> 1
    // x ^ Tmax == 0, x ^ other == 1
    // return !(x ^ 0x7fffffff);
    // 不允许使用 0x7fffffff, (only 0x0 - 0xff allowed)
    // x + 1 == 100000 0000 0000 0000 0000 0000 0000 0000 = ~x
    // 注意 x + 1 == 0 时，x == -1, 也就是 ~0
    return !((x + 1) ^ (~x)) & !!(x + 1); 
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    // 0 到 31 , 如果所有奇数位都为 1，返回 1
    // 思路：
    // 如果 x 为奇数位全为 1, 那么 x | 0101 0101 0101 0101 0101 0101 0101 0101 == 0xffffffff
    // 所以只需要判断 x | 0x55555555 是否等于 0xffffffff
    // a ^ b == 0, 那么 a == b
    // a ^ b != 0, 那么 a != b
    // return !((x | 0x55555555) ^ 0xffffffff);
    // update:
    // 不允许使用 0x55555555, (only 0x0 - 0xff allowed)
    // x & 0xaaaaaaaa == 0xaaaaaaaa
    int x_mask = ((0xaa << 24) | (0xaa << 16) | (0xaa << 8) | 0xaa); 
    return !((x & x_mask) ^ x_mask);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    // 思路：全部取反，然后末位加 1，之后变成的数与 -x 的补码
    return ((~x) + 1);
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // 思路：0x0000003y, 其中 y ∈ [0,9] 时为 1
    // 那么只需确定 x 前 28 为 0x00000030 并且后四位是 [0,9] 的范围
    // x & 0x0000000f - 10，如果小于 0，那么确定第二个条件
    // x & 0xfffffff0 得到前 28 位，如果等于 0x00000030，那么确定第一个条件
    // - 10 可以用 +(-10), 判断小于 0 只需要判断第 31 位是否 1(即判断 & 0x80000000 是否等于 0x80000000)
    // 条件 1 和 条件 2 同时确定返回 1
    return (!((((x & 0x0000000f) + ((~0x0000000a) + 1)) & 0x80000000) ^ 0x80000000)) & (!((x & 0xfffffff0) ^ 0x00000030));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // 思路：x == 0, 返回 z; x != 0, 返回 y
    // 很容易想到 0 & y + 0xffffffff & z == z, 0 & z + 0xffffffff & y == y
    // F & y + F' & z
    // 也就是说我们希望找到一种属于 x 的表达式 F 和 F'，使 F,F' 满足：
    // x == 0 时，F == 0, F' = 0xffffffff
    // x != 0 时，F == 0xffffffff, F' = 0
    // 又因为 ~0 == 0xffffffff, 所以 F == ~F'，那么只需要找 F 即可
    // 为了规避掉一般值，当 x != 0 时，我们 !x 就可以得到 1
    // 那么怎么 1 --> 0xffffffff 呢？
    // 考虑 ~0，所以得到 F = ~(!x), 但是这个满足了 x != 0 的情况，当 x == 0 时， F == 0x11111110
    // 这个时候考虑 F = ~(!x) + 1, x != 0 时候 F == 0，x == 0 时 F == 0xfffffff
    // 虽然与期望的 F 相反，但是等于 F' 呀，它们时共轭的，调整一下就行了
    // F & z + F' & y
    return (((~(!x)) + 1) & z) + ((~((~(!x)) + 1)) & y);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // 思路：x + (-(y+1)) < 0
    // 注意：不要写 x + (~(y + 1) + 1) , y 如果是 INT_MAX, 在加 1 就溢出了导致错误
    // return !(((x + (~(0x00000001) + 1) + ((~(y)) + 1) ) & 0x80000000) ^ 0x80000000);
    // update:
    // 上面那样写有问题：INT_MIN - INT_MAX 会出错
    // 不能通过相减得到的符号位是否 1 或者相减之后为 0 判断
    // 0x80000000 + (-0x7fffffff) 因为符号位溢出变为 0 了
    // 所以不能直接通过相减得到的符号位是否 1 判断
    int sign_x = (x >> 31) & 1; // x 的符号位
    int sign_y = (y >> 31) & 1; // y 的符号位
    int diff = x + (~y + 1);    // x - y
    // 1. x 和 y 符号位相同
    //    判断 x - y 的符号位是否为 1 并且 是否 x - y == 0
    // 2. x 和 y 符号位不同
    //    a. x 是负数，y 是正数，x <= y 一定成立
    //    b. x 是正数，y 是负数，x <= y 一定不成立
    return (sign_x & (!sign_y)) | (!(sign_x ^ sign_y) & (((diff >> 31) & 1) | !diff));
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    // 0:54 卡住了，啊啊啊啊啊啊啊啊啊啊啊
    // 8:59 更新
    // 思路：x == 0, F = 1; x != 0, F = 0
    // 令 F = 1 - X, x == 0, X == 0; x != 0, X == 1
    // 考虑 x != 0 时，必有 x | -x 的最高位为 1
    // 这时候若 x == 0, x | -x 还是 0
    // 那我们就处理这个 x | -x 就行了, 把它的最高位提取出来
    // 即 X == x | -x >> 31 & 1
    return 1 - (((x | ((~x) + 1)) >> 31) & 1);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    // 思路：统一转换为正数实现
    // ans = 1 + log2(x) x > 0
    // ans = 1 + log2(~x) x < 0
    // log2(x) 指的是 x 的二进制表示中最高位的下标
    // 例如 12 的二进制表示为 1100, 最高位下标为 4, log2(12) = 4
    // 使用二分法实现 log2(x)
    int is_negative = x >> 31; // x 为负数，is_negative = -1(0xffffffff); 否则为 0
    // 将 x 变为正数, 同时保证 x 为正数的时候不变
    x = x ^ is_negative;              // 如果 x 为负数，x = -x; 否则 x 不变
    int bit_count = 0;                // 记录需要的位数
    int check16 = (!!(x >> 16)) << 4; // 检查高 16 位是否有 1
    bit_count += check16;             // 如果有 1, 位数加 16
    x = x >> check16;                 // 如果有 1, 则将 x 右移 16 位，否则 x 不变
    int check8 = (!!(x >> 8)) << 3;   // 检查高 8 位是否有 1
    bit_count += check8;              // 如果有 1, 位数加 8
    x = x >> check8;                  // 如果有 1, 则将 x 右移 8 位，否则 x 不变
    int check4 = (!!(x >> 4)) << 2;   // 检查高 4 位是否有 1
    bit_count += check4;              // 如果有 1, 位数加 4
    x = x >> check4;                  // 如果有 1, 则将 x 右移 4 位，否则 x 不变
    int check2 = (!!(x >> 2)) << 1;   // 检查高 2 位是否有 1
    bit_count += check2;              // 如果有 1, 位数加 2
    x = x >> check2;                  // 如果有 1, 则将 x 右移 2 位，否则 x 不变
    int check1 = (!!(x >> 1));        // 检查高 1 位是否有 1
    bit_count += check1;              // 如果有 1, 位数加 1
    x = x >> check1;                  // 如果有 1, 则将 x 右移 1 位，否则 x 不变
    return bit_count + 1 + x;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int sign = (uf >> 31) & 1;                   // 符号位
    unsigned exponent = (uf >> 23) & 0x000000ff; // 指数位
    unsigned fraction = uf & 0x007fffff;         // 尾数位
    if (exponent == 0x000000ff) {
        // uf 是 NaN
        return uf;
    }
    if (exponent == 0) {
        // 非规格化，0.f * 2 ^ -126
        return ((0 | sign) << 31) | (fraction << 1);
    }
    // uf * 2 == (E + 1)
    exponent += 1;
    unsigned ans = 0;
    ans = (ans | sign) << 31;
    ans = ((0 | exponent) << 23) | ans;
    ans = ((0 | fraction) | ans);
    return ans;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    int sign = (uf >> 31) & 1;                     // 符号位
    unsigned exponent = ((uf >> 23) & 0x000000ff); // 指数位
    int fraction = (uf & 0x007fffff);              // 尾数位
    if (exponent == 0xff) {                        // NaN 或者 Infinity
        return 0x80000000u;                        // 返回 0x80000000u
    }
    if (exponent < 127) { // 小于 127，表示小于 1
        return 0;         // 返回 0
    }
    // 计算偏移量
    int offset = exponent - 127; // 偏移量
    if (offset >= 31) {          // 如果偏移量大于等于 31，表示溢出
        return 0x80000000u;      // 返回 0x80000000u
    }
    // 计算整数部分
    // 1.xxx * 2^(exponent - 127)
    // 其中 xxx 是尾数部分，1 是隐含的 1
    // 变成 int 就要舍去小数部分.xxx
    // 比如 1.101 * 2^2 = (1 + 0.5 + 0.125) * 2^2 = (1.625) * 4 = 6.5, 变成 int 就是 6
    // 也就是把 1.101 左移 2 位，得到 110.1
    // 这时候只需要右移 23 - offset 位就可以得到整数部分
    int result = (fraction | 0x00800000) >> (23 - offset); // 尾数加上隐含的 1，然后右移偏移量
    if (sign) {                                            // 如果是负数
        result = -result;                                  // 取反
    }
    return result;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    // sign exponent fraction
    // 2.0 --> (float) 0 10000000 00000000000000000000000
    // 2.0 ^ x > 0
    // // 0.5 --> (float) 0 01111110 00000000000000000000000
    // // 1111 1111 1111 1111 1111 1111 1000 0010
    if (x > 127) {
        return 0x7f800000;
    }
    if (x < -126) {
        return 0;
    }
    unsigned exponent = 127 + x;
    return (0 | (exponent << 23));
}
