#pragma once
#include "string.hpp"
#include <fstream>

namespace NPair
{
    class TPair
    {
        public:
            unsigned long long Num;
            NString::TString Str;

            TPair(){}

            TPair(NString::TString rStr,unsigned long long rNum)
            {
                Str = rStr;
                Num = rNum;
            }

            bool operator==(const TPair& second)
            {
                return (Str == second.Str);
            }

            bool operator<(TPair& second)
            {
                return (Str < second.Str);
            }

            void operator=(const TPair& second)
            {
                Num = second.Num;
                Str = second.Str;
            }
            void save(std::ofstream& wf)
            {
                wf.write((char *) &Num,sizeof(unsigned long long));
                Str.save(wf);
            }

            void load(std::ifstream& rf)
            {
                rf.read((char *) &Num,sizeof(unsigned long long));
                Str.load(rf);
            }

            friend std::ostream& operator<< (std::ostream &out, const TPair &pair)
            {
                out << "(" << pair.Str << "," << pair.Num << ")";
                return out;
            }
    };
}//namespace NPair