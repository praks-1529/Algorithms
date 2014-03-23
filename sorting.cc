#include<iostream>
using namespace std;
void insertion_sort(int *a, int n);
void selection_sort(int *a, int n);
void bubble_sort(int *a, int n);
void merge_sort(int *arr, int n);
void merge_sort_low(int *arr, int low, int high);
void quick_sort(int *arr, int n);
void quick_sort_low(int *arr, int low, int high);
int partition(int *arr, int low, int high);

void swap(int *a, int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void print_sorted_array(int *a, int N) {
  cout << "Sorted array is" << endl;
  for(int i=0; i<N; i++) {
    cout << a[i] << " " ;
  }
  cout << endl;
}

int main() {
  int N;
  cin >> N;
  int *arr = new int[N];
  for(int i=0; i<N; i++) {
    cin >> arr[i] ;
  }
  quick_sort(arr,N);
  print_sorted_array(arr, N);

}

void insertion_sort(int *a, int n) {
  for(int i=1; i<n; i++) {
    int key = a[i];
    int j;
    for(j=(i-1); ((j>=0)&&(a[j]<key)); j--) {
      a[j+1] = a[j];
    }
    a[j+1] = key;
  }
}

void selection_sort(int *a, int n) {
  for(int i=0; i<(n-1); i++) {
    for(int j=(i+1); j<n ;j++) {
      if(a[i] > a[j]) {
        swap(a, i, j);
      }
    }
  }
}

void bubble_sort(int *a, int n) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<(n-i-1); j++) {
      if(a[j] > a[j+1]) {
        swap(a, j, j+1);
      }
    }
  }
} 

void merge_sort(int *arr, int n) {
  merge_sort_low(arr, 0, n-1);
}

void merge_sort_low(int *arr, int low, int high) {
  int mid;
  if(high==low) {
    return;
  } else {
    mid = (high-low)/2;
    merge_sort_low(arr, low, (low+mid));
    merge_sort_low(arr, low+mid+1, high);
    int *aux = new int[high-low+1];
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

int partition(int *arr, int low, int high) {
  int pivot_key = arr[high];
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

void quick_sort_low(int *arr, int low, int high) {
  if(low>=high) {
    return;
  }
  int pivot_key = partition(arr, low, high);
  quick_sort_low(arr, low, pivot_key-1);
  quick_sort_low(arr, pivot_key+1, high);
}

void quick_sort(int *arr, int n) {
  quick_sort_low(arr, 0, (n-1));
}

