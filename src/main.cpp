#include<iostream>
#include"Bigint.h"

// Driver Code
int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		std::cout << "Use: " << argv[0] << " <num1> <num2> <op>\n";
		return 1;
	}

    Bigint ip;
    Bigint c;
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
		std::cout << (a*b).size()<<'\n';
		break;

        case 'f':
            std::cout << a.mulFFT(b).size()<<'\n';
            break;
		// to calculate power
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
        // also to calculate power
			std::cout << (a^atoi(argv[2])) << std::endl; 
			break;
		default:
			std::cout << "Error: Use right operator\n";
	}
		
	return 0;
}
