#include <iostream>
#include <string>

class bigInt
{
	private:

	// private members
	// holds the number
	std::string m_number;
	
	// holds the sign bit{false : +ve, true: -ve}
	bool m_sign{false};

	// holds the size of the number
	std::size_t m_size{};


	// private member functions
	// reverse the input string 's'
	static void reverse(std::string &s)
	{
		int start=0, end = s.size()-1;
		while(start < end)
		{
			char temp = s[start];
			s[start] = s[end];
			s[end] = temp;
			start++;
			end--;
		}
	}
	
	// compare two strings like integer numbers
	// if s1 > s2 => return 1
	// 	  s1 < s2 => return -1
	// 	  s1 == s2 => return 0
	static int compWithoutSign(const std::string& s1,const std::string& s2)
	{
		std::size_t size1 = s1.size();
		std::size_t size2 = s2.size();
		int comp = (size1 != size2) ? size1 - size2 : s1.compare(s2);
		return comp == 0 ? 0 : (comp > 0 ? 1 : -1);
	}


	// acts as a full adder
	// adds the c1, c2, carry
	// sum is stored in 'ch'
	// carry is modified
	static char calSumCy(char c1, char c2, int &carry)
	{
		char ch = c1 + c2 + carry - '0';
		if(ch > '9')
		{
			ch = ch - 10;
			carry = 1;
		}
		else
			carry = 0;
		return ch;
	}
	
	// acts as a full subtractor
	// same as 'calSumCy' instead of 'carry' it has 'borrow'
	static char calSubBr(char c1, char c2, int &borrow)
	{
		char ch = c1 - c2 - borrow + '0';
		if(ch < '0')
		{
			ch = ch + 10;
			borrow = 1;
		}
		else
			borrow = 0;
		return ch;
	}

	static void swapStrings(std::string &s1, std::string &s2, std::size_t &size1, std::size_t &size2)
{
	std::string temp = s2;
	s2 = s1;
	s1 = temp;
	std::size_t tempS = size1;
	size1 = size2;
	size2 = tempS;
}

	static void squeeze(std::string &s)
	{
		std::size_t i=0;
		std::size_t size = s.size();
		while(i<size-1 && s[i]=='0')
			i++;
		s = s.substr(i);
	}

	// accepts two strings
	// adds (integers in) two strings and return the result string
	static const std::string addStrings(const std::string& s1,const std::string& s2)
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
	static const std::string subStrings(const std::string& s1,const std::string& s2)
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


	public:
	explicit bigInt(const std::string& num)
	{
		if(num[0] == '-')
		{
			m_number = num.substr(1);
			m_sign = true;
		}
		else
			m_number = num;
		m_size = m_number.size();
	}
	
	void setValue(std::string num)
	{
		if(num[0] == '-')
		{
			m_number = num.substr(1);
			m_sign = true;
		}
		else
			m_number = num;
		m_size = m_number.size();
	}

	const std::string& value() const {return m_number;};

	void print() const
	{
		if(m_sign)
			std::cout<<'-';
		std::cout<<m_number<<'\n';
	}
	
	int compare(const bigInt& b)
	{
		if(m_sign != b.m_sign)
			return m_sign ? -1 : 1;

		int compResult = compWithoutSign(m_number, b.m_number);
		return m_sign ? -compResult : compResult;
	}


	bigInt add(const bigInt &num2) const
	{
		bigInt result("");
		if(m_sign == num2.m_sign)
		{
			result.setValue(addStrings(m_number, num2.m_number));
			result.m_sign = m_sign;
			return result;
		}
		
		int comp = compWithoutSign(m_number, num2.m_number);
		if(comp > 0)
		{
			result.setValue(subStrings(m_number, num2.m_number));
			result.m_sign = m_sign;
		}
		else if(comp < 0)
		{
			result.setValue(subStrings(num2.m_number, m_number));
			result.m_sign = num2.m_sign;
		}
		else
			result.setValue("0");

		return result;
	}

	bigInt sub(const bigInt &num2) const
	{
		bigInt result("");

		if(m_sign != num2.m_sign)
		{
			result.setValue(addStrings(m_number, num2.m_number));
			result.m_sign = m_sign;
			return result;
		}

		int comp = compWithoutSign(m_number, num2.m_number);
		if(comp > 0)
		{
			result.setValue(subStrings(m_number, num2.m_number));
			result.m_sign = m_sign;
		}
		else if(comp < 0)
		{
			result.setValue(subStrings(num2.m_number, m_number));			
			result.m_sign = !num2.m_sign;
		}
		else
			result.setValue("0");

		return result;
	}


	//  Function to add a number string directly to the object
	// without creating a new Object
	void addStr(const std::string& num)
	{
		bool sign = false;
		std::string str{};
		if(num[0] == '-')
		{
			sign = true;
			str = num.substr(1);
		}
		else
			str = num;
		if(m_sign == sign)
			m_number = addStrings(m_number, str);
		else
		{	
			int comp = compWithoutSign(m_number, str);
			if(comp > 0)
				m_number = subStrings(m_number, str);
			else if(comp < 0)
			{
				m_number = subStrings(str, m_number);			
				m_sign = sign;
			}
			else
				m_number = "0";
		}
	}

	// Fucntion to subtarct a numebr string directly to the object
	// without creating a new Object
	void subStr(const std::string& num)
	{
		bool sign = false;
		std::string str{};
		if(num[0] == '-')
		{
			sign = true;
			str = num.substr(1);
		}
		else
			str = num;
		if(m_sign != sign)
			m_number = addStrings(m_number, str);
		else
		{	
			int comp = compWithoutSign(m_number, str);
			if(comp > 0)
				m_number = subStrings(m_number, str);
			else if(comp < 0)
			{
				m_number = subStrings(str, m_number);			
				m_sign = !sign;
			}
			else
				m_number = "0";
		}
	}



};

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		std::cout << "Use: " << argv[0] << " <num1> <num2> <op>\n";
		return 1;
	}

	bigInt a(argv[1]);
	bigInt b(argv[2]);
	char ch = *argv[3];
	switch(ch)
	{
		case 'k': 
		std::cout << a.compare(b);
		break;
		
		case '+':
		//a.add(b).print();
		a.addStr(argv[2]);
		a.print();
		a.addStr("-1000");
		a.print();
		std::cout << a.value()<<'\n';
		break;

		case '-':
		a.print();
		a.subStr(argv[2]);
		a.print();
		std::cout << "vlaue: " << a.value() << '\n';
		break;

		case 'c':
		a.print();
		a.setValue(argv[2]);
		a.print();
		break;
		default:
			std::cout << "Error: Use right operator\n";
	}
		
	return 0;
}
