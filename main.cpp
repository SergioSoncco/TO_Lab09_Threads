#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <atomic>
#include <random>
#include <thread>
#include "llist.cpp"

int min = 0, max = 1000;
single_llist sl;
std::atomic_flag lock = ATOMIC_FLAG_INIT;

void adderThreadExecuting(single_llist sl);
void deleteThreadExecuting(single_llist sl);
void readThreadExecuting(single_llist sl);
void modifThreadExecuting(single_llist sl);


int main(){

  /*std::thread adderThread(adderThreadExecuting);
  std::thread deleteThread(deleteThreadExecuting);
  std::thread readThread(readThreadExecuting);
  std::thread modifThread(modifThreadExecuting);

  adderThread.join();
  deleteThread.join();
  readThread.join();
  modifThread.join();*/

  std::vector<std::thread> v;
  for (int n = 0; n < 10; ++n) {
     std::cout<<"\n-----------------------------------------------\n";
     v.emplace_back(adderThreadExecuting,sl);
     v.emplace_back(deleteThreadExecuting,sl);
     v.emplace_back(readThreadExecuting,sl);
     v.emplace_back(modifThreadExecuting,sl);
     std::cout<<"\n-----------------------------------------------\n";
  }
  for (auto& t : v) {
     t.join();
  }

  sl.display();
}

void adderThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 1000);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    std::cout << "Output from thread " << "adder "<<num << '\n';
    sl.insert_begin(num);
    lock.clear(std::memory_order_release);
}

void deleteThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 1000);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    std::cout << "Output from thread " << "deleter "<<num << '\n';
    int pos = sl.search(num);
    sl.delete_pos(pos);
    lock.clear(std::memory_order_release);
}
void readThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 1000);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    std::cout << "Output from thread " << "reader "<<num << '\n';
    sl.search(num);
    lock.clear(std::memory_order_release);
}
void modifThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 1000);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    std::cout << "Output from thread " << "modifier " << num << '\n';
    sl.update(num+100,sl.search(num));
    lock.clear(std::memory_order_release);
}
