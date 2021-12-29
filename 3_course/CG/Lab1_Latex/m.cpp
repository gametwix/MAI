void get_xy(double phi,double a, double &x,double &y){
    x = a*cos(phi)*(1 - cos(phi));
    y = a*sin(phi)*(1 - cos(phi));
}

void get_points(double a, double n, std::vector<std::pair<double,double>> &points){
    points.clear();
    for(int t = 0; t < 2*PI; t += 2*PI/n){
        double x,y;
        get_xy(t,a,x,y);
        points.push_back({x,y});
    }
}