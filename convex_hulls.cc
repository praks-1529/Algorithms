#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class node {
  public:
    node(ll  a_x, ll a_y) {
      x_ = a_x;
      y_ = a_y;
    }
    bool operator <(const node &rhs) {
      if(this->x_ < rhs.x_) {
        return true;
      } else if(this->x_ == rhs.x_) {
        if(this->y_ < rhs.y_) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
    friend ostream& operator<<(ostream& os, const node& a_node);
    ll x_;
    ll y_;
};

ostream& 
operator<<(ostream& os, const node& a_node)
{
    os << '(' << a_node.x_ << ',' << a_node.y_ << ')';
    return os;
}
#if 0
int
side(node P1, node P2, node P) {
  ll x = (P2.x_*P.y_ - P2.y_*P.x_) - P1.x_*(P.y_ - P2.y_) + P1.y_*(P.x_ - P2.x_); 
}
#endif

int
side(node P1, node P2, node P3) {
  // It is the direction of two vectors P1->P2 and P1->P. The 
  //  For three points (x1,y1) , (x2,y2)  and ,(x3,y3) simply compute the direction of the cross product of the 
  //  two vectors connecting the point (x1,y1)  to (x2, y2) and the point (x1, y1)  to (x3, y3), 
  //  which is given by the expression [(x2-x1)*(y3-y1)] - [(y2-y1)*(x3-x1)]
  ll direction = [(P2.x_ - P1.x_)*(P3.y_ - P1.y_)] - [(P2.y_-P1.y_)*(P3.x_-P1.x_)];
}
void 
swap(vector<node> &a, int i, int j) {
  node temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

int 
partition(vector<node> &arr, int low, int high) {
  node pivot_key = arr[high];
  int partition_index = low;
  for(int i=low; i<=(high-1) ; i++) {
    if(arr[i] < pivot_key) {
      swap(arr, partition_index, i);
      partition_index++;
    }
  }
  swap(arr, partition_index, high);
  return(partition_index);
}

void 
quick_sort_low(vector<node>& arr, int low, int high) {
  if(low>=high) {
    return;
  }
  ll pivot_key = partition(arr, low, high);
  quick_sort_low(arr, low, pivot_key-1);
  quick_sort_low(arr, pivot_key+1, high);
}

void 
quick_sort(vector<node> &arr, int n) {
  quick_sort_low(arr, 0, (n-1));
}

void
upper_hull(list<node> &L, vector<node> &vertices) {
  L.push_back(vertices[0]);
  L.push_back(vertices[1]);
  for(ull i=2; i<vertices.size(); i++) {
    node Pi = vertices[i];
    while(1) {
      if(L.size() == 1) {
        break;
      }
      node V = L.back();
      L.pop_back();
      node U = L.back();
      L.push_back(V);
      if(side(U, V, Pi) < 0) {
        break;
      }
      L.pop_back();
    }
    L.push_back(Pi);
  }
#if 0
  cout << "Upper hull" << endl;
  list<node>::iterator it;
  for(it=L.begin(); it!=L.end();  it++) {
    cout << *it << endl;
  }
#endif
}

void
lower_hull(list<node> &L, vector<node> &vertices) {
  L.push_back(vertices[0]);
  L.push_back(vertices[1]);
  for(ull i=2; i<vertices.size(); i++) {
    node Pi = vertices[i];
    while(1) {
      if(L.size() == 1) {
        break;
      }
      node V = L.back();
      L.pop_back();
      node U = L.back();
      L.push_back(V);
      if(side(U, V, Pi) > 0) {
        break;
      }
      L.pop_back();
    }
    L.push_back(Pi);
  }
#if 0
  cout << "Lower hull" << endl;
  list<node>::iterator it;
  for(it=L.begin(); it!=L.end();  it++) {
    cout << *it << endl;
  }
#endif
}

void
find_convex_hull(vector<node> &vertices) {
  list<node> UH;
  list<node> LH;
  upper_hull(UH, vertices);
  lower_hull(LH, vertices);
  list<node>::iterator it;
  for(it=UH.begin(); it!=UH.end();  it++) {
    cout << *it << endl;
  }
  LH.pop_back();
  list<node>::reverse_iterator rit=LH.rbegin();
  for(rit=LH.rbegin() ; rit!= LH.rend(); ++rit) {
    cout << *rit << endl;
  }
}

int main() {
  ull N;
  vector<node> vertices;
  scanf("%lld", &N);
  ll X,Y;
  while(N--) {
    scanf("%lld", &X);
    scanf("%lld", &Y);
    vertices.push_back(node(X, Y));
  }
  // Sort the vector based on the x co-ordinates
  quick_sort(vertices, vertices.size());
#if 0
  vector<node>::iterator it;
  for(it=vertices.begin();  it!= vertices.end(); it++) {
    cout << *it << endl;
  }
#endif
  find_convex_hull(vertices);
}
