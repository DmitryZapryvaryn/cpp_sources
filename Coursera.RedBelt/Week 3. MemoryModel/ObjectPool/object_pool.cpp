#include "../../test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate() {
		if (!freeObjects.empty()) {
			T* lastFreeObject = freeObjects.front();
			allocatedObjects.insert(lastFreeObject);
			freeObjects.pop();

			return lastFreeObject;
		}

		T* newObject = new T;
		allocatedObjects.insert(newObject);
		return newObject;
	}

	T* TryAllocate() {
		if (freeObjects.empty()) {
			return nullptr;
		}

		return Allocate();
	}

	void Deallocate(T* object) {
		auto foundObject = allocatedObjects.find(object);

		if (foundObject == allocatedObjects.end()) {
			throw invalid_argument("Object not found!");
		}

		freeObjects.push(object);
		allocatedObjects.erase(object);
	}

	~ObjectPool() {
		for (auto object : allocatedObjects) {
			delete object;
		}

		while (!freeObjects.empty()) {
			delete freeObjects.front();
			freeObjects.pop();
		}
	}

private:
	set<T*> allocatedObjects;
	queue<T*> freeObjects;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
