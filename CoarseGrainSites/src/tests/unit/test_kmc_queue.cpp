#include <cassert>
#include <iostream>

#include "../../../include/kmccoarsegrain/kmc_queue.hpp"

using namespace std;
using namespace kmccoarsegrain;

int main(void) {

  cout << "Testing: KMC_Queue constructor" << endl;
  { KMC_Queue kmc_queue; }

  cout << "Testing: KMC_Queue size" << endl;
  {
    KMC_Queue kmc_queue;
    assert(kmc_queue.size()==0);
  }

  cout << "Testing: KMC_Queue add" << endl;
  {
    pair<int,double> pr1{ 1, 23.1};
    pair<int,double> pr2{ 3, 10.3};
    pair<int,double> pr3{ 2, 0.13};

    KMC_Queue kmc_queue;
    kmc_queue.add(pr1);
    assert(kmc_queue.size()==1);
    kmc_queue.add(pr2);
    assert(kmc_queue.size()==2);
    kmc_queue.add(pr3);
    assert(kmc_queue.size()==3);
  }

  cout << "Testing: KMC_Queue pop_current" << endl;
  {

    pair<int,double> pr1{ 1, 23.1};
    pair<int,double> pr2{ 3, 10.3};
    pair<int,double> pr3{ 2, 0.13};

    KMC_Queue kmc_queue;
    kmc_queue.add(pr1);
    kmc_queue.add(pr2);
    kmc_queue.add(pr3);

    auto pr = kmc_queue.pop_current();
    assert(pr==pr3);
    pr = kmc_queue.pop_current();
    assert(pr==pr2);
    pr = kmc_queue.pop_current();
    assert(pr==pr1);
    assert(kmc_queue.size()==0);
  }
  return 0;
}
