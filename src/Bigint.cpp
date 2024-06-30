/**
 * This file contains function definitions for Bigint class
 * Big numbers are represented as strings
 * Arithmatic opeations are done on those strings
 * 
 * Most of the cases that is done character by character
 * Execept for "mulStringsFFT" that uses fft algorithm to find the result
 * 
 * The default consturtor first checks if the string is valid
 * If not the the Bigint number is initialized with "0"
 * 
 */

// Standered libraries
#include <iostream>
#include <algorithm>

// STL
#include <vector>
#include <string>

// 3rd party libararies
#include "Bigint.h"
#include "Fft.h"


// Funcion Definitons
Bigint::Bigint(const std::string& num):m_number{"0"}, m_sign{false}, m_size{1}  // Default constructor
{
    // Validation
    if(num.size()==0 || num == "-" || !std::all_of(num.begin() + (num[0] == '-'|| num[0] == '+' ? 1 : 0), num.end(), ::isdigit))
        return;
    else
    {
        if(num[0] == '-')
        {
            m_number = num.substr(1);
            m_sign = true;
        }
        else if(num[0] == '+')
            m_number = num.substr(1);
        else
            m_number = num;
        squeeze(m_number);
        if(m_number == "0")
            m_sign = false;
        m_size = m_number.size();
    }
};

// Private

void Bigint::reverse(std::string &s) {std::reverse(s.begin(), s.end());} // Reverses the input string

int Bigint::compWithoutSign(const std::string& s1,const std::string& s2) // Numerically compares the two input strings (first w.r.t. second)
{                                                                        // if Greater returns 1
    std::size_t size1 = s1.size();                                       // if Less returns -1, else 0
    std::size_t size2 = s2.size();
    int comp = (size1 != size2) ? size1 - size2 : s1.compare(s2);
    return comp == 0 ? 0 : (comp > 0 ? 1 : -1);
}

/**
 * @param:
 * c1: char type
 *  In valid case "0" to "9"
 * 
 * c2: char type
 *  In valid case "0" to "9"
 * 
 * carry: int type
 *  values = 0 or 1
 * 
 * @return:
 *  char type
 *  valaue = c1 + c2 after numerical addition
 *  if carry is generated carry is set, otherwise reset
 */
char Bigint::calSumCy(char c1, char c2, int &carry) 
{
    int sum = (c1 - '0') +(c2 - '0') + carry;
    carry = sum/10;
    return (sum%10) + '0';
}
	
char Bigint::calSubBr(char c1, char c2, int &borrow)
{
    int diff = (c1-'0') - (c2-'0') - borrow;
    borrow = (diff < 0);
    return (diff + (borrow ? 10 : 0)) + '0';
}

char Bigint::calMulCy(const char& c1, const char& c2, int& carry)
{
    int mul = (c1-'0') * (c2-'0') + carry;
    carry = mul/10;
    return mul%10 + '0';
}

void Bigint::swapStrings(std::string &s1, std::string &s2, std::size_t &size1, std::size_t &size2)
{
	std::string temp = s2;
	s2 = s1;
	s1 = temp;
	std::size_t tempS = size1;
	size1 = size2;
	size2 = tempS;
}

void Bigint::squeeze(std::string &s)
{
    std::size_t i=0;
    std::size_t size = s.size();
    while(i<size-1 && s[i]=='0')
        i++;
    s = s.substr(i);
}

// accepts two strings
// adds (integers in) two strings and return the result string
std::string Bigint::addStrings(const std::string& s1,const std::string& s2)
{
    std::string result{};
    std::size_t size1 = s1.size();
    std::size_t size2 = s2.size();
    int carry= 0;
    int i1 = size1-1, i2 = size2-1;
    while(i1>=0 || i2 >= 0 || carry)
    {
        char c1 = i1>=0 ? s1[i1--] : '0';
        char c2 = i2>=0 ? s2[i2--] : '0';
        result += calSumCy(c1, c2, carry);
    }

    reverse(result);
    return result;
}

// accepts two strings.
// subtracts the smaller integer in the string 's2' from
// the larger integrs in the string 's1'
std::string Bigint::subStrings(const std::string& s1,const std::string& s2)
{
    std::string result{};
    std::size_t size1 = s1.size();
    std::size_t size2 = s2.size();
    int borrow= 0;

    int i1 = size1-1, i2 = size2-1;
    while(i1>=0 || i2 >= 0 || borrow)
    {
        char c1 = i1>=0 ? s1[i1--] : '0';
        char c2 = i2>=0 ? s2[i2--] : '0';
        result += calSubBr(c1, c2, borrow);
    }
    reverse(result);
    // squeeze the result to get rid of leading zeroes
    squeeze(result);
    return result;
}

std::string Bigint::mulStrings(const std::string& s1, const std::string& s2)
{
    std::string result="0";
    if(s1 == "0" || s2 == "0")
        return result;
    std::size_t size1 = s1.size();
    std::size_t size2 = s2.size();
    
    for(int j = size2-1; j>=0; j--)
    {
        int carry = 0;
        std::string temp;

        for(int i=size1-1; i>=0; i--)
            temp += calMulCy(s1[i], s2[j], carry);
        if(carry)
            temp += carry + '0';

        reverse(temp);
        temp.append(size2-j-1,'0');
        addStringsToFirst(result, temp);
    }
    return result;
}

// Implimenting the COOEY-TUCKY algorithm for multiplication of large intergers
std::string Bigint::mulStringsFFT(const std::string& num1, const std::string& num2)
{
    std::size_t num1Len = num1.size();
    std::size_t num2Len = num2.size();
   std::vector<int> a(num1Len);
   std::vector<int> b(num2Len);

    // copy all the character of first number into a BACKWORDS;
   for(std::size_t i=0; i<num1Len; i++)
        a[i] = num1[num1Len-1-i] - '0';
    //  do the same thing for b
    for(std::size_t i=0; i<num2Len; i++)
        b[i] = num2[num2Len-1 -i] - '0';

    // multiply using strassen fft algo
    std::vector<int> resArr = std::move(mulstrassen(a,b));
    std::size_t resLen = resArr.size();
    std::string result;
    for(int i = resLen-1; i>=0; i--)
    {
        result += "0";
        addStringsToFirst(result,std::to_string(resArr[i]));
    }
    return result;
}


void Bigint::addStringsToFirst(std::string& s1, const std::string& s2) {s1 = addStrings(s1,s2);}

// Public Functons

// Copy operators
Bigint& Bigint::operator=(const Bigint& num)
{
    m_number = num.m_number;
    m_sign = num.m_sign;
    m_size = num.m_size;
    return *this;
}

Bigint& Bigint::operator=(const std::string& num) {return *this = Bigint(num);}


// Additions
Bigint Bigint::operator+(const Bigint& num) const
{
    Bigint result;
    if(m_sign == num.m_sign)
    {
        result = addStrings(m_number, num.m_number);
        result.m_sign = m_sign;
        return result;
    }
    
    int comp = compWithoutSign(m_number, num.m_number);
    if(comp > 0)
    {
        result = subStrings(m_number, num.m_number);
        result.m_sign = m_sign;
    }
    else if(comp < 0)
    {
        result = subStrings(num.m_number, m_number);
        result.m_sign = num.m_sign;
    }

    return result;
}

Bigint Bigint::operator+(const std::string& num) const {return *this + Bigint(num);}


// Subtractions
Bigint Bigint::operator-(const Bigint &num) const
{
    Bigint result;

    if(m_sign != num.m_sign)
    {
        result = addStrings(m_number, num.m_number);
        result.m_sign = m_sign;
        return result;
    }

    int comp = compWithoutSign(m_number, num.m_number);
    if(comp > 0)
    {
        result = subStrings(m_number, num.m_number);
        result.m_sign = m_sign;
    }
    else if(comp < 0)
    {
        result = subStrings(num.m_number, m_number);			
        result.m_sign = !num.m_sign;
    }

    return result;
}

Bigint Bigint::operator-(const std::string &num) const {return *this + Bigint(num);}


// Multiplications
Bigint Bigint::operator*(const Bigint& num) const
{
    Bigint result(mulStrings(m_number, num.m_number));
    result.m_sign = m_sign != num.m_sign;
    return result;
}

Bigint Bigint::operator*(const std::string& num) const {return *this * Bigint(num);}

// using fft
Bigint Bigint::mulFFT(const Bigint& num) const
{
    Bigint result(mulStringsFFT(m_number, num.m_number));
    result.m_sign = m_sign != num.m_sign;
    return result;
}

Bigint Bigint::mulFFT(const std::string& str) const
{
    Bigint num(str);   
    Bigint result(mulStringsFFT(m_number, num.m_number));
    result.m_sign = m_sign != num.m_sign;
    return result;
}



// Divisions (To Be added)

// Power
Bigint Bigint::operator^(const int& n) const
{
	if(n==0)	return Bigint("1");
	Bigint temp = *this^(n/2);
	if(n%2 == 0) return temp * temp;
	return *this * temp * temp;
}

// Add and copy
Bigint& Bigint::operator+=(const Bigint& num) {return *this = *this + num;}
Bigint& Bigint::operator+=(const std::string& num) {return *this = *this + num;}

// Subtract and copy
Bigint& Bigint::operator-=(const Bigint& num) {return *this = *this - num;}
Bigint& Bigint::operator-=(const std::string& num) {return *this = *this - num;}

// Multiply and copy
Bigint& Bigint::operator*=(const Bigint& num) {return *this = *this * num;}
Bigint& Bigint::operator*=(const std::string& num) {return *this = *this * num;}

// Divide and Copy (TO BE ADDED)


// Gets Data
const std::string& Bigint::value() const {return m_number;}
const std::size_t& Bigint::size() const {return m_size;}
const bool& Bigint::sign() const {return m_sign;}


// Inputs
std::istream& operator>>(std::istream& is, Bigint& num)
{
    std::string ip;
    is >> ip;
    num = ip;
    return is;
}

// Outputs
std::ostream& operator<<(std::ostream& os, const Bigint& num)
{
    if(num.m_sign)
        os << "-";
    os << num.m_number;
    return os;
}

void Bigint::print() const {std::cout<<*this<<'\n';}
	
// Comparision
int Bigint::compare(const Bigint& b) const
{
    if(m_sign != b.m_sign)
        return m_sign ? -1 : 1;

    int compResult = compWithoutSign(m_number, b.m_number);
    return m_sign ? -compResult : compResult;
}

// Equal-to, greater than, less than 
bool Bigint::operator==(const Bigint& num) const {return this->compare(num) == 0;}
bool Bigint::operator<(const Bigint& num) const {return this->compare(num) == -1;}
bool Bigint::operator>(const Bigint& num) const {return this->compare(num) == 1;}

// Greater than or Equal to
bool Bigint::operator<=(const Bigint& num) const {return this->compare(num) != 1;}
// Less than or Equal to
bool Bigint::operator>=(const Bigint& num) const {return this->compare(num) != -1;}
