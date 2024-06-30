#ifndef BIGINT_H
#define BIGINT_H


// Includes

// Standered libraries
#include <iostream>
// STL
#include <string>

/**
 * Bigint class
 * This class holds values of integers as std::string, 0th index is the MSB, last index has the LSB
 * Sign of the integer is stored as boolean value, TRUE means -ve, FALSE means +ve
 * The number of the digits of the integer is also being tracked
*/

// clas definition
class Bigint{
    private:

    // private members
	std::string m_number; // Holds the number string
	bool m_sign; // Holds the sign bit{false : +ve, true: -ve}
	std::size_t m_size; // holds the size of the number

    // utility funcitons
    static void reverse(std::string &s);// reverses string
    static int compWithoutSign(const std::string& s1,const std::string& s2); // compares two strings without sign
    static char calSumCy(char c1, char c2, int &carry);// Acts as full adder
    static char calSubBr(char c1, char c2, int &borrow);// Acts as full subtarctor
    static char calMulCy(const char& c1, const char& c2, int& carry);// multiplies c1 with c2 with carry
    static void swapStrings(std::string &s1, std::string &s2, std::size_t &size1, std::size_t &size2);// Swaps two strings
    static void squeeze(std::string &s);// Gets rid of any leading zero
    static std::string addStrings(const std::string& s1, const std::string& s2); // Adds two strings digit by digit
    static std::string subStrings(const std::string& s1, const std::string& s2); // Subtracts two strings digit by digit
    static std::string mulStrings(const std::string& s1, const std::string& s2); // Multiplies two strings digit by digit
    static std::string mulStringsFFT(const std::string&, const std::string&); // Multiplies strings using Sconhage-Strassen algo 
    static void addStringsToFirst(std::string& s1, const std::string& s2);// Adds two strings and the result is stored in first string

    public:

    // public member functions
    explicit Bigint(const std::string& num="0"); // Default constructor

    Bigint& operator=(const Bigint&); // Copy assignment operator
    Bigint& operator=(const std::string&); // Same but works directly for String

    // Addition
    Bigint operator+(const Bigint&) const; // Adds two Bigint objects, Returns a Bigint
    Bigint operator+(const std::string&) const; // Adds a "valid" string integer with a Bigint object, Returns a Bigint

    // Subtraction
    Bigint operator-(const Bigint&) const; // Subtracts two Bigint, Returns a Bigint
    Bigint operator-(const std::string&) const; // Subtracts a "Valid" string integer with a Bigint object, Returns a Bigint

    // Multiplication
    Bigint operator*(const Bigint&) const; // Multiplies two Bigints, Returns a Bigint
    Bigint operator*(const std::string&) const; // Multiplies a "Valid" strings, if "invalid" "0" is returnd, returns a Bigint

    // Multiplication using Stohange Stassen's FFT algorithm (not optimized)
    Bigint mulFFT(const Bigint&) const;
    Bigint mulFFT(const std::string&) const;


    // Add and copy
    Bigint& operator+=(const Bigint&);
    Bigint& operator+=(const std::string&);

    // Subtract and copy
    Bigint& operator-=(const Bigint&);
    Bigint& operator-=(const std::string&);

    // Multiply and copy
    Bigint& operator*=(const Bigint&);
    Bigint& operator*=(const std::string&);

    // Comparision
    bool operator==(const Bigint&) const;
    bool operator<(const Bigint&) const;
    bool operator>(const Bigint&) const;

    bool operator<=(const Bigint&) const;
    bool operator>=(const Bigint&) const;

    int compare(const Bigint&) const; // if greater returns a 1, if less -1, if equal 0  

    // Power
    Bigint operator^(const int&) const;

    // Gets data
    const std::string& value() const; // Gets the value As a string(without sign)
    const std::size_t& size() const; // Gets size
    const bool& sign() const; // Gets sign

    // For output
    friend std::ostream& operator<<(std::ostream&, const Bigint&);
    friend std::istream& operator>>(std::istream&, Bigint&);
    void print() const;


};

#endif