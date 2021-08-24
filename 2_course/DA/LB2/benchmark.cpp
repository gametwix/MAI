#include <iostream>
#include <map>
#include <chrono>

#include "rb_vect.hpp"
#include "pair.hpp"
#include "string.hpp"

using duration_t = std::chrono::microseconds;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::map<char, uint32_t> rb_tree;
    rb::rb_tree<NPair::TPair> my_rb_tree;
    char action;
    char key;
    long long value;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t rb_ts = 0, my_rb_ts = 0;
    for(int i = 0;i<170;++i) {
        std::cin >> action;
        if( action == '+' ) {
            std::cin >> key >> value;
                start = std::chrono::system_clock::now();
                rb_tree.insert( {key, value} );
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
                NPair::TPair p = *(new NPair::TPair(*(new NString::TString(&key)),value));
                bool res;
                
                start = std::chrono::system_clock::now();
                my_rb_tree.Search(p,res);
                if(res == false)
                {
                my_rb_tree.insert_data(p);
                }
                end = std::chrono::system_clock::now();
                my_rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
    std::cout << "std::map ms=" << rb_ts << "\nmy_rb ms=" << my_rb_ts << std::endl;
    return 0;
}
