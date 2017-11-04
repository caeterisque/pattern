#pragma once
#include "stdafx.h"
#include <new> 
#include <iostream>
#include <stack>

using namespace std;

const int default_size = 100;

template <typename T>
class KVector {
public:
	

	class Iterator {
	public:
		Iterator(T* arr, size_t size, int cur) : _arr(arr), _size_deq(size), _cur(cur) {}
		Iterator(const Iterator& iter) : _arr(iter._arr), _size_deq(iter._size_deq), _cur(iter._cur) {}

		Iterator& operator++() {
			_cur = (_cur + 1) % (_size_deq + 1);

			//std::cout << _cur << std::endl;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp(*this);
			++*this;
			return temp;
		}

		bool operator ==(const Iterator& it) {
			return (_arr == it._arr && _cur == it._cur);
		}

		bool operator !=(const Iterator& it) {
			return (_arr != it._arr || _cur != it._cur);
		}

		T& operator * () {
			return _arr[_cur];
		}
	private:
		T* _arr;
		size_t _size_deq;
		int _cur;
	};



	KVector() : fCapacity(default_size), ptr(new T[fCapacity]) {}

	KVector(const KVector<T> &a) {
		fSize = a.fSize;
		ptr = new T[a.fCapacity];
		for (int i = 0; i < fSize; i++)
			ptr[i] = a.ptr[i];
	}

	KVector(int _fCapacity, int _fSize) {
		fSize = _fSize;
		fCapacity = _fCapacity;
		ptr = new T[_fCapacity];
		for (int i = 0; i<fCapacity; i++)
			ptr[i] = T();
	}

	KVector(int _fCapacity, int _fSize, T* b) {
		fSize = _fSize;
		fCapacity = _fCapacity;
		ptr = new T[_fCapacity];
		int i = 0;
		for (i; i < fSize; i++)
			ptr[i] = b[i];
		for (i; i < fCapacity; i++)
			ptr[i] = T();

	}

	~KVector<T>() {
		delete[]ptr;
	}

	KVector(initializer_list<T> _Ilist) {
		ptr = static_cast<T*>(operator new[]((_Ilist.size() << 1) * sizeof(T)));
		fSize = 0;

		for (auto x : _Ilist) {
			PushBack(x);
		}
	}


	template <typename ... Args>
	void emplace_back(Args&&... val) {
		fCapacity += sizeof ... (Args);
		new (ptr + fSize) T(forward<Args>(val)...);
		fSize += sizeof ... (Args);
	}

	void PushBack(T const& e) {
		ptr[fSize] = e;
		++fSize;

	}

	void PopBack() {
		ptr[fSize - 1].~T();
		fSize--;
	}

	void print(std::ostream& output) const;
	void set(int, T);
	T get(int)const;
	T* getPtr();
	int getSize()const;
	T & operator [](int);
	KVector<T> & operator = (KVector<T> &);

	T operator *=(KVector <T>  const& v1);
	T operator *(KVector <T>  const& v1);

	double Size()const;
	void Swap(KVector <T>  &a);

	KVector & operator +=(KVector <T>   &v);
	KVector & operator -=(KVector <T>  & v);
	KVector<T> operator + (KVector<T> & a);
	KVector operator -(KVector <T>   & v);

	bool operator == (KVector <T> const &v1);
	bool operator != (KVector <T>  const &v1);
	bool operator < (KVector <T>  const &v1);
	bool operator <= (KVector <T>  const &v1);
	bool operator > (KVector <T>  const &v1);
	bool operator >= (KVector <T> const &v1);


	Iterator begin() const {
		return Iterator(ptr, fSize, 0);
	}

	Iterator end() const {
		return Iterator(ptr, fSize, fSize);
	}
	//template <typename T>
	friend ostream& operator<<(ostream & os, const KVector<T>&a) {
		a.print(os);
		return os;
	}

	/*template <typename T>
	friend istream& operator >> (istream & input, KVector <T>&a) {
	cout << "Enter coordinates:" << endl;
	for (int i = 0; i < a.fSize; i++) {
	cout << "coordinate " << i + 1 << " = ";
	input >> a.ptr[i];
	}
	return input;
	}*/
private:
	int fCapacity;
	int fSize;
	T *ptr;
};

template <typename T>
void KVector<T>::set(int i, T data) {
	if (i < 0 || i >(fSize - 1))
		return;
	ptr[i] = data;
}

template <typename T>

T KVector<T>::get(int i)const {
	//if (i<0||i>(fSize-1))
	//return -1;
	return ptr[i];
}

template <typename T>
T* KVector<T>::getPtr() {
	T *arr = new T[fSize];
	for (int i = 0; i < fSize; i++)
		arr[i] = ptr[i];
	return arr;
}

template <typename T>
int KVector<T>::getSize()const {
	return fSize;
}

template<typename T>
inline T & KVector<T>::operator[](int i) {
	try {
		if (i < 0) throw i;
		return coordinates[i];
	}
	catch (int) {
		cout << "error" << endl;
	}
}

template <typename T>
void KVector<T>::print(std::ostream& os) const {
	cout << "(";
	int i;
	for (i = 0; i < fSize - 1; i++)
		os << ptr[i] << ", ";
	os << ptr[i];
	cout << ")";
}
///////////////////////////////////////////////////////////////////
template <typename T>
double KVector <T>::Size()const {
	T sqrtx = 0;
	for (int i = 0; i<fSize; i++)
		sqrtx += ptr[i] * ptr[i];
	double sizex = sqrt((double)sqrtx);
	return sizex;
}

template <typename T>
void KVector<T>::Swap(KVector<T> &a) {
	swap(a.fSize, fSize);
	swap(a.fCapacity, fCapacity);
	swap(a.ptr, ptr);
}



template <typename T>
T KVector <T> :: operator *=(KVector<T> const& v1) {//скалярное произведение
	T t = 0;
	for (int i = 0; i<fSize; i++)
		t += ptr[i] * v1.ptr[i];
	return t;
}
template <typename T>
T KVector<T>:: operator *(KVector<T> const& v1) {
	KVector<T> t(*this);
	return (t *= v1);
}


template <typename T>
KVector<T> &KVector<T> :: operator +=(KVector<T> & v) {
	for (int i = 0; i<v.fCapacity; i++)
		ptr[i] = ptr[i] + v.ptr[i];
	return *this;
}

template <typename T>
KVector<T> &KVector<T> :: operator -=(KVector<T> & v) {
	for (int i = 0; i<v.fSize; i++)
		ptr[i] = ptr[i] - v.ptr[i];
	return *this;
}

template <typename T>
KVector<T> KVector<T> :: operator + (KVector<T>  & v) {
	KVector<T> t(*this);
	t += v;
	t.fCapacity = max(this->fCapacity, v.fCapacity);//2*fSize;
	return t;
}

template <typename T>
KVector<T> KVector<T> :: operator -(KVector<T> & v) {
	KVector<T> t(*this);
	t -= v;
	t.fCapacity = max(this->fCapacity, v.fCapacity);//2*fSize;
	return t;
}

template <typename T>
KVector<T>  &KVector<T> :: operator = (KVector<T> & a) {
	if (this != &a) {
		fSize = a.fSize;
		delete[] ptr;
		fCapacity = a.fCapacity;
		ptr = new T[a.fCapacity];
		for (int i = 0; i<a.fCapacity; i++)
			ptr[i] = a.ptr[i];
		return *this;
	}
	else {
		return a;
	}
}

template <typename T>
bool KVector<T>:: operator == (KVector<T> const &v1) {//Векторы называются равными, если они сонаправлены и их длины равны.
	return (*this).Size() == v1.Size();
}

template <typename T>
bool KVector<T>:: operator != (KVector<T> const &v1) {
	return (*this).Size() != v1.Size();
}

template <typename T>
bool KVector<T>:: operator < (KVector const &v1) {
	return (*this).Size()<v1.Size();
}

template <typename T>
bool KVector<T>:: operator <= (KVector <T> const &v1) {
	return (*this).Size() <= v1.Size();
}

template <typename T>
bool KVector<T>:: operator > (KVector<T> const &v1) {
	return (*this).Size()>v1.Size();
}

template <typename T>
bool KVector<T>:: operator >= (KVector<T> const &v1) {
	return (*this).Size() >= v1.Size();
}
