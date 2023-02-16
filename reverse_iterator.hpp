#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef				Iterator													iterator_type;
			typedef	typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef	typename	ft::iterator_traits<Iterator>::value_type			value_type;
			typedef	typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef	typename	ft::iterator_traits<Iterator>::pointer				pointer;
			typedef	typename	ft::iterator_traits<Iterator>::reference			reference;

		private:
			iterator_type	__it;

		public:
		//생성부  생성자, 복사생성자, 소멸자, 대입연산자 iterator를 받아와서 구현하기에 template 사용
			reverse_iterator() : __it() {}
			explicit reverse_iterator(iterator_type it) : __it(it) {}
			template <class Iter> 
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : __it(rev_it.base()) {} 
			virtual ~reverse_iterator() {}

			template <class Iter> 
			reverse_iterator &operator=(const reverse_iterator<Iter>& rev_it) {
				__it = rev_it.base();
				return *this;
			}
		//comparison operators
		iterator_type base() const { return __it; }
		reference operator*() const {
			iterator_type tmp = __it;
			return *--tmp;
		}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(__it - n); }
		reverse_iterator operator++(int) { return reverse_iterator(__it--); }
		reverse_iterator &operator++() { --__it; return *this; }
		reverse_iterator operator+=(difference_type n) { __it -= n; return *this; }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(__it + n); }
		reverse_iterator operator--(int) { return reverse_iterator(__it++); }
		reverse_iterator &operator--() { ++__it; return *this; }
		reverse_iterator operator-=(difference_type n) { __it += n; return *this; }
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return *(*this + n); }
		const reference operator[](difference_type n) { return *(*this + n); }
	};
	//comparison operators
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <typename iter1, typename iter2>
	bool operator==(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <typename iter1, typename iter2>
	bool operator!=(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <typename iter1, typename iter2>
	bool operator<(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <typename iter1, typename iter2>
	bool operator<=(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <typename iter1, typename iter2>
	bool operator>(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <typename iter1, typename iter2>
	bool operator>=(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return rhs.base() - lhs.base();
	}
	template <typename iter1, typename iter2>
	typename reverse_iterator<iter1>::difference_type operator-(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) {
		return rhs.base() - lhs.base();
	}

}
#endif
