#pragma once
template<typename T>
struct Figure {
	using coords = std::pair<T, T>;
	coords a, b, c, d;
	Figure(T a) {
		get_coords(*this, a);
	}
	
	Figure() {}
	~Figure(){}
};

template<typename T, typename S>
void get_coords(T& elem, S side) {
	elem.a.first = elem.a.second = elem.d.first = elem.b.second = 0;
	elem.b.first = elem.c.first = elem.c.second = elem.d.second = side;
}