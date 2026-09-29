/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&(~((~x)&~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x){
        if(!y) return 1;
        else return 0;
    }
    else{
        if(!y) return 0;
        return !((x^y)&(1<<31));
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
 //使用不当运算符
// int logtwo(int v) {
//     if(v<1)return -1;
//     return logtwo(v>>1)+1;
// }
//二分查找
int logtwo(int v) {
    int r=0;
    int s=((v>>16)>0)<<4;
    r=r|s;
    v=v>>s;
    s=((v>>8)>0)<<3;
    r=r|s;
    v=v>>s;
    s=((v>>4)>0)<<2;
    r=r|s;
    v=v>>s;
    s=((v>>2)>0)<<1;
    r=r|s;
    v=v>>s;
    s=((v>>1)>0);
    r=r|s;
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
 //超限
int byteSwap(int x, int n, int m) {
    int a=n<<3;
    int b=m<<3;
    // int tempn =((x>>(n<<3))&0xFF)<<(m<<3);
    // int tempm =((x>>(m<<3))&0xFF)<<(n<<3);
    // x=(~(0xFF<<(m<<3)))&(~(0xFF<<(n<<3)))&x;
    return (((x>>a)&0xFF)<<b)|(((x>>b)&0xFF)<<a)|((~(0xFF<<b))&(~(0xFF<<a))&x);
}
/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
 //time out
 //循环条件不能写!!(i>>4)
 //无符号数需要写1u否则越界
 //>>2是乘4
 //～是取反不是！
unsigned reverse(unsigned v) {
    for(int i=16;!!i;i--){
        unsigned a=(1u<<(32-i));
        unsigned b=(1u<<(i-1));
        unsigned c=33-(i<<1);
        v=(v&(~a)&(~b))+((v&a)>>c)+((v&b)<<c);
    }
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
 //codex说mask，什么是mask，跟这个的区别是什么? 
int logicalShift(int x, int n) {
    return (x>>n)&(~((((~(1u<<31))&x)>>n)<<1)^((x>>n)<<1));
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v=x^(0xFFFFFFFF);
    int top=~(!(v&(1u<<31)))+1;//if的代替
    int r=0;
    int s=(!!(v>>16))<<4;
    r=r|s;
    v=v>>s;
    s=(!!(v>>8))<<3;
    r=r|s;
    v=v>>s;
    s=(!!(v>>4))<<2;
    r=r|s;
    v=v>>s;
    s=(!!(v>>2))<<1;
    r=r|s;
    v=v>>s;
    s=(!!(v>>1));
    r=r|s;
    v=v>>s;
    return (((31+(~r)+1)&top)|(0&(~top)))+!v;//边界值-1的处理，逻辑比较复杂
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned v = x;
    int a=1u<<31;
    int r=0;
    int s=0;
    unsigned b = 0x7fffffu;

    if(!x) return 0;//单独处理0
    int result=x&a;//保留符号位

    if(result){//负数取绝对值
        v=~v+1;
    }
    unsigned m=v;
    for(int i=4;i>=0;i--){//求最高位的位置
        s=((v>>(1<<i))>0)<<i;
        r=r|s;
        v=v>>s;
    }//9
    //阶码：127+r
    result=result|((127+r)<<23);//符号位+阶码

    unsigned tail = m << (31 - r);//若不足先补上
    unsigned rest = tail & 0xffu;
    tail = (tail >> 8) & b;//保留所需的23位
    if (rest > 0x80u)//8位舍弃的数若达到一半以上进位
        tail = tail + 1;
    else if (rest == 0x80u)//若刚好一半使末位为0
        tail = tail + (tail & 1);
    // int tail=x&(~a);//9
    // if(r>24){
    //     result=(result|((tail>>(r-23))&b))+!!((~b)&tail);
    // }
    // else{
    //     result=result|(tail&b);//11
    // }
    return result+tail;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf){
    unsigned sign=uf&0x80000000u;
    unsigned exp=uf&0x7f800000u;
    unsigned frac=uf&0x007fffffu;

    if (exp==0x7f800000u)// NaN 或无穷大 
        return uf;
    if (!exp)
        return sign|(frac << 1);// 零或非规格化数
    exp = exp+0x00800000u;//阶码字段加 1 
    if (exp==0x7f800000u)// 溢出：返回无穷大，尾数必须为 0 
        return sign|exp;
    return sign|exp|frac;// 普通情况：原符号、加一后的阶码、原尾数 
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
//符号位1+阶码11+尾码52
//int范围-2^7,2^7-1
//8/8+
//负数先变整数，再取补码
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign=uf2&0x80000000u;
    unsigned exp=uf2&0x7FF00000u;
    unsigned frac1=uf2&0x000FFFFFu;
    unsigned frac2=uf1&0xFFFFFFFFu;
    int temp=(exp>>20)-1023;
    if(temp>7)return 0x80000000;
    else if(!(temp-7)){
        if((!sign)){
            return 0x80000000;
        }
    }
    else if(temp<0)return 0;
    unsigned tail=(frac1<<11)|0x80000000|((frac2&0xFFE00000)>>11);
    tail=tail>>(32-temp-1);
    if(sign){
        tail=(~tail)+1;
        tail=tail&(~0x80000000u);
    }
    return sign|tail;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x<-149)return 0;
    if(x<-126)return 1u<<(x+149);
    if(x>127)return 0x7F800000u;
    return (x+127)<<23;
    return 2;
}
