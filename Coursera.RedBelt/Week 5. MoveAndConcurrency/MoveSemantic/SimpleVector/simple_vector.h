#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(size_t size);
  SimpleVector(const SimpleVector<T>& other);
  ~SimpleVector();

  void operator=(const SimpleVector& other);
  T& operator[](size_t index);

  T* begin();
  T* end();

  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
	T* data;
	size_t size_, capacity_;
};

template<typename T>
SimpleVector<T>::SimpleVector() : data(nullptr), size_(0), capacity_(0) {}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) :
	data(new T[size]), 
	size_(size), 
	capacity_(size) {}

template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T> & other) :
	data(new T[other.capacity_]), 
	size_(other.size_), 
	capacity_(other.capacity_) {

	std::copy(other.begin(), other.end(), begin());
}

template<typename T>
SimpleVector<T>::~SimpleVector()
{
	delete[] data;
}

template<typename T>
void SimpleVector<T>::operator=(const SimpleVector<T>& other) {
	if (other.size_ <= capacity_) {
		std::copy(other.begin(), other.end(), begin());
		size_ = other.size_;
	}
	else {
		// copy-and-swap idiom
		// Так мы достигаем двух целей:
		//  - избегаем дублирования кода в конструкторе копирования
		//    и операторе присваивания
		//  - обеспечиваем согласованное поведение конструктора копирования
		//    и оператора присваивания
		SimpleVector tmp(other);
		std::swap(data, tmp.data);
		std::swap(size_, tmp.size_);
		std::swap(capacity_, tmp.capacity_);
	}
}

template<typename T>
T & SimpleVector<T>::operator[](size_t index)
{
	return data[index];
}

template<typename T>
T * SimpleVector<T>::begin()
{
	return data;
}

template<typename T>
T * SimpleVector<T>::end()
{
	return data + size_;
}

template<typename T>
const T * SimpleVector<T>::begin() const
{
	return data;
}

template<typename T>
const T * SimpleVector<T>::end() const
{
	return data + size_;
}

template<typename T>
size_t SimpleVector<T>::Size() const
{
	return size_;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const
{
	return capacity_;
}

template<typename T>
void SimpleVector<T>::PushBack(const T & value)
{
	if (size_ == capacity_) {
		size_t new_capacity = capacity_ == 0 ? 4 : capacity_ * 2;

		T* tmp = new T[new_capacity];
		std::copy(begin(), end(), tmp);

		delete[] data;

		data = tmp;
		capacity_ = new_capacity;
	}

	data[size_++] = value;
}
