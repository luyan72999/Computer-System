#include <iostream>
#include <string>
using namespace std;
// This simulator implements first hit policy
class Freenode {
  public:
    int addr;
    int size;
    Freenode* prev;
    Freenode* next;

  Freenode(int addr, int size):addr(addr),size(size) {
    prev = NULL;
    next = NULL;
  }
};

class Freelist {
  public:
    Freenode* head;
    int length;

    Freelist(int base, int size) {
      // param size: the amount of heap memory to manage
        Freenode* node = new Freenode(base, size);
        head = node;
        length = 1;
    }

    Freenode* insert_node(int addr, int size) {
      // create new node and insert it into list by address order
      
      // the freed memory chunk
      Freenode* node = new Freenode(addr, size);
      // check if free list is empty
      if (length == 0) {
        head = node;
      } else if (node->addr < head->addr) {
        // check if this chunk is less than head, if yes update head
        Freenode* temp = head;
        head = node;
        node->next = temp;
        temp->prev = node;
      } else {
        Freenode* curr = head->next;
        if (curr == NULL) {
          //if list only contains a head
          head->next = node;
          node->prev = head;
        } else {
          Freenode* temp; // use temp to record the last node if insert into the end
          while (curr) {
            if(node->addr < curr->addr) {
              node->next = curr;
              node->prev = curr->prev;
              curr->prev->next = node;
              curr->prev = node;
              length += 1;
              return node;
            } else {
              temp = curr;
              curr = curr->next;
            }
          }
          if (node->next == NULL) {
            // check if node is still not inserted, this means it should be inserted in the end
            temp->next = node;
            node->prev = temp;
          }
        } 
      }
      length += 1;
      return node;
    }

    Freenode* search(int size_requested) {
      // search for a fit space to use and return this free node using first fit strategy
      // note the input param size refers to requested size plus header size
      // return null if fail to find a big enough free space
      if (length >= 1) {
        Freenode* curr = head;
        int counter = 0;
        while (curr) {
          counter += 1;
          if (curr->size >= size_requested) {
            cout << to_string(counter) + " elements are searched" << "\n";
            return curr;
          } else {
            curr = curr->next;
          }
        }
        // fail to find 
        return NULL;
      } else {
        // free list is empty
        return NULL;
      }
    }

    // helper function: remove a node from list
    void remove(Freenode* node) {
      // if the node to delete is head
        if (node->prev == NULL) {
          head = head->next;
          delete node;
        } else if (node->next == NULL) {
          // if node to delete is tail
          node->prev->next = NULL;
          delete node;
        } else {
          node->prev->next = node->next;
          node->next->prev = node->prev;
          delete node;
        }
        length -= 1;
        return;
    }

    int split(Freenode* node, int size_requested) {
      // after search, split the node in two: one to return for caller, one remain in free list
      // here actually is modifying the params of this node or remove this node when all size of this node is taken
      // then return the hdptr position
      if (node->size == size_requested) {
        int hdptr = node->addr;
        // delete this free node from list
        remove(node);
        // return header position to caller
        return hdptr;
      } else {
        int hdptr = node->addr;
        // reduce the size of this node
        node->addr += size_requested;
        node->size -= size_requested;
        // return header position to caller
        return hdptr;
      }
    }

    void check_and_merge(Freenode* node) {
      // every time a new chunk of memory is returned, check its prev and next and merge when necessary
      
        if (node->prev) {
          if (node->next) {
            // if node have both prev and next
            Freenode* prev = node->prev; 
            Freenode* next = node->next; 
            // check if merge with prev
            if ((prev->addr + prev->size) == node->addr) {
              prev->size += node->size;
              remove(node);
              // merge with prev occurs, check if prev needs to merge with next
              if ((prev->addr + prev->size) == next->addr) {
                prev->size += next->size;
                remove(next);
              }
            } else {
              // no merge occur with prev, check next
              if ((node->addr + node->size) == next->addr) {
                node->size += next->size;
                remove(next);
              }
            }
          } else {
            // node just have prev
            Freenode* prev = node->prev; 
            if ((prev->addr + prev->size) == node->addr) {
              // merge
              prev->size += node->size;
              remove(node);
            }
          }
        } else if (node->next) {
            // node just have next
            Freenode* next = node->next; 
            if ((node->addr + node->size) == next->addr) {
              // merge
              node->size += next->size;
              remove(next);
            }
        }
        return;     
    }


    ~Freelist() {
      /// travese the list and delete all the nodes
        Freenode* curr = head;
        while (curr) {
          Freenode* next = curr->next;
          delete curr;
          curr = next;
        }
    }


};

class Header {
  public:
    int hdptr;
    int allocptr;
    int size; // size of user requested memory

  Header(int hdptr, int size):hdptr(hdptr),size(size) {
    allocptr = hdptr + sizeof(Header);
  }
};

class Allocator {
  public:
    int base;
    int size;
    Freelist* free_list;

    Allocator(int base, int size): base(base), size(size) {
      free_list = new Freelist(base, size);
    }

    Header* alloc(int size) {
      int size_with_header = size + sizeof(Header);
      Freenode* node = free_list->search(size_with_header);
      if (node) {
        int hdptr = free_list->split(node, size_with_header);
        Header* header = new Header(hdptr, size);
        cout << to_string(header->size) + " bytes are allocated at " + to_string(header->allocptr) << "\n"; 
        return header;
      } else {
        cout << "Failed to allocate requested bytes." << "\n";
        return NULL;
      }
    } 

    void free(Header* h) {
      int size_with_header = h->size + sizeof(Header);
      Freenode* node = free_list->insert_node(h->hdptr, size_with_header);
      free_list->check_and_merge(node);
      cout << "With header: total " + to_string(size_with_header) + " bytes are freed at " + to_string(h->hdptr) << "\n";
      delete h;
      return;
    }

    void print_list(Freelist* list) {
      cout << "Free list info ----------------------------------" << "\n";
      if (list->head) {
        Freenode* iter = list->head;
        while(iter){
          cout << "Free node (address, size):" << " ";
          cout << iter->addr << " ";
          cout << iter->size << "\n";
          iter = iter->next;
        }
        cout << "List length:" << " ";
        cout << list->length << "\n\n";
      } else {
        cout << "Free list is empty" << "\n\n";
      }
    }

    ~Allocator() {
      delete free_list;
    }
};

int main() {
  // the following code creates an allocator, allocate and free some memory to print freelist infos
  Allocator* a = new Allocator(1000, 500);

  Header* h1 = a->alloc(10);
  Header* h2 = a->alloc(10);
  a->print_list(a->free_list);
  Header* h3 = a->alloc(10);
  Header* h4 = a->alloc(10);
  a->print_list(a->free_list);
  Header* h5 = a->alloc(10);
  Header* h6 = a->alloc(10);
  a->print_list(a->free_list);

  a->free(h1);
  Header* h7 = a->alloc(20);
  a->free(h5); 
  a->print_list(a->free_list);
  Header* h8 = a->alloc(5);
  a->free(h7); 
  Header* h9 = a->alloc(100);
  a->free(h3); 
  Header* h10 = a->alloc(20);
  a->print_list(a->free_list);

  a->free(h9); 
  a->alloc(500);
  a->free(h2); 
  a->print_list(a->free_list);
  a->free(h4); 
  a->free(h6); 
  a->print_list(a->free_list);
  a->free(h8); 
  a->free(h10); 
  a->print_list(a->free_list);

  delete a;

  return 0;
}