#include <iostream>
#include <string>

class bigInt
{
	private:
	std::string number;
	bool sign{false};
	public:
	bigInt(std::string num)
	{
		if(num[0] == '-')
		{
			number = num.substr(1);
			sign = true;
		}
		else
			number = num;
	}
	
	void value(std::string num)
	{
		if(num[0] == '-')
		{
			number = num.substr(1);
			sign = true;
		}
		else
			number = num;
	}

	void print()
	{
		if(sign)
			std::cout<<'-';
		std::cout<<number;
	}
	
	char calSumCy(char c1, char c2, int &carry)
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

	bigInt addBigInt(bigInt num2)
	{
		bigInt b("");
		std::string s1 = number;
		std::string s2 = num2.number;
		
		int size1 = s1.size();
		int size2 = s2.size();
		if(size2 > size1)
		{
			std::string temp = s2;
			s2 = s1;
			s1 = temp;
			int tempS = size1;
			size1 = size2;
			size2 = tempS;
		}
		
		std::string temp = "";
		int carry= 0;
		int i1 = size1-1, i2 = size2-1;
		while(i1>=0 && i2 >= 0)
		{
			char ch = calSumCy(s1[i1--], s2[i2--], carry);
			temp.insert(0,1,ch);
		}
		if(size1 > size2)
		{
			while(carry && i1>=0)
			{
				char ch = calSumCy(s1[i1--], '0', carry);
				temp.insert(0,1,ch);
			}
			if(!carry && i1>=0)
				temp.insert(0,s1.substr(0,i1+1));
		}
		if(carry)
			temp.insert(0,1,'1');
		
		b.value(temp);
		return b;
	}
};

int main()
{

	bigInt a("4667527771816363667793925935923754311949934927911888888888888888888888888888888888888888888888888888888684354831843154356835544444444444444444444444444445555555555555555555555555555555555555555555555444999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999777777777777777778");
	bigInt b("694279681418036820800019091721761350130668906015874831843154356835544444444444444444444444444445555555555555555555555555555555555555555555555444999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999777777777777777778");
	bigInt c = a.addBigInt(b);
	c.print();
	return 0;
}
