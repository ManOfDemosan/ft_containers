#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"


namespace ft {

	template <typename T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename allocator_type::difference_type				difference_type;

		private:
			pointer __begin_;
			pointer __end_;
			pointer __end_cap_; 
			allocator_type __a_; //alloc

		public:
			explicit vector(const allocator_type& a = allocator_type())
			: __begin_(NULL)
			, __end_(NULL)
			, __end_cap_(NULL)
			, __a_(a) {}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& a = allocator_type())
			: __begin_(NULL)
			, __end_(NULL)
			, __end_cap_(NULL)
			, __a_(a) {
				__begin_ = __a_.allocate(n);
				__end_ = __begin_;
				__end_cap_ = __end_ + n;
				try{
					for (size_type i = 0; i < n; i++) {
						__a_.construct(__end_, val);
						__end_++;
					}
				}catch (std::exception &e) {
					for(pointer p = __begin_; p != __end_; p++)
						__a_.destroy(p);
					__a_.deallocate(__begin_, n);
					throw;
				}
			}
		
			template <class InputIterator>
			explicit vector(InputIterator first, InputIterator last, 
				const allocator_type& a = allocator_type(),
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
			: __a_(a) {
				size_type n = ft::distance(first, last);
				__begin_ = __a_.allocate(n);
				__end_ = __begin_;
				__end_cap_ = __end_ + n;
				try{
					for (size_type i = 0; i < n; i++) {
						__a_.construct(__end_, *first);
						__end_++;
						first++;
					}
				}catch (std::exception &e) {
					for(pointer p = __begin_; p != __end_; p++)
						__a_.destroy(p);
					__a_.deallocate(__begin_, n);
					throw;
				}
			}

			vector(const vector& x)
			: __a_(x.__a_) {
				size_type n = x.size();
				__begin_ = __a_.allocate(n);
				__end_ = __begin_;
				__end_cap_ = __end_ + n;
				try{
					for (size_type i = 0; i < n; i++) {
						__a_.construct(__end_, x[i]);
						__end_++;
					}
				}catch (std::exception &e) {
					for(pointer p = __begin_; p != __end_; p++)
						__a_.destroy(p);
					__a_.deallocate(__begin_, n);
					throw;
				}
			}

			~vector() {
				for(pointer p = __begin_; p != __end_; p++)
					__a_.destroy(p);
				__a_.deallocate(__begin_, __end_cap_ - __begin_);
			}

			vector& operator=(const vector& x) {
				if (this == &x)
					return *this;
				for(pointer p = __begin_; p != __end_; p++)
					__a_.destroy(p);
				__a_.deallocate(__begin_, __end_cap_ - __begin_);
				size_type n = x.size();
				__begin_ = __a_.allocate(n);
				__end_ = __begin_;
				__end_cap_ = __end_ + n;
				try{
					for (size_type i = 0; i < n; i++) {
						__a_.construct(__end_, x[i]);
						__end_++;
					}
				}catch (std::exception &e) {
					for(pointer p = __begin_; p != __end_; p++)
						__a_.destroy(p);
					__a_.deallocate(__begin_, n);
					throw;
				}
				return *this;
			}
			

			// Iterators
			iterator begin() {return __begin_;}
			const_iterator begin() const {return __begin_;}
			iterator end() {return __end_;}
			const_iterator end() const {return __end_;}
			reverse_iterator rbegin() {return reverse_iterator(__end_);}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(__end_);}
			reverse_iterator rend() {return reverse_iterator(__begin_);}
			const_reverse_iterator rend() const {return const_reverse_iterator(__begin_);}

			// Capacity
			size_type size() const {return __end_ - __begin_;}
			size_type max_size() const {return __a_.max_size();}
			size_type capacity() const {return __end_cap_ - __begin_;}
			bool empty() const {return __begin_ == __end_;}
			void resize(size_type n, value_type val = value_type()) {
				if (n > size()) {
					if (n > capacity())
						reserve(n);
					for (size_type i = size(); i < n; i++) {
						__a_.construct(__end_, val);
						__end_++;
					}
				}
				else if (n < size()) {
					for (size_type i = size(); i > n; i--) {
						__a_.destroy(__end_);
						__end_--;
					}
				}
			}
			void reserve(size_type n) 
			{
				if(n == 0)
					n = 1;
				if (n > capacity()) {
					size_type old_size = size();
					pointer new_begin = __a_.allocate(n);
					pointer new_end = new_begin;
					pointer new_end_cap = new_begin + n;
					try{
						for (size_type i = 0; i < old_size; i++) {
							__a_.construct(new_end, __begin_[i]);
							new_end++;
						}
					}catch (std::exception &e) {
						for(pointer p = new_begin; p != new_end; p++)
							__a_.destroy(p);
						__a_.deallocate(new_begin, n);
						throw;// 예외를 다시 던진다. container에서 예외를 처리할 수 있도록 exception safety를 보장한다.
					}
					for(pointer p = __begin_; p != __end_; p++)
						__a_.destroy(p);
					__a_.deallocate(__begin_, capacity());
					__begin_ = new_begin;
					__end_ = new_end;
					__end_cap_ = new_end_cap;
				} 
			}

			// Element access
			reference operator[](size_type n) {return __begin_[n];}
			const_reference operator[](size_type n) const {return __begin_[n];}
			reference at(size_type n) {
				if (n >= size())
					throw std::out_of_range("vector::at");
				return __begin_[n];
			}
			const_reference at(size_type n) const {
				if (n >= size())
					throw std::out_of_range("vector::at");
				return __begin_[n];
			}
			reference front() {return *__begin_;}
			const_reference front() const {return *__begin_;}
			reference back() {return (*(__end_ - 1));}
			const_reference back() const {return (*(__end_ - 1));}

			// Modifiers
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
				size_type n = ft::distance(first, last);
				if (n > capacity())
					reserve(n);
				for (size_type i = size(); i > n; i--) {
					__a_.destroy(__end_);
					__end_--;
				}
				for (size_type i = 0; i < n; i++) {
					if (i < size())
						__begin_[i] = *first;
					else {
						__a_.construct(__end_, *first);
						__end_++;
					}
					first++;
				}
			}
			void assign(size_type n, const value_type& val) {
				if (n > capacity())
					reserve(n);
				for (size_type i = size(); i > n; i--) {
					__a_.destroy(__end_);
					__end_--;
				}
				for (size_type i = 0; i < n; i++) {
					if (i < size())
						__begin_[i] = val;
					else {
						__a_.construct(__end_, val);
						__end_++;
					}
				}
			}
			iterator insert(iterator position, const value_type& val) {
				size_type n = position - begin();
				if (size() == capacity())
					reserve(size() + 1);
				for (size_type i = size(); i > n; i--) {
					__begin_[i] = __begin_[i - 1];
				}
				__begin_[n] = val;
				__end_++;
				return begin() + n;
			}
			void insert(iterator position, size_type n, const value_type& val) {
				size_type pos = position - begin();
				if (size() + n > capacity())
					reserve(size() + n);
				for (size_type i = size(); i > pos; i--) {
					__begin_[i + n - 1] = __begin_[i - 1];
				}
				for (size_type i = 0; i < n; i++) {
					__begin_[pos + i] = val;
				}
				__end_ += n;
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				size_type n = ft::distance(first, last);
				size_type pos = position - begin();
				if (size() + n > capacity())
					reserve(size() + n);
				for (size_type i = size(); i > pos; i--) {
					__begin_[i + n - 1] = __begin_[i - 1];
				}
				for (size_type i = 0; i < n; i++) {
					__begin_[pos + i] = *first;
					first++;
				}
				__end_ += n;
			}
			iterator erase(iterator position) {
				size_type n = position - begin();
				for (size_type i = n; i < size() - 1; i++) {
					__begin_[i] = __begin_[i + 1];
				}
				__a_.destroy(__end_);
				__end_--;
				return begin() + n;
			}
			iterator erase(iterator first, iterator last) {
				size_type n = first - begin();
				size_type m = last - begin();
				for (size_type i = n; i < size() - (m - n); i++) {
					__begin_[i] = __begin_[i + (m - n)];
				}
				for (size_type i = 0; i < (m - n); i++) {
					__a_.destroy(__end_);
					__end_--;
				}
				return begin() + n;
			}
			void push_back(const value_type& val) {
				if (size() == capacity())
					reserve(size() * 2);
				__a_.construct(__end_, val);
				__end_++;
			}
			void pop_back() {
				if(size()!= 0){
					__a_.destroy(--__end_);
				}
			}
			void swap(vector& x) {
				pointer			tmp_begin = __begin_;
				pointer			tmp_end = __end_;
				pointer			tmp_end_of_storage = __end_cap_;
				allocator_type	tmp_a = __a_;
				
				__begin_ = x.__begin_;
				__end_ = x.__end_;
				__end_cap_ = x.__end_cap_;
				__a_ = x.__a_;
				
				x.__begin_ = tmp_begin;
				x.__end_ = tmp_end;
				x.__end_cap_ = tmp_end_of_storage;
				x.__a_ = tmp_a;
			}
			void clear() {
				for (size_type i = 0; i < size(); i++) {
					__a_.destroy(__begin_ + i);
				}
				__end_ = __begin_;
			}
			//getter
			allocator_type get_allocator() const {
				return __a_;
			}
	};
	//operator
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return rhs < lhs;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}	
	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	}
			
}

#endif
