#include <cmath>
#include <utility>

template <class T>
struct Square{
    using vertex_t = std::pair<T,T>;
    vertex_t dot[4];

    int square()
    {
        int size = dot[1].first;
        return size*size;
    }

    Square()
    {
        for(int i=0;i<4;++i)
        {
            dot[i].first = 0;
            dot[i].second = 0;
        }
    }

    friend std::ostream& operator<< (std::ostream &out, const Square &sq)
    {
        for(int i = 0;i < 4;++i)
        {
            out << "(" << sq.dot[i].first << "," << sq.dot[i].second << ") ";
        }
        return out;
    }

    friend std::istream& operator>>(std::istream &in, Square &sq)
    {
        int size;
        in >> size;
        sq.dot[1].first = size;
        sq.dot[2].first = size;
        sq.dot[2].second = size;
        sq.dot[3].second = size;
        return in;
    }

    void operator=(const Square &second)
    {
        for(int i=0;i<4;++i)
        {
            dot[i]=second.dot[i];
        }
    }


};


