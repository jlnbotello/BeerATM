#include <string>

typedef std::string String;

const int MAX_SIZE = 10; // set maximum size of the map

template<typename T>
struct KeyValue {
  String key;
  T value;
};

template<typename T>
class Map {
  private:
    KeyValue<T> pairs[MAX_SIZE];
    int size;
    
  public:
    Map() {
      size = 0;
    }
    
    bool insert(String key, T value) {
      if (size < MAX_SIZE) {
        pairs[size].key = key;
        pairs[size].value = value;
        size++;
        return true;
      }
      return false;
    }
    
    T find(String key) {
      for (int i = 0; i < size; i++) {
        if (pairs[i].key == key) {
          return pairs[i].value;
        }
      }
      return T(); // key not found
    }
};
