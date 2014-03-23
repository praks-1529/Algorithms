#include<iostream>
using namespace std;
#define INFINITY 10000;

int disjkstras(int **graph, int n, int source);
int belmanns(int **graph, int n, int source);
int floyd_warshalls(int **graph, int n);
int get_min_vertex(int *distance, int *visited, int n);

int min(int a, int b) {
  if(a<b) {
    return(a);
  } else {
    return(b);
  }
}

int main() 
{
  int n;
  cin >> n;

  int **a = new int*[n];
  for(int i=0; i<n ; i++) {
   a[i] = new int[n];
  } 
  
  for(int i=0; i<n; i++) {
   for(int j=0; j<n; j++) {
     cin >> a[i][j];
   }
  } 

  disjkstras(a, n, 0);
  belmanns(a, n, 0);
  floyd_warshalls(a,n);

  for(int i=0; i<n ; i++) {
   delete[] a[i];
  } 
  delete[] a;

}

int disjkstras(int **graph, int n, int source) {
  int *min_distance = new int[n]; 
  int *visited = new int[n]; 
  for(int i=0; i<n; i++) {
      min_distance[i] = INFINITY;
      visited[i]=0;
  }
  min_distance[source] = 0;


  for(int i=0; i<n ; i++) {
    int min_vertex = get_min_vertex(min_distance, visited, n);
    for(int j=0; j<n; j++) {
      if(min_distance[j] > (graph[min_vertex][j] + min_distance[min_vertex])) {  
        min_distance[j] = graph[min_vertex][j] + min_distance[min_vertex];
      }
    }
    visited[min_vertex] = 1;
  }

  for(int i=0; i<n; i++) {
      cout << min_distance[i] << " ";
  }

  delete[] min_distance;
  delete[] visited;
}

int belmanns(int **graph, int n, int source) {
  int *min_distance = new int[n]; 
  for(int i=0; i<n; i++) {
      min_distance[i] = INFINITY;
  }
  min_distance[source] = 0;

  for(int k=0; k<n ; k++) {
    for(int i=0; i<n ; i++) {
      for(int j=0; j<n; j++) {
        if(min_distance[j] > (graph[i][j] + min_distance[i])) {  
          min_distance[j] = graph[i][j] + min_distance[i];
        }
      }
    }
  }

  for(int i=0; i<n; i++) {
      cout << min_distance[i] << " ";
  }

  delete[] min_distance;
}

int floyd_warshalls(int **graph, int n) {
  for(int k=0; k<n ; k++) {
    for(int i=0; i<n ; i++) {
      for(int j=0; j<n; j++) {
        graph[i][j] = min(graph[i][j], (graph[i][k]+graph[k][j]));
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cout << graph[i][j] << " ";
    }
    cout << endl;
  }
}


int get_min_vertex(int *distance, int *visited, int n) {
  int ret_val = -1;
  int min = INFINITY;
  for(int i=0; i<n; i++) {
    if((distance[i] < min) && (visited[i] == 0)) {
      min = distance[i];
      ret_val = i;
    }
  }
  return(ret_val);
}
