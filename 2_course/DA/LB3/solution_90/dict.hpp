#pragma once

#include "pair.hpp"
#include "string.hpp"
#include "rb_vect.hpp"

#include <iostream>
#include <cstring>


namespace NDict
{
    class TDict
    {
        rb::rb_tree<NPair::TPair> Tree;
        public:
        void parse_comand(NString::TString &cmd)
        {
            NString::TString word;
            NString::TString path;
            NPair::TPair Data;
            bool res;
            switch(cmd[0])
            {
                case '+':
                std::cin >> Data.Str >> Data.Num;
                Data.Str.lower();

                Tree.Search(Data,res);
                if(res == false)
                {
                    Tree.insert_data(Data);
                    std::cout << "OK" << std::endl;
                }   
                else
                    std::cout << "Exist" << std::endl;
                break;
                case '-':
                std::cin >> Data.Str;
                Data.Str.lower();
                Tree.Search(Data,res);
                if(res == true)
                {
                    Tree.Delete(Data);
                    std::cout << "OK" << std::endl;
                }   
                else
                    std::cout << "NoSuchWord" << std::endl;
                
                break;
                case '!':
                std::cin >> word >> path;
                word.lower();
                if(word == "load")
                {
                    if(Tree.load(path.str))
                        std::cout << "OK" <<std::endl;
                    else
                        std::cout << "ERROR: can't open file" <<std::endl;
                }
                else
                {
                    if(Tree.save(path.str))
                        std::cout << "OK" <<std::endl;
                    else
                        std::cout << "ERROR: can't open file" <<std::endl;
                }
                break;
                default:
                Data.Str = cmd;
                Data.Str.lower();
                rb::rb_tree_elem<NPair::TPair> *elem = Tree.Search(Data,res);
                
                
                if(res)
                {
                    std::cout<< "OK: " << elem->Key.Num << std::endl;
                }
                else
                    std::cout << "NoSuchWord" << std::endl;
                

                break;

            }
            
        }

    };
}

