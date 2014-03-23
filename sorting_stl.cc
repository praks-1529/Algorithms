#include<iostream>
#include<vector>
using namespace std;

template <typename T>
void insertion_sort(vector<T> &a, int n);
template <typename T>
void selection_sort(vector<T> &a, int n);
template <typename T>
void bubble_sort(vector<T> &a, int n);
template <typename T>
void merge_sort(vector<T> &arr, int n);
template <typename T>
void merge_sort_low(vector<T> &arr, int low, int high);
template <typename T>
void quick_sort(vector<T> &arr, int n);
template <typename T>
void quick_sort_low(vector<T> &arr, int low, int high);
template <typename T>
int partition(vector<T> &arr, int low, int high);

template <typename T>
void swap(vector<T> &a, int i, int j) {
  T temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

template <typename T>
void print_sorted_array(vector<T> &a, int N) {
  cout << "Sorted array is" << endl;
  for(int i=0; i<N; i++) {
    cout << a[i] << " " ;
  }
  cout << endl;
}

int main() {
  int N;
  cin >> N;
  vector<int> arr(N);
  for(int i=0; i<N; i++) {
    cin >> arr[i] ;
  }
  quick_sort(arr,N);
  print_sorted_array(arr, N);
}

template <typename T>
void insertion_sort(vector<T> &a, int n) {
  for(int i=1; i<n; i++) {
    T key = a[i];
    int j;
    for(j=(i-1); ((j>=0)&&(a[j]<key)); j--) {
      a[j+1] = a[j];
    }
    a[j+1] = key;
  }
}

template <typename T>
void selection_sort(vector<T> &a, int n) {
  for(int i=0; i<(n-1); i++) {
    for(int j=(i+1); j<n ;j++) {
      if(a[i] > a[j]) {
        swap<T>(a, i, j);
      }
    }
  }
}

template <typename T>
void bubble_sort(vector<T> &a, int n) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<(n-i-1); j++) {
      if(a[j] > a[j+1]) {
        swap<T>(a, j, j+1);
      }
    }
  }
} 

template <typename T>
void merge_sort(vector<T> &arr, int n) {
  merge_sort_low<T>(arr, 0, n-1);
}

template <typename T>
void merge_sort_low(vector<T> &arr, int low, int high) {
  int mid;
  if(high==low) {
    return;
  } else {
    mid = (high-low)/2;
    merge_sort_low<T>(arr, low, (low+mid));
    merge_sort_low<T>(arr, low+mid+1, high);
    vector<T> aux(arr.size());
    int i,j,k;
    for(i=0, j=low, k=low+mid+1; ((j<=low+mid) && (k<=high)) ; i++) {
      if(arr[j] < arr[k]) {
        aux[i] = arr[j++];
      } else {
        aux[i] = arr[k++];
      }
    }
    while(j<=low+mid) {
      aux[i++] = arr[j++];
    }

    while(k<=high) {
      aux[i++] = arr[k++];
    }

    for(i=low, j=0; i<=high; i++, j++) {
      arr[i] = aux[j];
    }

    delete [] aux;
  }
}

template <typename T>
int partition(vector<T> &arr, int low, int high) {
  T pivot_key = arr[high];
  int partition_index = low;
  for(int i=low; i<=(high-1) ; i++) {
    if(arr[i] < pivot_key) {
      swap(arr, partition_index, i);
      partition_index++;
    }
  }
  swap<T>(arr, partition_index, high);
  return(partition_index);
}

template <typename T>
void quick_sort_low(vector<T> &arr, int low, int high) {
  if(low>=high) {
    return;
  }
  int pivot_key = partition(arr, low, high);
  quick_sort_low<T>(arr, low, pivot_key-1);
  quick_sort_low<T>(arr, pivot_key+1, high);
}

template <typename T>
void quick_sort(vector<T> &arr, int n) {
  quick_sort_low<T>(arr, 0, (n-1));
}
