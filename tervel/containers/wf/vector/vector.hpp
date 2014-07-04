#ifndef __TERVEL_CONTAINERS_WF_VECTOR_VECTOR_HPP_
#define __TERVEL_CONTAINERS_WF_VECTOR_VECTOR_HPP_

#include <atomic>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <memory>

#include "tervel/containers/wf/vector_array.h"


template<typename T>
class Vector {
 public:
  typedef std::atomic<T> ArrayElement;
  explicit Vector(const size_t capacity = 64)
    : current_size_(0)
    , internal_array(capacity, c_not_value_) {}

  bool at(size_t idx, const T &value);
  bool cas(size_t idx, const T &expValue, T newValue);

  size_t push_back_only(T value);
  size_t push_back_w_ra(T value);
  // size_t push_back(T value);

  bool pop_back_only(const T &value);
  bool pop_back_w_ra(const T &value);
  // bool pop_back(const T &value);

  // bool insertAt(size_t pos, T value);
  // bool eraseAt(size_t pos, T &value);

  size_t size() {
    return current_size_.load();
  };

  size_t capacity() {
    return internal_array.capacity();
  };

 private:
  size_t size(size_t val) {
    return current_size_.fetch_add(val);
  }

  std::atomic<size_t> current_size_ {0};
  VectorArray<T> internal_array;
  static const c_not_value_(nullptr);
};  // class Vector

#include "vector.imp"

#endif  // __TERVEL_CONTAINERS_WF_VECTOR_VECTOR_HPP_
