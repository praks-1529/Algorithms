/*! ----------------------------------------------------------
 *
 *  \file       memory_manager.cc
 *
 *  \brief
 *
 *
 *  \details
 *      Simulating Best Fit Alogorithm of memory manager
 *
 *  \history
 *      05/29/12 03:00:52 PDT Created By Prakash S
 *
 *  ----------------------------------------------------------*/
#include<iostream>
#include<bitset>
#include<queue>
#include<list>
#include<map>
using namespace std;

class mem_chunk {
  private:
  public:
    mem_chunk(int, int, int);
    ~mem_chunk() {};
    void resize(int, int, int);
    int start_i;
    int end_i;
    int size;
};

mem_chunk::mem_chunk(int start, int end, int mem) :
                     start_i(start),
                     end_i(end),
                     size(mem) 
{
}

class compare {
  private:
  public:
    bool operator() (mem_chunk* &a, mem_chunk* &b) {
      if(a->size > b->size) {
        return(true);
      } else {
        return(false);
      }
    }
};

void
mem_chunk::resize(int start, int end, int mem)
{
  start_i = start;
  end_i = end;
  size = mem;
}

static void 
custom_radix(int a[][4], int N);
static void
swap(int a[][4], int , int);
static int 
process_events(int event_queue[][4], int N, int P, int max_event);
static int 
allocate(int pid, int mem, int N, 
             vector< list<mem_chunk*>* > &mem_per_process,
             priority_queue<mem_chunk*, vector<mem_chunk*>, compare> &free_memory_slots);
static void 
deallocate(int pid, int N,
           list<mem_chunk*>* &process_list, 
           priority_queue<mem_chunk*, vector<mem_chunk*>, compare> &free_memory_slots);
int main() {
  int event_queue[65][4] = {0};
  int temp;
  int N;
  cin >> N;
  int P;
  cin >> P;
  temp = P;
  int index = 0;
  while(temp--) {
    int pid, start, end, mem;
    cin >> pid >> start >> end >> mem;
    /* Allocate event */
    event_queue[index][0] = pid;
    event_queue[index][1] = start;
    event_queue[index][2] = mem;
    event_queue[index++][3] = 1;

    /* Deallocate event */
    event_queue[index][0] = pid;
    event_queue[index][1] = end;
    event_queue[index][2] = mem;
    event_queue[index++][3] = 0;
  }

  int R;
  cin >> R;
  temp = R;
  while(temp--) {
    int pid, start, mem;
    cin >> pid >> start >> mem;
    event_queue[index][0] = pid;
    event_queue[index][1] = start;
    event_queue[index][2] = mem;
    event_queue[index++][3] = 1;
  }
  custom_radix(event_queue, index);
  for(int i=0; i< index; i++) {
    for(int k=0; k<4; k++) {
      cout << event_queue[i][k] << " " ;
    }
    cout << endl;
  }
  cout << process_events(event_queue, N, P, index) << endl;
}

static void 
custom_radix(int a[][4], int N) {
  /*First in-place sort based on process id */
  int k;
  k=0;
  for(int i=0; i<N; i++) {
    for(int j=0; j<(N-i-1); j++) {
      if(a[j][k] > a[j+1][k]) {
        swap(a, j, j+1);
      }
    }
  }  

  /* Then in-place sort based on time */
  k=1;
  for(int i=0; i<N; i++) {
    for(int j=0; j<(N-i-1); j++) {
      if(a[j][k] > a[j+1][k]) {
        swap(a, j, j+1);
      }
    }
  }  
}

void 
swap(int a[][4], int j, int k) {
  int tmp[4];
  tmp[0] = a[j][0];
  tmp[1] = a[j][1];
  tmp[2] = a[j][2];
  tmp[3] = a[j][3];

  a[j][0] = a[k][0];
  a[j][1] = a[k][1];
  a[j][2] = a[k][2];
  a[j][3] = a[k][3];

  a[k][0] = tmp[0];
  a[k][1] = tmp[1];
  a[k][2] = tmp[2];
  a[k][3] = tmp[3];
}

static int 
process_events(int event_queue[][4], int N, int P, int max_event) {
  map<int, int> deleted_process;
  vector< list<mem_chunk*>* > mem_per_process(P);
  priority_queue<mem_chunk*, vector<mem_chunk*>, compare> free_memory_slots;

  for(int i=0; i<=P; i++) {
    mem_per_process[i] = new list<mem_chunk*>;
    deleted_process[i] = 0; 
  }
 
  mem_chunk *tmp_chunk = new mem_chunk(0, N-1, N);
  free_memory_slots.push(tmp_chunk);

  for(int i=0; i<max_event; i++) {
    if((deleted_process[event_queue[i][0]] != 1)) {
      if(event_queue[i][3] == 1) {
        /*Allocation event*/
        int status = allocate(event_queue[i][0] /*pid*/,
            event_queue[i][2] /*mem*/,
            N,
            mem_per_process,
            free_memory_slots);
        if(status == 0) {
          /* Unsuccsfull allocation */
          deleted_process[event_queue[i][0]] = 1;
        } 
      } else {
        /*De-allocation event*/
        deallocate(event_queue[i][0], N, mem_per_process[event_queue[i][0]], free_memory_slots);
      }
    }
  }

  int count;
  for(int i=0; i<=P; i++) {
    if(deleted_process[i] == 1) {
      count++;
    } 
  }
  return(count);
}

static int 
allocate(int pid, int mem, int N, 
             vector< list<mem_chunk*>* > &mem_per_process,
             priority_queue<mem_chunk*, vector<mem_chunk*>, compare> &free_memory_slots) {
  list<mem_chunk*> tmp_list;
  bool slot_found = false;
  if(free_memory_slots.empty()) {
    /* ran out of memory */
    deallocate(pid, N, mem_per_process[pid], free_memory_slots);
    return(0);
  }
  do
  {
    mem_chunk *tmp_chunk = free_memory_slots.top();
    free_memory_slots.pop();
    if(tmp_chunk->size >= mem) {
      /* Slot found */
      slot_found = true;
      mem_chunk* alloted_chunk = new mem_chunk(tmp_chunk->start_i, tmp_chunk->start_i+mem-1, mem);
      if(tmp_chunk->size == mem) {
      } else {
        mem_chunk* free_chunk = new mem_chunk(tmp_chunk->start_i+mem, tmp_chunk->end_i, tmp_chunk->size-mem);
        free_memory_slots.push(free_chunk);
      }
      mem_per_process[pid]->push_back(alloted_chunk);
      delete tmp_chunk;
    } else {
      tmp_list.push_back(tmp_chunk);
    }
  } while(!slot_found);

  if(!slot_found) {
    /* Time to terminate the process */
    deallocate(pid, N, mem_per_process[pid], free_memory_slots);
    return(0);
  } else {
    list<mem_chunk*>::iterator it;
    for(it=tmp_list.begin(); it!=tmp_list.end(); it++) {
      free_memory_slots.push(*it);
    }
    return(1);
  }
}

static void 
deallocate(int pid, int N,
           list<mem_chunk*>* &process_list, 
           priority_queue<mem_chunk*, vector<mem_chunk*>, compare> &free_memory_slots) {
  bitset<1000> mem_map;
  mem_map.set();
  mem_chunk *tmp_chunk;
  while(!free_memory_slots.empty()) {
    tmp_chunk=free_memory_slots.top();
    free_memory_slots.pop();
    for(int i= tmp_chunk->start_i; i<= tmp_chunk->end_i; i++) {
      mem_map[i] = 0;
    }
    delete tmp_chunk;
  }

  /*Deallocate the memory of process pid*/
  list<mem_chunk*>::iterator it;
  for(it=process_list->begin(); it!=process_list->end(); it++) {
    tmp_chunk=*it;
    for(int i= tmp_chunk->start_i; i<= tmp_chunk->end_i; i++) {
      mem_map[i] = 0;
    }
    delete tmp_chunk;
  }

  /*Create a new heap */
  bool free;
  int block_index = 0;
  if(mem_map[0] == 1) {
    free = false;
  } else {
    free = true;
  }
  for(int i=0; i<N-1; i++) {
    if(mem_map[i] != mem_map[i+1]) {
      /*Change of block*/
      if(mem_map[i] == 0) {
        /* End of free block */
        tmp_chunk = new mem_chunk(block_index, i, i-block_index+1);
        free_memory_slots.push(tmp_chunk);
        block_index = i+1;
      }
    }
  }
}
