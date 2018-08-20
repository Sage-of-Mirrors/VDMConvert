#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <vector>

template < typename T >
class CArrayT {

	public:

	using TItem = T;
	using TArray = CArrayT<TItem>;

	CArrayT() = default;
	CArrayT(size_t capacity);
	CArrayT(const TItem & item, size_t count);
	CArrayT(const TItem items[], size_t count);
	CArrayT(const TArray & array);
	CArrayT(const TArray & array, size_t start, size_t count);
	CArrayT(const std::initializer_list<TItem> & items);

	TItem & at(size_t index);
	TItem & operator[](size_t index);
	TItem & front();
	TItem & back();
	TItem * data();

	const TItem & at(size_t index) const;
	const TItem & operator[](size_t index) const;
	const TItem & front() const;
	const TItem & back() const;
	const TItem * data() const;

	bool empty() const;
	size_t size() const;
	size_t capacity() const;

	void clear();
	void reserve(size_t needed);
	void resize(size_t count, const TItem & item = TItem());
	void shrink();

	void insert(const TItem & item, size_t index);
	void prepend(const TItem & item);
	void append(const TItem & item);
	bool remove(const TItem & item);
	void erase(size_t start, size_t count = 1);

	bool contains(const TItem & item, size_t * index = nullptr) const;

	TItem * copy() const;

	private:

	std::vector<TItem> mItems;

};

// ------------------------------------------------------------------------- //

template < typename T >
CArrayT<T>::CArrayT(size_t capacity) {
	if (capacity > 0) {
		mItems.reserve(capacity);
	}
}

template < typename T >
CArrayT<T>::CArrayT(const TItem & item, size_t count) :
	mItems(count, item)
{ }

template < typename T >
CArrayT<T>::CArrayT(const TItem items[], size_t count) {
	reserve(count);

	for (size_t i = 0; i < count; ++i) {
		append(items[i]);
	}
}

template < typename T >
CArrayT<T>::CArrayT(const TArray & array) {
	reserve(array.size());

	for (size_t i = 0; i < array.size(); ++i) {
		append(array[i]);
	}
}

template < typename T >
CArrayT<T>::CArrayT(const TArray & array, size_t start, size_t count) {
	reserve(count);

	for (size_t i = 0; i < count; ++i) {
		append(array[start + i]);
	}
}

template < typename T >
CArrayT<T>::CArrayT(const std::initializer_list<TItem> & items) :
	mItems(items)
{ }

template < typename T >
T & CArrayT<T>::at(size_t index) {
	return mItems[index];
}

template < typename T >
T & CArrayT<T>::operator[](size_t index) {
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
T * CArrayT<T>::data() {
	return mItems.data();
}

template < typename T >
const T & CArrayT<T>::at(size_t index) const {
	return mItems[index];
}

template < typename T >
const T & CArrayT<T>::operator[](size_t index) const {
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
const T * CArrayT<T>::data() const {
	return mItems.data();
}

template < typename T >
bool CArrayT<T>::empty() const {
	return mItems.empty();
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
void CArrayT<T>::resize(size_t count, const TItem & item) {
	mItems.resize(count, item);
}

template < typename T >
void CArrayT<T>::shrink() {
	mItems.shrink_to_fit();
}

template < typename T >
void CArrayT<T>::insert(const TItem & item, size_t index) {
	mItems.insert((mItems.begin() + index), item);
}

template < typename T >
void CArrayT<T>::prepend(const TItem & item) {
	insert(item, 0);
}

template < typename T >
void CArrayT<T>::append(const TItem & item) {
	mItems.push_back(item);
}

template < typename T >
bool CArrayT<T>::remove(const TItem & item) {
	for (auto i = mItems.begin(); i != mItems.end(); ++i) {
		if (*i == item) {
			mItems.erase(i);
			return true;
		}
	}

	return false;
}

template < typename T >
void CArrayT<T>::erase(size_t start, size_t count) {
	if (count == 0) {
		return;
	}

	auto first = (mItems.begin() + start);
	auto last = (first + (count - 1));
	mItems.erase(first, last);
}

template < typename T >
bool CArrayT<T>::contains(const TItem & item, size_t * index) const {
	for (auto i = mItems.begin(); i != mItems.end(); ++i) {
		if (*i == item) {
			if (index != nullptr) {
				*index = static_cast<size_t>(std::distance(mItems.begin(), i));
			}

			return true;
		}
	}

	return false;
}

template < typename T >
T * CArrayT<T>::copy() const {
	TItem * items = new TItem[mItems.size()];

	for (size_t i = 0; i < mItems.size(); ++i) {
		items[i] = mItems[i];
	}

	return items;
}