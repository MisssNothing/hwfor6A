#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
namespace topit {
  template< class T >
  struct Vector {
    Vector();
    Vector(size_t s, const T& val);
    ~Vector();

    Vector(const Vector< T >&);
    Vector< T >& operator=(const Vector< T >&);
    Vector(Vector< T >&&) noexcept;
    Vector< T >& operator=(Vector< T >&&) noexcept;

    void swap(Vector< T >&) noexcept;
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& val);
    void pushFront(const T& val);

    // Классная работа
    // 1. copy/swap
    // 2. Протестировать (!)
    void insert(size_t pos, const T& val);
    void insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e);
    void erase(size_t pos);

    // Домашняя работа
    // 1. Реализовать итераторы для вектора (сами итераторы НЕ тестировать)
    // 2. Придумать по 3 штуки insert/erase (в сумме 6) с итераторами
    struct VectorIterator;
    void insert(VectorIterator pos, const T& val);
    void erase(VectorIterator pos);
    template< class IT >
    void insert(VectorIterator pos, IT begin, IT end);

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

   private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t s);
  };

  template< class T >
  bool operator==(const Vector< T >&, const Vector< T >&) {
    return false;
  }
  template< class T >
  bool operator!=(const Vector< T >&, const Vector< T >&) {
    return false;
  }
}
template< class T >
void topit::Vector< T >::pushFront(const T& val)
{
  Vector< T > result(getSize() + 1);
  result[0] = val;
  for (size_t i = 0; i < getSize(); ++i) {
    result[i + 1] = (*this)[i];
  }
  swap(result);
}

template< class T >
topit::Vector< T >::Vector(Vector&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}
template< class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}
template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template<class T>
topit::Vector< T >& topit::operator=(const Vector<T>& lhs, const Vector<T>& rhs)
{
  Vector< T > cpy(rhs);
  std::swap(data_, cpy.data_);
  std::swap(size_, cpy.size_);
  std::swap(capacity_, cpy.capacity_);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
T& topit::Vector< T >::at(size_t id) {
  return const_cast< T& >(static_cast< const Vector< T >* >(this)->at(id));
}
template< class T >
const T& topit::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}
template< class T >
topit::Vector< T >::Vector(size_t size, const T& val):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = val;
  }
}
template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}
template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}
template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}
template< class T >
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
}
template< class T >
topit::Vector< T >::Vector():
 data_(nullptr),
 size_(0),
 capacity_(0)
{}
template< class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}

template< class T >
T& topit::Vector<T>::operator[](size_t id) noexcept
{
  return data_[id];
}

template< class T >
const T& topit::Vector<T>::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
void topit::Vector<T>::pushBack(const T& val)
{
  if (size_ == capacity_) {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
  data_[size_] = val;
  ++size_;
}
template<class T>
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
  if (lhs.getSize() != rhs.getSize()) {
    return false;
  }
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template<class T>
bool topit::operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
  return !(lhs == rhs);
}

#endif
