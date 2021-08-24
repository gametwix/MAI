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

namespace NBigNum{
TBigNum::TBigNum():Size(0), MaxSize(0){}
TBigNum::TBigNum(long long size): Size(0),MaxSize(size){
    Nums.resize(size);
}
TBigNum::TBigNum(const TBigNum &other):Size(other.Size), MaxSize(other.MaxSize){
    Nums.resize(other.MaxSize);
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());
}

TBigNum::TBigNum(const char* &str){
    (*this).FromStr(str);
}

TBigNum::~TBigNum(){}

long long TBigNum::GetSize(){ return Size; }
long long TBigNum::GetMaxSize(){ return MaxSize; }
int TBigNum::GetNum(long long pos){ return Nums[pos]; }
void TBigNum::SetSize(long long size){ Size = size; }
void TBigNum::SetMaxSize(long long maxsize){ MaxSize = maxsize; }
void TBigNum::SetNum(long long pos,int num){ Nums[pos] = num; }

void TBigNum::Revers(){
    int tmp;
    for(long long i = 0;i < Size/2 ;++i){
        tmp = Nums[Size - i - 1];
        Nums[Size - i - 1] = Nums[i];
        Nums[i] = tmp;
    }
}

TBigNum TBigNum::ShortDiv(TBigNum other){
    if(other.Size == 1 && other.Nums[0] == 0){ throw -1; }
    if(Size == 1 && other.Size == 1){ 
        TBigNum ans;
        ans.FromStr(std::to_string(Nums[0]/other.Nums[0]));
        return ans;
    }
    TBigNum ans(0);
    int past = 0;
    for(int i = Size - 1; i >=0; --i){
        long long q = (Nums[i] + past*BASE);
        long long num = q / other.Nums[0];
        ans.Nums.insert(ans.Nums.begin(),num);
        ++ans.MaxSize;
        ++ans.Size;
        past = q - num*other.Nums[0];
    }

    long long i = ans.Size - 1;
    while((i > 0) && (ans.Nums[i] == 0)) --i;
    ans.Size = i+1;
    return ans;
}

TBigNum TBigNum::LongDiv(TBigNum other){
    if(other.Size == 1 && other.Nums[0] == 0){ throw -1; }
    if(*this < other){
        TBigNum ans;
        ans.FromStr("0");
        return  ans; }
    if(Size == 1 && other.Size == 1){ 
        TBigNum ans;
        ans.FromStr(std::to_string(Nums[0]/other.Nums[0]));
        return ans;
    }
    long long n = other.Size;
    long long m = Size - other.Size;
    TBigNum tmp(Size + 1);
    TBigNum ans(0);
    tmp = *this;
    int norm = BASE/(other.Nums[n - 1] + 1);
    tmp = tmp * norm;
    other = other * norm;
    for(int i = m; i >= 0; --i){
        int q = (tmp.Nums[i+n]*BASE + tmp.Nums[i+n-1]) / other.Nums[n-1];
        int r = (tmp.Nums[i+n]*BASE + tmp.Nums[i+n-1]) % other.Nums[n-1];
        while(r < BASE){
            if(q == BASE || q*other.Nums[n-2] > BASE * r + tmp.Nums[i+n-2]){
                --q;
                r += other.Nums[n-1];
            } else break;
        }
        try {
            TBigNum mul = other*q;
            tmp = tmp.ShiftMinus(mul,i);
        }
        catch(int ch){
            --q;
            TBigNum mul = other*q;
            tmp = tmp.ShiftMinus(mul,i);
        }
        ans.Nums.insert(ans.Nums.begin(),q);
        ++ans.MaxSize;
        ++ans.Size;
    }
    long long i = ans.Size - 1;
    while((i > 0) && (ans.Nums[i] == 0)) --i;
    ans.Size = i+1;
    return ans;
}

TBigNum& TBigNum::operator=(const TBigNum other){
    if(&other == this) return *this;
    if(MaxSize < other.Size){
        Nums.resize(other.Size);
        MaxSize = other.Size;
    }
    Size = other.Size;
    Nums.assign(Nums.size(), 0);
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());

    return *this;
}

TBigNum& TBigNum::operator=(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    if(&other == this) return *this;
    if(MaxSize < other.Size){
        Nums.resize(other.Size);
        MaxSize = other.Size;
    }
    Size = other.Size;
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());
    return *this;
}

void TBigNum::FromStr(std::string str){
    long long size = str.size();
    long long size_num = size / POW + ((size % POW > 0 ) ? 1:0);
    long long start = 0;
    long long length = 0;
    if(MaxSize < size_num){
        MaxSize = size_num;
        Nums.resize(MaxSize);
    }
    
    
    for( long long i = 0; i < size_num;++i){
        start = size - i*POW;
        if(start >= POW){
            length = POW;
            start -= POW;
        } else {
            length = start;
            start = 0;
        }

        Nums[i]=stoi(str.substr(start,length));
    }   

    int i = size_num - 1;
    while( i > 0 && Nums[i] == 0) --i;
    Size = i+1;
}

TBigNum TBigNum::operator+(TBigNum& other){
    int past = 0;
    int tmp = 0;
    if(other.Size > Size)
        return other + (*this);
    TBigNum answer(Size + 1);
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] + other.Nums[i] + past;
        past = 0;
        if (tmp >= BASE){
            tmp = tmp - BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(long long i = other.Size; i < Size; ++i){
        tmp = Nums[i] + past;
        past = 0;
        if (tmp >= BASE){
            tmp = tmp - BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }
    answer.Size = Size;

    if(past > 0){
        answer.Nums[Size] = past;
        ++answer.Size;
    }
    return answer;
}


TBigNum TBigNum::operator-(TBigNum& other){
    int past = 0;
    int tmp = 0;
    if(other.Size > Size){
        throw -1;
    }
    TBigNum answer(Size);
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(long long i = other.Size; i < Size; ++i){
        tmp = Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    if(past > 0)
        throw -1;
    
    long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}

TBigNum TBigNum::operator-(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    int past = 0;
    int tmp = 0;
    if(other.Size > Size){
        throw -1;
    }
    TBigNum answer(Size);
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(long long i = other.Size; i < Size; ++i){
        tmp = Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    if(past > 0)
        throw -1;
    
    long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}


TBigNum TBigNum::operator*(TBigNum& other){
    long long tmp = 0;
    long long past = 0;
    TBigNum answer(Size + other.Size);

    for(long long i = 0; i < Size; ++i){
        for(long long j = 0;j < other.Size;++ j){
            tmp = Nums[i]*other.Nums[j] + answer.Nums[i+j] + past;
            past = tmp / BASE;
            tmp = tmp % BASE;
            answer.Nums[i+j] = tmp;

        }
        answer.Nums[i + other.Size] = past;
        past = 0;
    }



    long long i = Size + other.Size - 1;
    
    while ((i > 0) && (answer.Nums[i] == 0)) --i;

    answer.Size = i+1;

    return answer;
}



TBigNum TBigNum::operator*(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    return *this * other;
}


TBigNum TBigNum::ShiftMinus(TBigNum& other,int shift){
    int past = 0;
    int tmp = 0;
    if((other.Size + shift) > Size){
        throw -1;
    }
    TBigNum answer(Size);
    answer = *this;
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i+shift] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i+shift] = tmp;
    }

    for(int i = other.Size; i < Size-shift; ++i){
        tmp = Nums[i+shift] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i+shift] = tmp;
    }

    if(past > 0)
        throw -1;
    
    long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}

TBigNum TBigNum::operator/(TBigNum other){
    if(other.Size == 1 && other < BASE)
        return this->ShortDiv(other);
    else
        return this->LongDiv(other);
}

TBigNum TBigNum::operator/(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    if(other.Size == 1 && other < BASE)
        return this->ShortDiv(other);
    else
        return this->LongDiv(other);
}

TBigNum TBigNum::operator^(TBigNum other){
    TBigNum ans;
    if(other == 0){
        if(*this == 0)
            throw -1;
        else{
            ans.FromStr("1");
            return ans;
        }
    }
    if(other == 1) return *this;
    if(other.Nums[0] % 2 == 0){
        ans = *this ^ (other / 2);
        return ans*ans;
    } else {
        ans = *this ^ (other - 1);
        ans = *this * ans; 
    return ans;}
}
bool TBigNum::operator<(const TBigNum& other){
    if(Size < other.Size) return true;
    else if(Size > other.Size) return false;
    else {
        bool ans = false;
        for(long long i = Size - 1; i >= 0 && !(Nums[i] > other.Nums[i]); --i){
            if(Nums[i] < other.Nums[i]) ans = true;
        }
        return ans;
    }
}

bool TBigNum::operator>(const TBigNum& other){
    return !(*this < other) && !(*this == other);
}
bool TBigNum::operator==(const TBigNum& other){
    if(Size != other.Size) return false;
    else{
        bool ans = true;
        for(int i = Size - 1; i >= 0; --i)
            if(Nums[i] != other.Nums[i]) ans = false;
        return ans;
    }
}

bool TBigNum::operator<(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    return *this < other;
}

bool TBigNum::operator>(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    return *this > other;
}

bool TBigNum::operator==(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    return *this == other;
}

} //namespace BigNum

int main(){
    NBigNum::TBigNum num[2];
    char sym;
    while(std::cin >> num[0] >> num[1] >> sym){
        switch(sym){
            case '+':
                std::cout << num[0] + num[1] << std::endl;
                break;
            case '-':
                try{
                std::cout << num[0] - num[1] << std::endl;
                } catch( int i){
                    std::cout << "Error" <<std::endl;
                }
                break;
            case '*':
                std::cout << num[0] * num[1] << std::endl;
                break;
            case '/':
                try{
                std::cout << num[0] / num[1] << std::endl;
                } catch( int i){
                    std::cout << "Error" <<std::endl;
                }
                break;
            case '^':
                try{
                std::cout << (num[0] ^ num[1]) << std::endl;
                } catch( int i){
                    std::cout << "Error" <<std::endl;
                }
                break;
            case '>':
                std::cout << ((num[0] > num[1]) ? "true" : "false") << std::endl;
                break;
            case '=':
                std::cout << ((num[0] == num[1]) ? "true" : "false") << std::endl;
                break;
            case '<':
                std::cout << ((num[0] < num[1]) ? "true" : "false") << std::endl;
                break;
        }
    }

    return 0;
}

