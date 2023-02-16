#ifndef SET_HPP
#define SET_HPP

#include "red_black_tree.hpp"
#include <memory>

namespace ft {

	template <class Key, class Compare = ft::less<Key>, class Alloc = std::allocator<Key> >
	class set {
		public:
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::tree_const_iterator<value_type> iterator;
		typedef typename ft::tree_const_iterator<value_type> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			key_compare _comp;
			allocator_type _alloc;
			ft::red_black_tree<value_type, key_compare, allocator_type> _tree;

		public:
			explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree(value_compare(), alloc) {}

			template <class InputIterator>
			set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree(value_compare(), alloc) {
				_tree.insert(first, last);
			}

			set(const set& ref)
			: _comp(ref._comp), _alloc(ref._alloc), _tree(ref._tree) {}

			~set() {}

			set& operator=(const set& ref) {
				_tree = ref._tree;
				return *this;
			}

			//iterators
			iterator begin() {
				return _tree.begin();
			}

			const_iterator begin() const {
				return _tree.begin();
			}

			iterator end() {
				return _tree.end();
			}

			const_iterator end() const {
				return _tree.end();
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}

			//capacity
			bool empty() const {
				return _tree.empty();
			}

			size_type size() const {
				return _tree.size();
			}

			size_type max_size() const {
				return _alloc.max_size();
			}

			//modifiers
			pair<iterator, bool> insert(const value_type& val) {
				return _tree.insert(val);
			}
			
			iterator insert(iterator position, const value_type& val) {
				(void)position;
				return _tree.insert(val).first;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				_tree.insert(first, last);
			}

			void erase(iterator position) {
				_tree.erase(position);
			}

			size_type erase(const key_type& k) {
				return _tree.erase(k);
			}

			void erase(iterator first, iterator last) {
				_tree.erase(first, last);
			}

			void swap(set& x) {
				_tree.swap(x._tree);
			}

			void clear() {
				_tree.clear();
			}
			
			key_compare key_comp() const {
				return _comp;
			}
			
			value_compare value_comp() const {
				return _comp;
			}

			//operations
			iterator find(const key_type& k) {
				return _tree.find(k);
			}

			const_iterator find(const key_type& k) const {
				return _tree.find(k);
			}

			size_type count(const key_type& k) const {
				return _tree.count(k);
			}

			iterator lower_bound(const key_type& k) {
				iterator	it1 = this->begin();
				iterator	it2 = this->end();
				while (it1 != it2)
				{
					if (_comp(*it1, k) == false)
						break;
					++it1;
				}
				return it1;
			}

			const_iterator lower_bound(const key_type& k) const {
				const_iterator	it1 = this->begin();
				const_iterator	it2 = this->end();
				while (it1 != it2)
				{
					if (_comp(*it1, k) == false)
						break;
					++it1;
				}
				return it1;
			}

			iterator upper_bound(const key_type& k) {
				iterator	it1 = this->begin();
				iterator	it2 = this->end();
				while (it1 != it2)
				{
					if (_comp(k, *it1) == true)
						break;
					++it1;
				}
				return it1;
			}

			const_iterator upper_bound(const key_type& k) const {
				const_iterator	it1 = this->begin();
				const_iterator	it2 = this->end();
				while (it1 != it2)
				{
					if (_comp(k, *it1) == true)
						break;
					++it1;
				}
				return it1;
			}

			pair<iterator,iterator>	equal_range (const value_type& k) const {
				return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
			}

			//allocator
			allocator_type get_allocator() const {
				return _alloc;
			}
	};

	template <class Key, class Compare, class Alloc>
	void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator==(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class Compare, class Alloc>
	bool operator!=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator<(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class Compare, class Alloc>
	bool operator>(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class Key, class Compare, class Alloc>
	bool operator<=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}
}


#endif