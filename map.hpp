#ifndef MAP_HPP
#define MAP_HPP

#include "red_black_tree.hpp"
#include <memory>

namespace ft{
	template<typename Key, typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;

		typedef typename ft::tree_iterator<value_type> iterator;
		typedef typename ft::tree_const_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>{
			friend class map;
			protected:
			Compare comp;
			value_compare(Compare const& c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type& x, const value_type& y) const{
				return comp(x.first, y.first);
			}
		};

	private:
		key_compare														_comp;
		allocator_type													_alloc;
		ft::red_black_tree<value_type, value_compare, allocator_type>	_tree;
	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		: _comp(comp), _alloc(alloc), _tree(value_compare(_comp), _alloc){}
		
		template<typename InputIterator>
		map(InputIterator first, InputIterator last,
		 const key_compare& comp = key_compare(), 
		 const allocator_type& alloc = allocator_type()) 
		 : _comp(comp), _alloc(alloc), _tree(value_compare(_comp), _alloc){
			insert(first, last);
		}
		map(const map& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree){}
		~map(){}

		map& operator=(const map& x){
			if(this == &x)
				return *this;
			_tree = x._tree;
			return *this;
		}

		iterator begin(){return _tree.begin();}
		const_iterator begin() const{return _tree.begin();}

		iterator end(){return _tree.end();}
		const_iterator end() const{return _tree.end();}

		reverse_iterator rbegin(){return _tree.rbegin();}
		const_reverse_iterator rbegin() const{return _tree.rbegin();}

		reverse_iterator rend(){return _tree.rend();}
		const_reverse_iterator rend() const{return _tree.rbegin();}

		bool empty() const{return _tree.empty();}
		size_type size() const{return _tree.size();}
		size_type max_size() const{return _tree.max_size();}

		mapped_type& operator[](const key_type& k){
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

		//insert
		pair<iterator, bool> insert(const value_type& val){
			return _tree.insert(val);
		}
		iterator insert(iterator position, const value_type& val){
			return _tree.insert(position, val);
		}
		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last){
			_tree.insert(first, last);
		}

		void erase(iterator position){
			_tree.erase(position);
		}
		size_type erase(const key_type& k){
			return _tree.erase(ft::make_pair(k, mapped_type()));
		}
		void erase(iterator first, iterator last){
			_tree.erase(first, last);
		}
		void swap(map& x){
			_tree.swap(x._tree);
		}
		void clear(){
			_tree.clear();
		}
		key_compare key_comp() const{
			return key_compare();
		}
		value_compare value_comp() const{
			return value_compare(key_compare());
		}

		iterator find(const key_type& k){
			return _tree.find(ft::make_pair(k, mapped_type()));
		}
		const_iterator find(const key_type& k) const{
			return _tree.find(ft::make_pair(k, mapped_type()));
		}
		size_type count(const key_type& k) const{
			return _tree.count(ft::make_pair(k, mapped_type()));
		}
	
		iterator lower_bound(const key_type& key) {
				iterator it1 = this->begin();
				iterator it2 = this->end();
				while (it1 != it2) {
					if (_comp(it1->first, key) == false)
						break;
					++it1;
				}
				return it1;
		}

		const_iterator lower_bound(const key_type& key) const {
				const_iterator it1 = this->begin();
				const_iterator it2 = this->end();
				while (it1 != it2) {
					if (_comp(it1->first, key) == false)
						break;
					++it1;
				}
				return it1;
		}

		iterator upper_bound(const key_type& key) {
				iterator it1 = this->begin();
				iterator it2 = this->end();
				while (it1 != it2) {
					if (_comp(key, it1->first) == true)
						break;
					++it1;
				}
				return it1;
		}
	
		const_iterator upper_bound(const key_type& key) const {
				const_iterator it1 = this->begin();
				const_iterator it2 = this->end();
				while (it1 != it2) {
					if (_comp(key, it1->first) == true)
						break;
					++it1;
				}
				return it1;
		}

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const{
			const_iterator it1 = this->lower_bound(k);
			const_iterator it2 = this->upper_bound(k);
			return ft::make_pair(it1, it2);
		}
		pair<iterator, iterator> equal_range(const key_type& k){
			iterator it1 = this->lower_bound(k);
			iterator it2 = this->upper_bound(k);
			return ft::make_pair(it1, it2);
		}
		allocator_type get_allocator() const{
			return allocator_type();
		}
	};
	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
		if (x.size() != y.size())
			return false;
		return ft::equal(x.begin(), x.end(), y.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
		return y < x;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
		return !(x < y);
	}

};
#endif