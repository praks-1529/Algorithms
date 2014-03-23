#include<iostream>
#include<vector>
using namespace std;

class interval {
  public:
    interval() : start_(0), end_(0) { } 
    interval(int a_start, int a_end) : start_(a_start), end_(a_end) { };
    friend ostream& operator<< (ostream &os, const interval &node);
    int start_;
    int end_;
};

ostream& operator<<(ostream &os, const interval &node) {
  os << "(" << node.start_ << "," << node.end_ <<  ")";
  return os;
}

void
find_union(vector<interval> &ip, vector<interval> &op, interval u_i) {
  bool start_found = 0;
  bool end_found = 0;
  interval g_i;
  for(int i=0; i<ip.size(); i++) {
    if(!start_found) {
      if(u_i.start_ >= ip[i].start_ && u_i.start_ <= ip[i].end_) {
        g_i.start_ = ip[i].start_;
        if(u_i.end_ < ip[i].end_) {
          op.push_back(ip[i]);
          continue;
        }
        start_found = 1;
      } else if(u_i.start_ > ip[i].end_ && u_i.start_ < ip[i+1].start_) {
        op.push_back(ip[i]);
        g_i.start_ = u_i.start_;
        start_found = 1;
      } else {
        op.push_back(ip[i]);
      }
    } 
    if(start_found && !end_found) {
      if(u_i.end_ > ip[i].end_) {
        continue;
      } else {
        if(u_i.end_ < ip[i].start_) {
          g_i.end_ = u_i.end_;
          op.push_back(g_i);
          op.push_back(ip[i]);
          end_found = true;
          continue;
        } else {
          g_i.end_ = ip[i].end_;
          op.push_back(g_i);
          end_found = true;
          continue;
        }
      }
    }
    if(end_found) {
      op.push_back(ip[i]);
    }
  }
}

int main() {
  int N;
  cin >> N;
  vector<interval> ip;
  while(N--) {
    int i, j;
    cin >> i >> j;
    ip.push_back(interval(i, j));
  }
  int g_s, g_e;
  cin >> g_s >> g_e;
  vector<interval> op;
  find_union(ip, op, interval(g_s, g_e));
  for(int i=0; i<op.size(); i++) {
    cout << op[i];
  }
}

