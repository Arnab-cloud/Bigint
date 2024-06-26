#include <iostream>
#include <string>
#include <algorithm>

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
    static void addStringsToFirst(std::string& s1, const std::string& s2);// Adds two strings and the result is stored in first string

    public:
    // public member functions
    explicit Bigint(const std::string& num="0"); // Default constructor

    Bigint& operator=(const Bigint&); // Copy assignment operator
    Bigint& operator=(const std::string&); // Same but works directly for String

    // Addition
    Bigint operator+(const Bigint&) const;
    Bigint operator+(const std::string&) const;
    // void addStr(const std::string&); // Adds string directly

    // Subtraction
    Bigint operator-(const Bigint&) const;
    Bigint operator-(const std::string&) const;
    // void subStr(const std::string&);

    // Multiplication
    Bigint operator*(const Bigint&) const;
    Bigint operator*(const std::string&) const;

    // Division

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

    int compare(const Bigint&) const;

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

// Funcion Definitons

Bigint::Bigint(const std::string& num):m_number{"0"}, m_sign{false}, m_size{1}  // Default constructor
{
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


void Bigint::reverse(std::string &s) {std::reverse(s.begin(), s.end());}

int Bigint::compWithoutSign(const std::string& s1,const std::string& s2)
{
    std::size_t size1 = s1.size();
    std::size_t size2 = s2.size();
    int comp = (size1 != size2) ? size1 - size2 : s1.compare(s2);
    return comp == 0 ? 0 : (comp > 0 ? 1 : -1);
}

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
        temp.append(size2-j,'0');
        addStringsToFirst(result, temp);
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


// Driver Code
int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		std::cout << "Use: " << argv[0] << " <num1> <num2> <op>\n";
		return 1;
	}

    Bigint ip;
    int n = atoi(argv[2]);
	Bigint a(argv[1]);
	Bigint b(argv[2]);
	char ch = *argv[3];
	switch(ch)
	{
		case 'k': 
            if(a > b)
                std::cout << "a is greater than b\n";
            else    std::cout << "b is greater than  or eqaul to a\n";
		break;
		
		case '+':
        std::cout << "a is "<< a <<"\nb is " << b << '\n';
		std::cout << "a + b is : " << a+b << '\n';
        std::cout << "a is added to -1000"<<std::endl;
		a += "-1000";
		a.print();
		std::cout << (a+b);
		break;

		case '-':
		std::cout << "a is "<< a <<"\nb is " << b << '\n';
		std::cout << "a - b is : " << a - b << '\n';
        std::cout << "a is sub to -1000"<<std::endl;
		a -= "-1000";
		a.print();
		std::cout << (a-b) << std::endl;
		break;

		case 'c':
		a.print();
		a = argv[2];
		a.print();
		break;

		case '.':
		(a*b).print();
		break;

		case 'm':
        std::cout<<n<<'\n';
        a = a^n;
		// a.print();
		std::cout << "number of digits: " << a.size() << std::endl;
		break;

        case 'i':
        std::cout<< "Enter the number: ";
        std::cin >> ip;
        std::cout << "The number is " << ip<<std::endl; 
        break;

		case 'p':
			std::cout << (a^atoi(argv[2])) << std::endl; 
			break;
		default:
			std::cout << "Error: Use right operator\n";
	}
		
	return 0;
}
