#include <iostream>
#include"figure.h"
#include"stack.h"
#include<algorithm>

void menu() {
    std::cout << "Enter 0-4 to:" << std::endl;
    std::cout << "1 - add square to stack" << std::endl;
    std::cout << "2 - delete figure from stack" << std::endl;
    std::cout << "3 - print all coordinates of figures in stack" << std::endl;
    std::cout << "4 - print the number of figures with an area less than..." << std::endl;
    std::cout << "0 - exit" << std::endl;
}

void error() {
    std::cout << "Incorrect value!" << std::endl;
}

int main()
{
    int a, b, choice;
    long double area;
    Stack<Figure<int>> stack;
    Figure<int> sq;
    menu();
    std::cout << "Your choice: ";
    do {
        std::cin >> choice;
        switch(choice) {
        case 1:
            std::cout << "Enter the side of the square: ";
            std::cin >> a;
            sq = Figure<int>(a);
            std::cout << "Insert at the end of the stack [1] or at a specific position [2]? ";
            std::cin >> choice;
            if (choice == 1) {
                stack.Push(sq);
            }
            else if (choice == 2) {
                std::cout << "Enter the position number on the stack ";
                try {
                    std::cin >> b;
                    if (stack.Size() == 0) {
                        b--;
                        if (b<0 || b>stack.Size()) {
                            throw b;
                        }
                    }
                }
                catch (const int a) {
                    std::cout << "There is no such iterator\n";
                    break;
                }
                Stack<Figure<int>>::Forward_iterator it = stack.Begin();
                int i = 1;
                if (i != b) {
                    for (i; i < b; ++i) {
                        ++it;
                    }
                }
                stack.Insert(it, sq);
            }
            else {
                error();
            }
            break;
        case 2: {
            std::cout << "Enter the position number on the stack ";
            std::cin >> b;
            try {
                if (b<0 || b>stack.Size()) {
                    throw b;
                }
            }
            catch (const int a) {
                std::cout << "There is no such iterator\n";
                break;
            }
            Stack<Figure<int>>::Forward_iterator it = stack.Begin();
            for (int i = 1; i < b; ++i) {
                ++it;
            }
            stack.Erase(it);
            break;
        }
        case 3: {
            auto print = [](Figure<int>& elem) {
                std::cout << "("<<elem.a.first << ", " << elem.a.second<<"), ";
                std::cout << "(" << elem.b.first << ", " << elem.b.second << "), ";
                std::cout << "(" << elem.c.first << ", " << elem.c.second << "), ";
                std::cout << "(" << elem.d.first << ", " << elem.d.second << ")"<<std::endl;
            };
            std::for_each(stack.Begin(), stack.End(), print);
            break; 
        }
        case 4:
        {
            std::cout << "Enter area: ";
            std::cin >> area;
            try {
                if (area < 0) {
                    throw area;
                }
            }catch(const long double a){
                std::cout << "You entered negative area\n";
                break;
            }
            long double count = std::count_if(stack.Begin(), stack.End(), [area](Figure<int>& elem) {return area > elem.d.second * elem.d.second; });
            std::cout << "The number of figures with an area less than " << area << " is " << count << std::endl;
            break;
        }
        case 0:
            std::cout << "The program is closed, goodbye!\n";
            return false;
            break;
        default:
            std::cout << "Incorrect values! Try again.\n";
            break;
        }
        std::cout << "What's next?\n";
        std::cout << ">>";
    } while (choice);
    return 0;
}