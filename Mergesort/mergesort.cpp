#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<chrono>
#include<thread>
using namespace std;

// constants
int const WIDHT=120, HEIGHT=25, SIZE=WIDHT, TIME=30;

// drawing part
void Draw(int ARR[], int size) {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
  for (auto y=0; y < HEIGHT; y++) {
    for (auto x=0; x < WIDHT; x++) {
      if (ARR[x] < y)
        cout << "#";
      else
        cout << " ";
    }
    cout << endl;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
}

// mergesort brain
void merge (int ARR[], int const left, int const right, int const mid) {
  auto const sARRl=mid-left+1, sARRr=right-mid;
  auto *ARRl = new int[sARRl], *ARRr = new int[sARRr];
  for (auto i=0; i < sARRl; i++)
    ARRl[i] = ARR[left+i]; 
  for (auto i=0; i < sARRr; i++)
    ARRr[i] = ARR[mid+i+1];
  auto indexL=0, indexR=0, indexM = left;
  while (indexL < sARRl && indexR < sARRr) {
    if (ARRl[indexL] >= ARRr[indexR]) {
      ARR[indexM++] = ARRl[indexL++];;
    } else {
      ARR[indexM++] = ARRr[indexR++];;
    }
    Draw(ARR, SIZE);
  }
  while (indexL < sARRl) {
    ARR[indexM++] = ARRl[indexL++];
  }
  while (indexR < sARRr) {
    ARR[indexM++] = ARRr[indexR++];
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
  int *array = genArray(SIZE);
  print(array, SIZE);
  Draw(array, SIZE);
  int n;
  cin >> n;
  mergesort(array, 0, SIZE-1);
}