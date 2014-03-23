#include<iostream>
#include<math.h>
using namespace std;

void 
reverse_substring(char *a, int N);

int main() {
  int N;
  cin >> N;
  char *arr = new char[N];
  for(int i=0 ; i<N; i++) {
    cin >> arr[i];
  }
  reverse_substring(arr, N);

}

void 
reverse_substring(char *a, int N) {
  int *key_frwd = new int[N];
  int *key_bwd = new int[N];
  int R = 4;
  key_frwd[N-1] = key_frwd[N-2] = 0;
  key_bwd[0] = key_bwd[1] = 0;

  for(int i=0; i<(N-2); i++) {
    if(i==0) {
      key_frwd[i] = ((a[i]-'a')*(int)pow(R,2) + (a[i+1]-'a')*R+(a[i+2]-'a'));
    } else {
      key_frwd[i] = (R*key_frwd[i-1]+(a[i+2] - 'a') - ((a[i-1]-'a')*(int)pow(R,3)));
    }
  }

  for(int i=N-1; i>=2; i--) {
    if(i==(N-1)) {
      key_bwd[i] = ((a[i]-'a')*(int)pow(R,2) + (a[i-1]-'a')*R+(a[i-2]-'a'));
    } else {
      key_bwd[i] = (R*key_bwd[i+1]+(a[i-2]-'a') - ((a[i+1]-'a')*(int)pow(R,3)));
    }
  }

  for(int i=0; i< N; i++) {
    cout << key_frwd[i] << " ";
  }
  cout << endl;
  for(int i=0; i< N; i++) {
    cout << key_bwd[i] << " ";
  }
  cout << endl;

  for(int i=0; i<N-2 ; i++) {
    for(int k=N-1; k>=2; k--) {
      if(key_frwd[i] == key_bwd[k]) {
        /*Check for spurious hit*/
        if(a[i]==a[k] && a[i+1] == a[k-1] && a[i+2] == a[k-2]) {
          cout << a[i] << a[i+1] << a[i+2] << endl;
        }
      }
    }
  }
}
