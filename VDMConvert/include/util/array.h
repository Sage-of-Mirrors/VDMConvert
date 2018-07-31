#pragma once

#include <cstddef>
#include <cassert>
#include <vector>

template < typename T >
class CArrayT {

	public:

	CArrayT(size_t capacity = 100);

	T & at(size_t index);
	T & operator[] (size_t index);
	T & front();
	T & back();

	const T & at(size_t index) const;
	const T & operator[] (size_t index) const;
	const T & front() const;
	const T & back() const;

	size_t size() const;
	size_t capacity() const;

	void clear();
	void reserve(size_t needed);
	void insert(T item, size_t index);
	void prepend(T item);
	void append(T item);
	bool remove(T item);
	void remove(size_t index);
	bool contains(T item) const;

	private:

	std::vector<T> mItems;

};

// ------------------------------------------------------------------------- //

template < typename T >
CArrayT<T>::CArrayT(size_t capacity) {
	if (capacity > 0) {
		mItems.reserve(capacity);
	}
}

template < typename T >
T & CArrayT<T>::at(size_t index) {
	assert(index < mItems.size());
	return mItems[index];
}

template < typename T >
T & CArrayT<T>::operator[] (size_t index) {
	assert(index < mItems.size());
	return mItems[index];
}

template < typename T >
T & CArrayT<T>::front() {
	return mItems.front();
}

template < typename T >
T & CArrayT<T>::back() {
	return mItems.back();
}

template < typename T >
const T & CArrayT<T>::at(size_t index) const {
	assert(index < mItems.size());
	return mItems[index];
}

template < typename T >
const T & CArrayT<T>::operator[] (size_t index) const {
	assert(index < mItems.size());
	return mItems[index];
}

template < typename T >
const T & CArrayT<T>::front() const {
	return mItems.front();
}

template < typename T >
const T & CArrayT<T>::back() const {
	return mItems.back();
}

template < typename T >
size_t CArrayT<T>::size() const {
	return mItems.size();
}

template < typename T >
size_t CArrayT<T>::capacity() const {
	return mItems.capacity();
}

template < typename T >
void CArrayT<T>::clear() {
	mItems.clear();
}

template < typename T >
void CArrayT<T>::reserve(size_t needed) {
	mItems.reserve(needed);
}

template < typename T >
void CArrayT<T>::insert(T item, size_t index) {
	assert(index <= mItems.size());
	mItems.insert((mItems.begin() + index), item);
}

template < typename T >
void CArrayT<T>::prepend(T item) {
	insert(item, 0);
}

template < typename T >
void CArrayT<T>::append(T item) {
	mItems.push_back(item);
}

template < typename T >
bool CArrayT<T>::remove(T item) {
	for (auto i = mItems.begin(); i != mItems.end(); ++i) {
		if (*i == item) {
			mItems.erase(i);
			return true;
		}
	}

	return false;
}

template < typename T >
void CArrayT<T>::remove(size_t index) {
	assert(index < mItems.size());
	mItems.erase(mItems.begin() + index);
}

template < typename T >
bool CArrayT<T>::contains(T item) const {
	for (auto i = mItems.begin(); i != mItems.end(); ++i) {
		if (*i == item) {
			return true;
		}
	}

	return false;
}
