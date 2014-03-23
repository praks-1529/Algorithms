#define PI 3.14159265359
#define sq(a) ((a)*(a))

class coord_point {
  public:
    coord_point() : x_(-101), y_(-101) { }
    coord_point(double  a_x, double a_y) {
      x_ = a_x;
      y_ = a_y;
    }
    double x_;
    double y_;
};

/* Distance between two points */
double
my_distance(coord_point &a, coord_point &b) {
  return sqrt((double)sq(a.x_ - b.x_) + sq(a.y_ - b.y_));
}

/* Angle between two sides of the triangle. a1 and a2 are adjacent sides, where as
 * opp is the opposite side of the angle of the triangle */
double my_angle(double &a1, double &a2, double &opp) {
  return acos((sq(a1) + sq(a2) - sq(opp))/(2*a1*a2));
}

/* Given three points find all three sides */
vector<double> 
get_sides(vector<coord_point> &ip) {
  vector<double> x;
  x.pb(my_distance(ip[0], ip[1]));
  x.pb(my_distance(ip[1], ip[2]));
  x.pb(my_distance(ip[0], ip[2]));
  sort(x.begin(), x.end());
  return x;
}

/* Given all three angles of triangle */
vector<double> 
get_angle(vector<coord_point> &ip) {
  vector<double> x;
  double a = my_distance(ip[0], ip[1]);
  double b = my_distance(ip[0], ip[2]);
  double c = my_distance(ip[1], ip[2]);
  x.pb(my_angle(a,b,c));
  x.pb(my_angle(b,c,a));
  x.pb(my_angle(c,a,b));
  sort(x.begin(), x.end());
  return x;
}

/* Find if two triangle is similar */
bool
is_similar_triangles(vector<double> &fa, vector<double> &sa, 
                     vector<double> &fs, vector<double> &ss) {
  for(int i=0; i<3; i++) {
    long a = (fa[i]*ERROR);
    long b = (sa[i]*ERROR);
    if(a != b) {
      return false;
    }
  }
  double x,y, a, b;
  long m, n;
  x = fs[0]; y = fs[1]; m = (ERROR*(x/y));
  a = ss[0]; b = ss[1]; n = (ERROR*(a/b));

  if(m != n) {
    return false;
  }
  x = fs[1]; y = fs[2]; m = (ERROR*(x/y));
  a = ss[1]; b = ss[2]; n = (ERROR*(a/b));
  if(m != n) {
    return false;
  }
  x = fs[0]; y = fs[2]; m = (ERROR*(x/y));
  a = ss[0]; b = ss[2]; n = (ERROR*(a/b));
  if(m != n) {
    return false;
  }
  return true;
}

/* given center of circle and another point find the quadrant */
int
quadrant(coord_point &center, coord_point &point) {
  if(point.y_ >= center.y_) {
    /* 1st or 2nd */
    if(point.x_ >= center.x_) {
      return 1;
    } else {
      return 2;
    }
  } else {
    /* 3rd or 4th */
    if(point.x_ >= center.x_) {
      return 4;
    } else {
      return 3;
    }
  }
}

double
calculate_angle(coord_point &ref_point, coord_point &point, coord_point &center) {
  // Equation of vector from (x1, y1) to (x2, y2)  is (x2-x1)i + (y2 - y1)j
  // Vector A = a1i + a2j => Vector from center and ref_point
  double a1 = ref_point.x_ - center.x_;
  double a2 = ref_point.y_ - center.y_;

  //Vector B = b1i + b2j => From center to point
  double b1 = point.x_ - center.x_;
  double b2 = point.y_ - center.y_;

  // Now from dot notation A.B = |A|*|B|*cos(w)
  double x = (a1*b1 + a2*b2) / (sqrt( sq(a1) + sq(a2)) * sqrt(sq(b1) + sq(b2)));
  double rad = acos(x);
  if((quadrant(center, point) == 1) || (quadrant(center, point)) == 2) {
    return rad;
  } else {
    return 2*PI - rad;
  }
}

/* Area of triangle */
double
traingle_area(const coord_point &a, const coord_point &b, const coord_point &c) {
  double area = ( (a.x_*(b.y_ - c.y_)) + (b.x_*(c.y_ - a.y_)) + (c.x_*(a.y_ - b.y_)) )/2.0;
  if(area < 0) {
    area *= -1;
  }
  return area;
}

/* Checks if three points are collinear */
bool 
are_points_colliniear( coord_point &a, coord_point &b , coord_point &c) {
  /* If slopes are equal then they are colliniear or else not */
  if(((b.y_-a.y_)/(b.x_-a.x_)) == ((c.y_-b.y_)/(c.x_-b.x_))) {
    return true;
  } else {
    return false;
  }
}

/* Gets the slope of the two line */
double 
get_slope(coord_point &a, coord_point &b) {
  return ((b.y_ - a.y_)/(b.x_ -a.x_));
}

void
get_circumcenter( coord_point &a, coord_point &b , coord_point &c, coord_point &circum) {
  
  circum.x_ = circum.y_ = INF;
  /* Calculate midpoints */
  double n1, n2, m1, m2;
  m1 = (a.x_ + b.x_)/2;
  n1 = (a.y_ + b.y_)/2;
  m2 = (b.x_ + c.x_)/2;
  n2 = (b.y_ + c.y_)/2;
  

  /* Some special cases */
  bool got_from_ab=false;
  if((get_slope(a, b) == 0) || (get_slope(b, c) == 0)) {
    if((get_slope(a, b) == 0)) {
      circum.x_ = m1;
      got_from_ab=true;
    } else {
      circum.x_ = m2;
    }
  } 
  if((get_slope(a, b) == INF) || (get_slope(b, c) == INF)) {
    if((get_slope(a, b) == INF)) {
      circum.y_ = n1;
      got_from_ab=true;
    } else {
      circum.y_ = n2;
    }
  }
  
  if(circum.x_ == INF && circum.y_ == INF) {
    double s1, s2;
    /* We don't have both x and y */
    s1 = -1/get_slope(a, b);
    s2 = -1/get_slope(b, c);
    circum.x_ = (s1*m1 - s2*m2 + n2 - n1)/(s1 - s2);
    circum.y_ = s2*(circum.x_) - s2*m2 + n2;
  } else if(circum.x_ != INF && circum.y_ != INF) {
    /* We have both x and y */
    return;
  } else if(circum.x_ != INF) {
    double s;
    /* We have x, and need to find y */
    if(got_from_ab) {
       s         = -1/get_slope(b, c);
       circum.y_ = s*(circum.x_ - m2) + n2;
    } else {
      s          = -1/get_slope(a, b);
      circum.y_  = s*(circum.x_ - m1) + n1;
    } 
  } else {
    double s;
    /* We have y, and need to find x */
    if(got_from_ab) {
       s         = -1/get_slope(b, c);
       circum.x_ = (circum.y_ - m2)/s + n2;
    } else {
       s         = -1/get_slope(a, b);
       circum.x_ = (circum.y_ - m1)/s + n1;
    } 
  }
}

int main() {
  vector<coord_point> f;
  vector<coord_point> s;
  int i=6;
  while(i--) {
    double x, y;
    cin >> x >> y;
    if(i>2) {
      f.pb(coord_point(x, y));
    } else {
      s.pb(coord_point(x, y));
    }
  }
  vector<double> fa = get_angle(f);
  vector<double> sa = get_angle(s);
  vector<double> fs = get_sides(f);
  vector<double> ss = get_sides(s);
#if DEBUG
  for(int i=0; i<3; i++) {
    cout << fa[i] << " " ;
  }
  cout << endl;
  for(int i=0; i<3; i++) {
    cout << sa[i] << " " ;
  }
  cout << endl;
  for(int i=0; i<3; i++) {
    cout << fs[i] << " " ;
  }
  cout << endl;
  for(int i=0; i<3; i++) {
    cout << ss[i] << " " ;
  }
#endif
  if(is_similar_triangles(fa, sa, fs, ss)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

