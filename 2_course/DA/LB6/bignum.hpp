#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>

const long long BASE = 1000000000;
const long long POW = 9;

namespace NBigNum{
class TBigNum{
private:
    long long Size,MaxSize;
    std::vector<long long> Nums;
    TBigNum ShortDiv(TBigNum other);
    TBigNum LongDiv(TBigNum other);
public:
    
    TBigNum();
    TBigNum(long long size);
    TBigNum(const TBigNum &other);
    TBigNum(const char* &str);
    ~TBigNum();

    long long GetSize();
    long long GetMaxSize();
    int GetNum(long long pos);
    void SetSize(long long size);
    void SetMaxSize(long long maxsize);
    void SetNum(long long pos,int num);
    void FromStr(std::string str);
    void Revers();
    TBigNum ShiftMinus(TBigNum& other,int shift = 0);
    
    TBigNum& operator=(const TBigNum other);
    TBigNum& operator=(int number);

    TBigNum operator+(TBigNum& other);
    TBigNum operator-(TBigNum& other);
    TBigNum operator-(int number);
    TBigNum operator*(TBigNum& other);
    TBigNum operator*(int number);
    TBigNum operator/(TBigNum other);
    TBigNum operator/(int number);
    TBigNum operator^(TBigNum other);

    bool operator<(const TBigNum& other);
    bool operator>(const TBigNum& other);
    bool operator==(const TBigNum& other);
    bool operator<(int number);
    bool operator>(int number);
    bool operator==(int number);

    friend std::ostream& operator<< (std::ostream &out, const TBigNum &num){
        long long size = num.Size;
        if(size > 0){
            out << num.Nums[size-1];
        }
        for(long long i = size - 1; i > 0 ; --i){
            out <<std::setw(POW) << std::setfill('0')<< num.Nums[i-1];
        }
        return out;
    }

    friend std::istream& operator>> (std::istream& in,TBigNum& num){
        std::string str;
        in >> str;
        num.FromStr(str);
        return in;
    }

    
};


}//namespace BigNum

inline NBigNum::TBigNum operator "" _bn(const char* str, size_t size){
    NBigNum::TBigNum tmp;
    tmp.FromStr(str);
    return tmp;
}