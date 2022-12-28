#ifndef SET_HPP_
#define SET_HPP_

#include <string>
#include <vector>
#include <functional>

struct StringHasher {
  unsigned int operator()(const std::string &key) const {
    unsigned int hash = 0;
    for (int i = 0; i < key.length(); ++i) {
      hash = hash * 137 + key[i];
    }
    return hash;
  }
};

template <class T, class H=std::hash<T>> class Set {
public:
  Set(int initSize, const H &hasher);
  ~Set() = default;
  Set &operator=(const Set &) = delete;

  T get(const T &key) const;
  bool add(const T &key, const T &value);
  bool remove(const T &key);

private:
  bool _has(const T &key) const;
  enum struct State { Empty, Key, Deleted };
  struct HashTableCell {
    T key;
    T data;
    State state;
    unsigned int hash;
    HashTableCell() : key(""), data(""), state(State::Empty), hash(0) {}
    HashTableCell(const T &key, const T &data, State state, unsigned int hash)
        : key(key), data(data), state(state), hash(hash) {}
  };
  H hasher;
  std::vector<HashTableCell> table;
  unsigned int keysCount;
  void growTable(std::size_t new_size);
};

template <class T, class H> Set<T, H>::Set(int initSize, const H &_hasher)
    : hasher(_hasher), table(initSize), keysCount(0) {}

template <class T, class H> bool Set<T, H>::_has(const T &key) const {
  if (keysCount == 0) {
    return false;
  }
  unsigned int pos = hasher(key) % table.size();

  for (std::size_t prob = 0;; ++prob) {
    pos = (pos + prob) % table.size();
    switch (table[pos].state) {
    case State::Deleted:
      continue;
    case State::Empty:
      return false;
    case State::Key:
      if (table[pos].key == key) {
        return true;
      }
      continue;
    }
  }
  return false;
}

template <class T, class H> T Set<T, H>::get(const T &key) const {
  if (keysCount == 0) {
    return "";
  }
  unsigned int pos = hasher(key) % table.size();

  for (std::size_t prob = 0;; ++prob) {
    pos = (pos + prob) % table.size();
    switch (table[pos].state) {
    case State::Deleted:
      continue;
    case State::Empty:
      return "";
    case State::Key:
      if (table[pos].key == key) {
        return table[pos].data;
      }
      continue;
    }
  }
  return "";
}

template <class T, class H> bool Set<T, H>::add(const T &key, const T &value) {
  if (_has(key)) {
    return false;
  }
  if (keysCount >= table.size() * 3 / 4) {
    growTable(table.size() * 2);
  }
  std::size_t key_hash = hasher(key) % table.size();
  std::size_t pos = key_hash;
  int first_deleted = -1;
  for (std::size_t prob = 0;; ++prob) {
    pos = (pos + prob) % table.size();
    switch (table[pos].state) {
    case State::Deleted:
      if (first_deleted == -1) {
        first_deleted = pos;
      }
      continue;
    case State::Empty:
      if (first_deleted != -1) {
        pos = first_deleted;
      }
      table[pos].key = key;
      table[pos].data = value;
      table[pos].state = State::Key;
      table[pos].hash = key_hash;
      ++keysCount;
      return true;
    case State::Key:
      continue;
    }
  }
  ++keysCount;
  return true;
}

template <class T, class H> bool Set<T, H>::remove(const T &key) {
  if (!_has(key)) {
    return false;
  }
  std::size_t pos = hasher(key) % table.size();
  for (std::size_t prob = 0;; ++prob) {
    pos = (pos + prob) % table.size();
    switch (table[pos].state) {
    case State::Deleted:
      continue;
    case State::Empty:
      return false;
    case State::Key:
      if (table[pos].key != key) {
        continue;
      }
      table[pos].key = "";
      table[pos].data = "";
      table[pos].state = State::Deleted;
      return true;
    }
  }
  return false;
}

template <class T, class H> void Set<T, H>::growTable(std::size_t new_size) {
  std::vector<HashTableCell> buffer(new_size);
  std::size_t new_keysCount = 0;
  for (std::size_t i = 0; i < table.size(); ++i) {
    if (table[i].state == State::Key) {
      ++new_keysCount;
      std::size_t new_pos = hasher(table[i].key) % new_size;
      for (std::size_t prob = 0;; ++prob) {
        new_pos = (new_pos + prob) % new_size;
        if (buffer[new_pos].state == State::Deleted ||
            buffer[new_pos].state == State::Empty) {
          buffer[new_pos].key = table[i].key;
          buffer[new_pos].data = table[i].data;
          buffer[new_pos].state = State::Key;
          break;
        }
      }
    }
  }
  table = buffer;
  keysCount = new_keysCount;
}

#endif // SET_HPP_
