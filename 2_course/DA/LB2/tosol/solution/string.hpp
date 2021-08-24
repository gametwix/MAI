#pragma once
#include <cstring>
#include <iostream>
#include <fstream>
#include <cctype>

namespace NString
{
    class TString
    {
            
        public:
            char* str;
            size_t size;

            
            TString()
            {
                str = new char[257];
                size = 0;
            }

            TString(const TString &second)
            {
                str = new char[257];
                size = second.size;
                std::memcpy(str,second.str,sizeof(char)*257);
            }

            TString(const char *second)
            {
                str = new char[257];
                size = sizeof(second);
                std::memcpy(str,second,sizeof(char)*size);
            }

            ~TString()
            {
                delete[] str;
            }


            void operator=(const TString &second)
            {
            std::memcpy(str,second.str,sizeof(char)*257);
            size = second.size;
            }

            void operator=(char *second)
            {
            size = sizeof(second);
            std::memcpy(str,second,sizeof(char)*size);
            }

            bool operator==(const TString &second)
            {
                for(int i=0;i<257;++i)
                {
                    if(str[i]!=second.str[i])
                        return false;
                    if(str[i]=='\0')
                        break;
                }
                return true;
            }

            bool operator==(const char *second)
            {
                for(int i=0;i<257;++i)
                {
                    if(str[i]!=second[i])
                        return false;
                    if(str[i]=='\0')
                        break;
                }
                return true;
            }

            bool operator>(const TString &second)
            {
                for(int i=0;i<257;++i)
                {
                    if(str[i]==second.str[i] && str[i]!='\0')
                        continue;
                    if(str[i]>second.str[i] || (second.str[i] == '\0' && str[i] != '\0'))
                        return true;
                    else
                        break;
                    
                }
                return false;
            }

            const bool operator<(const TString &second)
            {
                for(int i=0;i<257;++i)
                {
                    if(str[i]==second.str[i] && str[i]!='\0')
                        continue;
                    if(str[i]<second.str[i] || (second.str[i] != '\0' && str[i] == '\0'))
                        return true;
                    else
                        break;
                    
                }
                return false;
            }

            friend std::ostream& operator<< (std::ostream &out, const TString &str)
            {
                out << str.str;
                return out;
            }

            friend std::istream& operator>>(std::istream &in, TString &str)
            {
                if(in >> str.str)
                {
                    while(str.str[str.size] != '\0')
                    ++str.size;
                }
                return in;
            }

            int find(char ch)
            {
                for(int i=0;i<257;++i)
                {
                    if(this->str[i] == ch)
                        return i;
                    if(this->str[i] == '\0')
                        return -1;
                }
                return -1;
            }

            int find(const char ch, int start)
            {
                if(start > 257)
                    start = 257;
                for(int i=start;i<257;++i)
                {
                    if(this->str[i] == ch)
                        return i;
                    if(this->str[i] == '\0')
                        return -1;
                }
                return -1;
            }

            char &operator[](size_t index)
            {
                return this->str[index];
            }

            void save(std::ofstream& wf)
            {
                wf.write((char *) &size,sizeof(int));
                wf.write(str,sizeof(char)*(size+1));
            }

            void load(std::ifstream& rf)
            {
                rf.read((char *) &size,sizeof(int));
                rf.read(str,sizeof(char)*(size+1));
            }
            void lower()
            {
                for(int i = 0; i < size+1; i++) 
                {
                    str[i] = std::tolower(str[i]);
                }
            }
    };
} //namespace NString