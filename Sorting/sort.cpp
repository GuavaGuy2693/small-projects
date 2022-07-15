#include<iostream>
#include<stdlib.h>
#include<chrono>
#include<thread>
using namespace std;

// constants
int const WIDTH=120, HEIGHT=28, SIZE=WIDTH, TIME=30;

// drawing part
void Draw(int ARR[], int size) {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
  for (auto y=0; y < HEIGHT; y++) {
    for (auto x=WIDTH-1; x >= 0; x--) {
      if (ARR[x] < y)
        cout << "#";
      else
        cout << " ";
    }
    cout << endl;
  }
  // std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
}

// swap function
void swap (int *x, int *y) {
  int t = *x;
  *x = *y;
  *y = t;
}

// merge sort
void merge (int ARR[], int const left, int const right, int const mid) {
  auto const sARRl=mid-left+1, sARRr=right-mid;
  auto *ARRl = new int[sARRl], *ARRr = new int[sARRr];
  for (auto i=0; i < sARRl; i++)
    ARRl[i] = ARR[left+i]; 
  for (auto i=0; i < sARRr; i++)
    ARRr[i] = ARR[mid+i+1];
  auto indexL=0, indexR=0, indexM = left;
  while (indexL < sARRl && indexR < sARRr) {
    if (ARRl[indexL] <= ARRr[indexR]) {
      ARR[indexM++] = ARRl[indexL++];;
    } else {
      ARR[indexM++] = ARRr[indexR++];;
    }
    // draw call
    Draw(ARR, SIZE);
  }
  while (indexL < sARRl) {
    ARR[indexM++] = ARRl[indexL++];
    Draw(ARR, SIZE);
  }
  while (indexR < sARRr) {
    ARR[indexM++] = ARRr[indexR++];
    Draw(ARR, SIZE);
  }
  delete[] ARRl, ARRr;
}

void mergesort (int ARR[], int const start, int const end) {
  if (start >= end)
    return;
  auto mid=start+(end-start)/2;
  mergesort(ARR, start, mid);
  mergesort(ARR, mid+1, end);
  merge(ARR, start, end, mid);
}

// selection sort
void selectionsort (int ARR[], int size) {
  for (auto i=0; i < size; i++) {
    for (auto j=i; j < size; j++) {
      if (ARR[j] < ARR[i])
        swap(ARR[i], ARR[j]);
      Draw(ARR, SIZE);
    }
  }
}

// quick sort
int partition (int ARR[], int start, int end) {
  int pivot = ARR[end];
  int i = (start - 1);;
  for (auto j=start; j <= end; j++) {
    if (ARR[j] < pivot) {
      i++;
      swap(ARR[i], ARR[j]);
    }
    Draw(ARR, SIZE);
  }
  swap(ARR[++i], ARR[end]);
  Draw(ARR, SIZE);
  return i;
}

void quicksort (int ARR[], int start, int end) {
  if (start < end) {
    int pi = partition(ARR, start, end);
    quicksort(ARR, start, pi-1);
    quicksort(ARR, pi+1 , end);
  }
}

// random array generator
int *genArray (int size) {
  int *ARR = new int[size];
  for (auto i=0; i < size; i++){
    ARR[i] = rand()%HEIGHT;
  }
  return ARR;
}

void print (int ARR[], int size) {
  for (auto i=0; i < size; i++){
    cout << ARR[i] << " ";
  }
  cout << endl;
}

// driver code
int main () {
  int *array = new int[SIZE];
  array = genArray(SIZE);
  while (true) {
    array = genArray (SIZE);
    Draw (array, SIZE);
    selectionsort (array, SIZE);
    array = genArray (SIZE);
    mergesort (array, 0, SIZE-1);
    array = genArray (SIZE);
    quicksort (array, 0, SIZE);
  }
}