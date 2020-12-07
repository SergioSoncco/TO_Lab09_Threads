#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <atomic>
#include <random>
#include <thread>
#include "llist.cpp"

single_llist sl;
std::atomic_flag lock = ATOMIC_FLAG_INIT;

void adderThreadExecuting(single_llist sl);
void deleteThreadExecuting(single_llist sl);
void readThreadExecuting(single_llist sl);
void modifThreadExecuting(single_llist sl);


int main(){

  /*std::thread adderThread(adderThreadExecuting,sl);
  std::thread deleteThread(deleteThreadExecuting,sl);
  std::thread readThread(readThreadExecuting,sl);
  std::thread modifThread(modifThreadExecuting,sl);
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
    uniform_int_distribution<> distribucion(0, 10);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    std::cout << "Insertando: "<< num << '\n';
    sl.insert_begin(num);
    lock.clear(std::memory_order_release);
}

void deleteThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 10);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    int pos = sl.search_val(num);
    if(pos!=-1){
     std::cout<<"Eliminando: "<<num<<"\n";
     sl.delete_pos(pos);
    }
    else{
     std::cout<<"No se elmino: "<<num<<"\n";
    }
    lock.clear(std::memory_order_release);
}

void readThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 10);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    sl.search(num)? std::cout<<"Buscado: "<<num<< '\n' : std::cout<<"No encontrado: "<<num<< '\n';
    lock.clear(std::memory_order_release);
}

void modifThreadExecuting(single_llist sl){
    std::random_device device;
    mt19937 generador(device());
    uniform_int_distribution<> distribucion(0, 10);
    int num = distribucion(generador);
    while (lock.test_and_set(std::memory_order_acquire))
        ;
    sl.update(num+10,sl.search(num))? std::cout << "Modificando: "<<num<<" a "<<num+10<< '\n' : std::cout << "No encontrado"<< '\n';
    lock.clear(std::memory_order_release);
}
