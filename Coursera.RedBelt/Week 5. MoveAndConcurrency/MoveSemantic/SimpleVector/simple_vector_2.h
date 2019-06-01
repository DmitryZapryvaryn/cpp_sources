#include <cstdint>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() : data(nullptr), size_(0), capacity_(0) {}
  explicit SimpleVector(size_t size);
  SimpleVector(const SimpleVector&) = delete;
  SimpleVector(SimpleVector&&);
  ~SimpleVector();


  void operator=(const SimpleVector&) = delete;
  void operator=(SimpleVector&&);
  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);
  void PushBack(T&& value);

private:
	T* data;
	size_t size_, capacity_;
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) :
	data(new T[size]),
	size_(size),
	capacity_(size) {}

template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector&& other) : data(other.data), capacity_(other.capacity_), size_(other.size_) {
	other.data = nullptr;
	other.capacity_ = other.size_ = 0;
}

template<typename T>
SimpleVector<T>::~SimpleVector()
{
	delete[] data;
}

template<typename T>
void SimpleVector<T>::operator=(SimpleVector&& other) {
	delete[] data;
	data = other.data;
	capacity_ = other.capacity_;
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
void SimpleVector<T>::PushBack(const T& value)
{
	if (size_ == capacity_) {
		size_t new_capacity = capacity_ == 0 ? 4 : capacity_ * 2;

		T* tmp = new T[new_capacity];
		std::move(begin(), end(), tmp);

		delete[] data;

		data = tmp;
		capacity_ = new_capacity;
	}

	data[size_++] = value;
}

template<typename T>
void SimpleVector<T>::PushBack(T&& value)
{
	if (size_ == capacity_) {
		size_t new_capacity = capacity_ == 0 ? 4 : capacity_ * 2;

		T* tmp = new T[new_capacity];
		std::move(begin(), end(), tmp);

		delete[] data;

		data = tmp;
		capacity_ = new_capacity;
	}

	data[size_++] = move(value);
}
