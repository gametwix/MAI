//Класс для взаимодействия с суммами британских денег

#include <iostream>


class BritishMoney 
{
    private:

        unsigned long long pounds;
        unsigned char shilling;
        unsigned char penny;    

        BritishMoney sum(const BritishMoney &a,const BritishMoney &b);

        BritishMoney diff(BritishMoney a,BritishMoney b);

        BritishMoney norm(const BritishMoney &a);

        void norm();
        
        double div(BritishMoney a,BritishMoney b);

        BritishMoney impl(const BritishMoney &a,double b);
        

    public:
        //операции ввода вывода
        friend std::ostream& operator<< (std::ostream &out, const BritishMoney &a)
        {
            out << a.pounds << " " << (int)a.shilling << " " << (int)a.penny;
            return out;
        }

        friend std::istream& operator>>(std::istream &in, BritishMoney &a)
        {
            unsigned long long pounds;
            int shilling;
            int penny;
            BritishMoney c;
            in >> pounds >> shilling >> penny;
            if (pounds >= 0 && shilling >= 0 && penny >= 0)
            {
                a.pounds = pounds;  
                a.shilling = shilling;
                a.penny = penny;
            }
            else
            {
                a.pounds = 0;  
                a.shilling = 0;
                a.penny = 0;
            }
            
            a.norm();
            return in;
        }


        void get(unsigned long long pounds, int shilling,int penny)
        {
            this->pounds = pounds;
            this->shilling = shilling;
            this->penny = penny;
            norm(*this);
        }

        void print();

        BritishMoney()
        {
            this->pounds = 0;
            this->shilling = 0;
            this->penny = 0;
        }

        //операция присваивания
        void operator =(const BritishMoney &b)
        {
            pounds = b.pounds;
            shilling = b.shilling;
            penny = b.penny;
        }

        //арефимитические операции
        BritishMoney operator+(BritishMoney b)
        {
            return sum(*this,b);
        }

        BritishMoney operator-(BritishMoney b)
        {
            return diff(*this,b);
        }

        BritishMoney operator*(double b) 
        {
            return impl(*this,b);
        }

        BritishMoney operator/(double b)
        {
            BritishMoney c;
            c = *this * (1/b);
            return c;
        }

        double operator/(BritishMoney b)
        {
            return div(*this,b);
        }

        //операции сравнения
        bool operator==(const BritishMoney &b)
        {
            if(this->pounds == b.pounds && this->shilling == b.shilling && this->penny == b.penny)
                return true;
            else return false;
        }

        bool operator!=(const BritishMoney &b)
        {
            return !(*this == b);
        }

        bool operator>(const BritishMoney &b)
        {
            if(this->pounds > b.pounds) return true;
            else if(this->pounds == b.pounds)
            {
                if((int)this->shilling > (int)b.shilling) return true;
                else if((int)this->shilling == (int)b.shilling)
                {
                    if((int)this->penny > (int)b.penny) return true;
                    else false;
                }
                else return false;
            }
            else return false;
            return false;
        }

        bool operator<(const BritishMoney &b)
        {
            if(this->pounds < b.pounds) return true;
            else if(this->pounds == b.pounds)
            {
                if((int)this->shilling < (int)b.shilling) return true;
                else if((int)this->shilling == (int)b.shilling)
                {
                    if((int)this->penny < (int)b.penny) return true;
                    else false;
                }
                else return false;
            }
            else return false;
            return false;
        }

        bool operator>=(const BritishMoney &b)
        {
            return ((*this>b)||(*this==b));
        }

        bool operator<=(const BritishMoney &b)
        {
            return ((*this<b)||(*this==b));
        }

};
