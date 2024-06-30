#include<iostream>
#include<complex>
#include<vector>

#define NUM_BASE 10;

template<typename T>
constexpr T pi = 3.1415926535897932384626433832795;

template<typename T>
using cmplx_list_t = std::vector<std::complex<T>>;

template<typename T>
using cmplx_size_t = typename cmplx_list_t<T>::size_type; 

template<typename T>
using cmplx_val_t = typename cmplx_list_t<T>::value_type;


template<typename T>
cmplx_size_t<T> next_pow2(cmplx_size_t<T> n) {
    if(n <= 1)
        return 1;
    n--;

    std::size_t size= sizeof(n);
    for(std::size_t i =1; i<size; i <<= 1)
        n |= n >> i;
    return n+1;
}

template<typename T>
void fft(cmplx_list_t<T>& a, const std::complex<T>& omega)
{
    cmplx_size_t<T> len = a.size();
    if(len == 1)
        return;
    
    cmplx_size_t<T> halfLen = len/2;
    cmplx_list_t<T> evens(halfLen);
    cmplx_list_t<T> odds(halfLen);

    // cmplx_size_t<T> ie = 0, io = 0;
    for(cmplx_size_t<T> i = 0; i<halfLen; i++)
    {
        evens[i] = a[2*i];
        odds[i] = a[2*i+1];
    }

    // recursion
    std::complex<T> wSq = omega*omega; 
    fft<T>(evens, wSq);
    fft<T>(odds, wSq);

    // combine even and odd permutations
    std::complex<T> x{1,0};
    std::complex<T> temp; 
    for(cmplx_size_t<T> i = 0; i< halfLen; i++)
    {
        temp = x*odds[i];   
        a[i] = evens[i] + temp;
        a[i + halfLen] = evens[i] - temp;
        x *= omega;
    }
}

template<typename T>
void i_fft(cmplx_list_t<T>& y,const std::complex<T>& omega)
{
    T len = static_cast<T>(y.size());
    fft(y, std::conj(omega));
    for(cmplx_val_t<T>& ele : y)
        ele /= len;
}

template<typename T>
std::vector<cmplx_list_t<T>> createTable(const std::vector<int>& a, const std::vector<int>& b)
{
    cmplx_size_t<T> aLen = static_cast<cmplx_size_t<T>>(a.size());
    cmplx_size_t<T> bLen = static_cast<cmplx_size_t<T>>(b.size());
    cmplx_size_t<T> size = next_pow2<T>(aLen+bLen);

    // allocate a table
    std::vector<cmplx_list_t<T>> fft_table(3, cmplx_list_t<T>(size));

    // put the coeffs of a
    for(cmplx_size_t<T> i=0; i<size; i++)
    {
        fft_table[0][i] = i < aLen ? static_cast<cmplx_val_t<T>>(a[i]) : 0; 
        fft_table[1][i] = i < bLen ? static_cast<cmplx_val_t<T>>(b[i]) : 0; 
        fft_table[2][i] = 0;
    }
    return fft_table;
}

template<typename T>
long long eval(const cmplx_list_t<T>& a)
{
    long long res=0;
    cmplx_size_t<T> len = a.size();
    for(int i = len-1; i>=0; i--)
    {
        res *= NUM_BASE;
        res += std::floor(a[i].real() + 0.5);
        // std::cout << res << '\n';
    }
    return res;
}

template<typename T>
void print_table(const std::vector<cmplx_list_t<T>>& table)
{
    for(const cmplx_list_t<double>& list : table)
    {
        for(const cmplx_val_t<double>& ele: list)
            std::cout << ele << ", ";
        std::cout << '\n';
    }
}

std::vector<int> mulstrassen(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<cmplx_list_t<double>> fft_table = std::move(createTable<double>(a,b));
    cmplx_size_t<double> fft_len = fft_table[0].size();

    std::vector<int> ret(fft_len);
    // calculate fft
    double theta = 2.0 * pi<double> / (double)fft_len;
    std::complex<double> omega = {std::cos(theta), std::sin(theta)};
    // std::cout << "Value of omega : " << omega << '\n';
    
    // std::cout<< "Table before:\n";
    // print_table(fft_table);
    
    fft<double>(fft_table[0], omega);
    fft<double>(fft_table[1], omega);

    // do a point-wise multiplication
    for(cmplx_size_t<double> i = 0; i < fft_len; i++)
        fft_table[2][i] = fft_table[0][i] * fft_table[1][i];

    // do the i_fft
    i_fft(fft_table[2], omega);
    for(std::size_t i=0; i<fft_len; i++)
        ret[i] = std::floor(fft_table[2][i].real() + 0.5);
    return ret;
} 