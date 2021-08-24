#ifndef BASE
#define BASE

#include <iostream>
#include <iomanip>
#include <cstring>

namespace NCarnum
{
    class TCarnum
    {
        public:
        int Num = 0;
        char Sym[3]={'A','A','A'};

        void operator=(const TCarnum &second_elem)
        {
            this->Num = second_elem.Num;
            std::memcpy(Sym,second_elem.Sym,sizeof(char)*3);

        }

        friend std::istream& operator>>(std::istream &in, TCarnum &carnum)
        {
            in >> carnum.Sym[0] >> carnum.Num >> carnum.Sym[1] >> carnum.Sym[2];
            return in;
        }

        friend std::ostream& operator<< (std::ostream &out, const TCarnum &carnum)
        {
            out << carnum.Sym[0] << " " <<  std::setfill('0') << std::setw(3) << carnum.Num << " " << carnum.Sym[1] << carnum.Sym[2];
            return out;
        }

        bool operator<(const TCarnum &b)
        const
        {
            if((int)(this->Sym[0])-65 < (int)(b.Sym[0])-65) return true;
            else
            {
                if(this->Num < b.Num) return true;
                else
                {
                    if((int)(this->Sym[1])-65 < (int)(b.Sym[1])-65) return true;
                    else
                    {
                        if((int)(this->Sym[2])-65 < (int)(b.Sym[2])-65) return true;
                        else
                        {
                            return false;
                        }
                    }
                    
                }
                
            }
            
        }
        
    }; // class TCarnum

} // namespace NCarnum


namespace NBase
{
    class TBase_elem
    {
        public:
        NCarnum::TCarnum Carnum;
        char Str[65] = "";

       
        void operator=(const TBase_elem &second_elem)
        {
            this->Carnum = second_elem.Carnum;
            std::memcpy(Str,second_elem.Str,sizeof(char)*64);
            
        }


        friend std::istream& operator>>(std::istream &in, TBase_elem &elem)
            {
                in >> elem.Carnum;
                in.peek();
                in >> elem.Str;
                return in;
            }

        friend std::ostream& operator<< (std::ostream &out, const TBase_elem &elem)
            {
                out << elem.Carnum << "\t" <<  elem.Str;
                return out;
            }


        bool operator< (const TBase_elem &b)
        const
        {
            return this->Carnum < b.Carnum;
        }
    }; // class TCarnum
} // namespace NCarnum

#endif
