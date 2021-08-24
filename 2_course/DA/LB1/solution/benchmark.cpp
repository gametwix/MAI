#include <iostream>
#include <algorithm>
#include <chrono>

#include "sort_base.hpp"
#include "base.hpp"
#include "vector.hpp"


using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

/*
using duration_t = std::chrono::milliseconds;
const std::string DURATION_PREFIX = "ms";
*/

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    NVector::TVector<NBase::TBase_elem> input, input_stl;
    NBase::TBase_elem elem;
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    while (std::cin >> elem)
    {
        input.Push_back(elem);
    }
    auto end_ts = std::chrono::system_clock::now();
    std::cout << "Read time: " << std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count() << DURATION_PREFIX << std::endl;
    input_stl = input;

    std::cout << "Count of lines is " << input.Size() << std::endl;

    // Измеряем время работы сортировки подсчётом.
    start_ts = std::chrono::system_clock::now();
    NSort_base::Sort( input );
    end_ts = std::chrono::system_clock::now();

    uint64_t counting_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    // Измеряем время работы stl сортировки.
    start_ts = std::chrono::system_clock::now();
    std::stable_sort(input_stl.Begin(), input_stl.End());
    end_ts = std::chrono::system_clock::now();

    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();
    std::cout << "Counting sort time: " << counting_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
}