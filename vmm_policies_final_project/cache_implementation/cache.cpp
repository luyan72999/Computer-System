#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;


// Abstract class
class Cache {
public:
    int max_size;
    int hit = 0;
    int attemps = 0;

    // Pure virtual function
    virtual void insert(int to_insert) = 0;
    virtual void look_up(int to_search) = 0;

    float calculate_hit_rate() {
      float hit_rate = static_cast<float>(hit) / attemps;
      return hit_rate;
    }

    void change_max_size(int new_size) {
      max_size = new_size;
    }
};

class Cache_Random: public Cache {
  public:
    vector <int>* cache;

    Cache_Random(int size) {
      max_size = size;
      cache = new vector<int>();
      srand(time(NULL));
    }
    // destructor
    ~Cache_Random() {
      delete cache;
    }
    void insert(int to_insert) override {
      if(cache->size() < max_size) {
        cache->push_back(to_insert);
        return;
      } else {
      // cache is full, pick a random one to replace
        int random = random_generator(0, max_size-1);
        (*cache)[random] = to_insert;
        return;
      }
    }

    void look_up(int to_search) override {
      attemps ++;
      // if found, cache hit ++
      for (int i = 0; i < cache->size(); i++) {
        if ((*cache)[i] == to_search) {
          hit ++;
          return;
        }
      }
      // if not found, insert the value into cache 
      insert(to_search);
      hit --;
      attemps --;
      look_up(to_search);
    }

    int random_generator(uint32_t start, uint32_t end) {
      int span = end - start;
      int random = rand() % span + start;
      return random;
    }

    void clear_cache() {
      cache->clear();
      hit = 0;
      attemps = 0;
    }
};

class Cache_Fifo: public Cache {
  public:
    vector <int>* cache;

    Cache_Fifo(int size) {
      max_size = size;
      cache = new vector<int>();
    }
    // destructor
    ~Cache_Fifo() {
      delete cache;
    }
    void insert(int to_insert) override {
      if(cache->size() < max_size) {
        cache->push_back(to_insert);
        return;
      } else {
      //cache is full, kick the first element out
        cache->erase(cache->begin());
        cache->push_back(to_insert);
        return;
      }
    }

    void look_up(int to_search) override {
      attemps ++;
      // if found, cache hit ++
      for (int i = 0; i < cache->size(); i++) {
        if ((*cache)[i] == to_search) {
          hit ++;
          return;
        }
      }
      // if not found, insert the value into cache 
      insert(to_search);
      hit --;
      attemps --;
      look_up(to_search);
    }

    void clear_cache() {
      cache->clear();
      hit = 0;
      attemps = 0;
    }
};

class Entry_LFU {
  public:
    int value;
    int frequency = 0;

    Entry_LFU(int value): value(value) {}
};

class Cache_LFU: public Cache {
  public:
    vector <Entry_LFU>* cache;

    Cache_LFU(int size) {
      max_size = size;
      cache = new vector<Entry_LFU>();
    }
    // destructor
    ~Cache_LFU() {
      delete cache;
    }
    
    void insert(int to_insert) override {
      // create Entry_LFU obj
      Entry_LFU temp(to_insert);

      if(cache->size() < max_size) {
        cache->push_back(temp);
        return;
      } else {
        // cache is full, kick out the least frequently used entry
        sort(cache->begin(), cache->end(), [](const Entry_LFU &item1, const Entry_LFU &item2) {
            return item1.frequency < item2.frequency;
        });
        // the first one will be the least frequently used after sorting
        cache->erase(cache->begin());
        cache->push_back(temp);
        return;
      }
    }

    void look_up(int to_search) override {
      attemps ++;
      // if found, cache hit ++
      for (int i = 0; i < cache->size(); i++) {
        if ((*cache)[i].value == to_search) {
          (*cache)[i].frequency ++;
          hit ++;
          return;
        }
      }
      // if not found, insert the value into cache 
      insert(to_search);
      hit --;
      attemps --;
      look_up(to_search);
    }

    void clear_cache() {
      cache->clear();
      hit = 0;
      attemps = 0;
    }
};

class Cache_LRU: public Cache {
  public:
    vector <int>* cache;

    Cache_LRU(int size) {
      max_size = size;
      cache = new vector<int>();
    }
    // destructor
    ~Cache_LRU() {
      delete cache;
    }
    void insert(int to_insert) override {
      if(cache->size() < max_size) {
        cache->push_back(to_insert);
        return;
      } else {
      //cache is full, kick the first element out
        cache->erase(cache->begin());
        cache->push_back(to_insert);
        return;
      }
    }

    void look_up(int to_search) override {
      attemps ++;
      // if found, cache hit ++
      for (int i = 0; i < cache->size(); i++) {
        if ((*cache)[i] == to_search) {

          int temp = (*cache)[i];
          int j = i + 1;
          for (; j < cache->size(); j++) {
            (*cache)[j-1] = (*cache)[j];
          }
          // put temp into the last position of the cache
          (*cache)[j-1] = temp;
          hit ++;
          return;
        }
      }
      // if not found, insert the value into cache 
      insert(to_search);
      hit --;
      attemps --;
      look_up(to_search);
    }

    void clear_cache() {
      cache->clear();
      hit = 0;
      attemps = 0;
    }
};

int main() {
  Cache_Random cr = Cache_Random(10);
  Cache_Fifo cf = Cache_Fifo(10);
  Cache_LFU clfu = Cache_LFU(10);
  Cache_LRU clru = Cache_LRU(10);
  
  // test cases 
  // workload 1: starting from 1,2,3...10,11,1,2,3..10,11,1,2......
  vector<int> test1 = {1,2,3,4,5,6,7,8,9,10,11};
  cout << "test size 10" << endl;
  // Random
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      cr.look_up(test1[j]);
    }
  }
  cout << "Random" << endl;
  cout << cr.calculate_hit_rate() << endl;

  // FIFO
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      cf.look_up(test1[j]);
    }
  }
  cout << "FIFO" << endl;
  cout << cf.calculate_hit_rate() << endl;

  // LFU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      clfu.look_up(test1[j]);
    }
  }
  cout << "LFU" << endl;
  cout << clfu.calculate_hit_rate() << endl;

  // LRU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      clru.look_up(test1[j]);
    }
  }
  cout << "LRU" << endl;
  cout << clru.calculate_hit_rate() << endl;


  // test 2  
  cr.clear_cache();
  cf.clear_cache();
  clfu.clear_cache();
  clru.clear_cache();
  cr.change_max_size(11);
  cf.change_max_size(11);
  clfu.change_max_size(11);
  clru.change_max_size(11);
  
  // test cases 
  // workload 1: starting from 1,2,3...10,11,1,2,3..10,11,1,2......
  cout << "test size 11" << endl;
  //Random
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      cr.look_up(test1[j]);
    }
  }
  cout << "Random" << endl;
  cout << cr.calculate_hit_rate() << endl;

  // FIFO
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      cf.look_up(test1[j]);
    }
  }
  cout << "FIFO" << endl;
  cout << cf.calculate_hit_rate() << endl;

  //LFU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      clfu.look_up(test1[j]);
    }
  }
  cout << "LFU" << endl;
  cout << clfu.calculate_hit_rate() << endl;

  // LRU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      clru.look_up(test1[j]);
    }
  }
  cout << "LRU" << endl;
  cout << clru.calculate_hit_rate() << endl;

  // test 3 
  cr.clear_cache();
  cf.clear_cache();
  clfu.clear_cache();
  clru.clear_cache();
  cr.change_max_size(5);
  cf.change_max_size(5);
  clfu.change_max_size(5);
  clru.change_max_size(5);
  
  // test cases 
  // workload 1: starting from 1,2,3...10,11,1,2,3..10,11,1,2......
  cout << "test size 5" << endl;
  //Random
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      cr.look_up(test1[j]);
    }
  }
  cout << "Random" << endl;
  cout << cr.calculate_hit_rate() << endl;

  // FIFO
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      cf.look_up(test1[j]);
    }
  }
  cout << "FIFO" << endl;
  cout << cf.calculate_hit_rate() << endl;

  //LFU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      clfu.look_up(test1[j]);
    }
  }
  cout << "LFU" << endl;
  cout << clfu.calculate_hit_rate() << endl;

  // LRU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test1.size(); j++) {
      clru.look_up(test1[j]);
    }
  }
  cout << "LRU" << endl;
  cout << clru.calculate_hit_rate() << endl;



  // test 4

  cr.clear_cache();
  cf.clear_cache();
  clfu.clear_cache();
  clru.clear_cache();
  cr.change_max_size(10);
  cf.change_max_size(10);
  clfu.change_max_size(10);
  clru.change_max_size(10);

    // workload 1: starting from 1,2,3...10,11,1,2,3..10,11,1,2......
  cout << "test medium locality" << endl;

  vector<int> test4 = {1,2,3,4,5,6,7,8,9,10,16,2,6,1,3,9,16,10,2,9,3,2,1,8,6,2,3,5,10,11,1,2,4,5,11}; 
  //Random
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test4.size(); j++) {
      cr.look_up(test4[j]);
    }
  }
  cout << "Random" << endl;
  cout << cr.calculate_hit_rate() << endl;

  // FIFO
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test4.size(); j++) {
      cf.look_up(test4[j]);
    }
  }
  cout << "FIFO" << endl;
  cout << cf.calculate_hit_rate() << endl;

  //LFU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test4.size(); j++) {
      clfu.look_up(test4[j]);
    }
  }
  cout << "LFU" << endl;
  cout << clfu.calculate_hit_rate() << endl;

  // LRU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test4.size(); j++) {
      clru.look_up(test4[j]);
    }
  }
  cout << "LRU" << endl;
  cout << clru.calculate_hit_rate() << endl;

  // test 4

  cr.clear_cache();
  cf.clear_cache();
  clfu.clear_cache();
  clru.clear_cache();

  cout << "test high locality" << endl;

  vector<int> test5 = {1,2,3,4,5,6,7,8,9,10,16,2,16,7,9,9,7,10,2,9,3,2,3,2,9,2,3,5,10,11,1,2,4,5,11}; 
  //Random
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test5.size(); j++) {
      cr.look_up(test5[j]);
    }
  }
  cout << "Random" << endl;
  cout << cr.calculate_hit_rate() << endl;

  // FIFO
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test5.size(); j++) {
      cf.look_up(test5[j]);
    }
  }
  cout << "FIFO" << endl;
  cout << cf.calculate_hit_rate() << endl;

  //LFU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test5.size(); j++) {
      clfu.look_up(test5[j]);
    }
  }
  cout << "LFU" << endl;
  cout << clfu.calculate_hit_rate() << endl;

  // LRU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test5.size(); j++) {
      clru.look_up(test5[j]);
    }
  }
  cout << "LRU" << endl;
  cout << clru.calculate_hit_rate() << endl;

  // test 6
  cr.clear_cache();
  cf.clear_cache();
  clfu.clear_cache();
  clru.clear_cache();

  cout << "test low locality" << endl;

  vector<int> test6 = {1,2,3,4,5,6,7,8,9,10,16,20,11,6,1,2,18,17,3,9,10,2,3,20,19,15,3,5,10,11,7,2,4,5,8}; 
  //Random
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test6.size(); j++) {
      cr.look_up(test6[j]);
    }
  }
  cout << "Random" << endl;
  cout << cr.calculate_hit_rate() << endl;

  // FIFO
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test6.size(); j++) {
      cf.look_up(test6[j]);
    }
  }
  cout << "FIFO" << endl;
  cout << cf.calculate_hit_rate() << endl;

  //LFU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test6.size(); j++) {
      clfu.look_up(test6[j]);
    }
  }
  cout << "LFU" << endl;
  cout << clfu.calculate_hit_rate() << endl;

  // LRU
  for (int i = 0; i < 100; i ++) {
    for (int j = 0; j < test6.size(); j++) {
      clru.look_up(test6[j]);
    }
  }
  cout << "LRU" << endl;
  cout << clru.calculate_hit_rate() << endl;
}
  




