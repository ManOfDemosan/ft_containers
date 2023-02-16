#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"


namespace ft {
	template <typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef	typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef	typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef	typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
			typedef	typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef	typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		private:
			pointer _ptr;

		public:
			random_access_iterator() : _ptr(NULL) {}
			random_access_iterator(const random_access_iterator &other) : _ptr(other._ptr) {}
			template<typename Iter>
			random_access_iterator(const random_access_iterator<Iter> &other) : _ptr(other.base()) {}
			random_access_iterator(pointer ptr) : _ptr(ptr) {}
			virtual ~random_access_iterator() {}

			random_access_iterator &operator=(const random_access_iterator &other) {
				if (this != &other)
					_ptr = other._ptr;
				return *this;
			}

		//operator overloading
		pointer base() const { return _ptr; }
		reference operator*(){ return *_ptr; }
		const reference operator*() const { return *_ptr; }
		random_access_iterator operator+(difference_type n) const { return random_access_iterator(_ptr + n); }
		random_access_iterator operator++(int) { return random_access_iterator(_ptr++); }
		random_access_iterator &operator++() { ++_ptr; return *this; }
		random_access_iterator operator+=(difference_type n) { _ptr += n; return *this; }
		random_access_iterator operator-(difference_type n) const { return random_access_iterator(_ptr - n); }
		random_access_iterator operator--(int) { return random_access_iterator(_ptr--); }
		random_access_iterator &operator--() { --_ptr; return *this; }
		random_access_iterator operator-=(difference_type n) { _ptr -= n; return *this; }
		pointer operator->() const { return _ptr; }
		reference operator[](difference_type n) { return _ptr[n]; }
		const reference operator[](difference_type n) const { return _ptr[n]; }
		
	};
	//operator overloading
	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> &it) { return random_access_iterator<T>(it.base() + n); }
	template <typename T>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() - rhs.base(); }
	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() - rhs.base(); }
	template <typename T>
	bool operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() == rhs.base(); }
	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() == rhs.base(); }
	template <typename T>
	bool operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() != rhs.base(); }
	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() != rhs.base(); }
	template <typename T>
	bool operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() < rhs.base(); }
	template <typename T1, typename T2>
	bool operator<(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() < rhs.base(); }
	template <typename T>
	bool operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() <= rhs.base(); }
	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() <= rhs.base(); }
	template <typename T>
	bool operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() > rhs.base(); }
	template <typename T1, typename T2>
	bool operator>(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() > rhs.base(); }
	template <typename T>
	bool operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() >= rhs.base(); }
	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1> &lhs, const random_access_iterator<T2> &rhs) { return lhs.base() >= rhs.base(); }
}
#endif
