#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP
#include "iterator.hpp"
#include <iterator>
namespace ft {
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	//is_integral
	struct true_integral {
		static const bool value = true;
	};

	struct false_integral {
		static const bool value = false;
	};

	template <typename T>
	struct is_integral: public false_integral {};

	template <>
	struct is_integral<bool>: public true_integral {};

	template <>
	struct is_integral<char>: public true_integral {};

	template <>
	struct is_integral<unsigned char>: public true_integral {};

	template <>
	struct is_integral<wchar_t>: public true_integral {};

	template <>
	struct is_integral<short>: public true_integral {};

	template <>
	struct is_integral<unsigned short>: public true_integral {};

	template <>
	struct is_integral<int>: public true_integral {};

	template <>
	struct is_integral<unsigned int>: public true_integral {};

	template <>
	struct is_integral<long>: public true_integral {};

	template <>
	struct is_integral<unsigned long>: public true_integral {};

	template <>
	struct is_integral<long long>: public true_integral {};

	template <>
	struct is_integral<unsigned long long>: public true_integral {};

// distance
	template <typename InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
		typename ft::iterator_traits<InputIt>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}
	// lexicographical compare 
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1,*first2))
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}
	// Pair =======================================================================

	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair() : first(), second() {}
		
		template<class U, class V>
		pair(const pair<U,V>& p) : first(p.first), second(p.second) {}

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator=(const pair& other) {
			if (this != &other) {
				this->first = other.first;
				this->second = other.second;
			}
			return *this;
		}
	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) { return (pair<T1,T2>(x,y)); }

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs < lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs < rhs); }
// Compare object =============================================================

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T>
	struct less : public binary_function<T,T,bool> {
		bool operator()(const T& x, const T& y) const {
			return x < y;
		}
	};

// equal
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		while (first1!=last1) {
			if (!pred(*first1,*first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}


} // namespace ft

#endif 
