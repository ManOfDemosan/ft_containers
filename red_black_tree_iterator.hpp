#ifndef RED_BLACK_TREE_ITERATOR_HPP
#define RED_BLACK_TREE_ITERATOR_HPP

#include "iterator.hpp"
#include "red_black_tree_node.hpp"
#include "enable_if.hpp"


namespace ft{
	template <typename T>
	class tree_const_iterator; 

	template <typename T>
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{
		private:
			typedef ft::RedBlackTreeNode<T> 	Node;
			typedef ft::RedBlackTreeNode<T>* 	NodePtr;
			NodePtr								_node;
		
		public:
			typedef	bidirectional_iterator_tag		iterator_category;
			typedef	T								value_type;
			typedef	T*								pointer;
			typedef	T&								reference;
			typedef	std::ptrdiff_t					difference_type;
			
			tree_iterator() : _node(NULL) {}
			tree_iterator(const tree_iterator &other) : _node(other._node) {}
			tree_iterator(NodePtr node) : _node(node) {}
			~tree_iterator() {}
			tree_iterator &operator=(const tree_iterator &other) {
				_node = other._node;
				return *this;
			}

			NodePtr	 base() const { return (_node); }

			tree_iterator& operator++() {
				if (_node->right != NULL) {
					_node = min_value_node(_node->right);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->left)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				return (*this);
			}
			tree_iterator operator++(int) {
				tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			tree_iterator& operator--() {
				if (_node->left != NULL) {
					_node = max_value_node(_node->left);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->right)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				else 
					_node = NULL;
				return (*this);
			}

			tree_iterator operator--(int) {
				tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			reference operator*() const {return (_node->value);}
			pointer operator->() const { return (&(_node->value)); }
			
			bool operator==(const tree_iterator& ref) const { return (_node == ref.base()); }

			bool operator!=(const tree_iterator& ref) const { return (_node != ref.base()); }

			bool operator==(const tree_const_iterator<T>& ref) const { return (_node == ref.base()); }
			
			bool operator!=(const tree_const_iterator<T>& ref) const { return (_node != ref.base()); }
			
			private:
			NodePtr min_value_node(NodePtr node) {
				if (node->left == NULL)
					return (node);
				return (min_value_node(node->left));
			}

			NodePtr max_value_node(NodePtr node) {
				if (node->right == NULL)
					return (node);
				return (max_value_node(node->right));
			}
	};

	template<typename T>
	class tree_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{
		private:
			typedef ft::RedBlackTreeNode<T> Node;
			typedef ft::RedBlackTreeNode<T> *NodePtr;
			NodePtr _node;
		
		public:
			typedef	bidirectional_iterator_tag		iterator_category;
			typedef	T								value_type;
			typedef	const T*						pointer;
			typedef	const T&						reference;
			typedef	std::ptrdiff_t					difference_type;

			tree_const_iterator() : _node(NULL) {}
			tree_const_iterator(const tree_const_iterator &other) : _node(other._node) {}
			tree_const_iterator(const tree_iterator<T> &other) : _node(other.base()) {}
			tree_const_iterator(NodePtr node) : _node(node) {}
			virtual ~tree_const_iterator() {}
			tree_const_iterator& operator=(const tree_const_iterator &ref) {
				if (this != &ref)
					_node = ref.base();
				return (*this);
			}
			tree_const_iterator& operator=(const tree_iterator<T>& ref) {
				if (this != &ref)
					_node = ref.base();
				return (*this);
			}

			NodePtr	 base() const { return (_node); }

			tree_const_iterator &operator++() {
				if (_node->right != NULL) {
					_node = min_value_node(_node->right);
					return (*this);
				}
				while(_node->parent != NULL && _node != _node->parent->left)
					_node = _node->parent;
				if(_node->parent != NULL) {
					_node = _node->parent;
				}
					
				return (*this);
			}
			

			tree_const_iterator operator++(int) {
				tree_const_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			tree_const_iterator &operator--() {
				if (_node->left != NULL) {
					_node = max_value_node(_node->left);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->right)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				else 
					_node = NULL;
				return (*this);
			}
			tree_const_iterator operator--(int) {
				tree_const_iterator tmp(*this);
				--(*this);
				return tmp;
			}

			reference operator*() const {
				return _node->value;
			}
			pointer operator->() const {
				return (&(_node->value));
			}
			
			
			bool operator==(const tree_const_iterator& ref) const { return (_node == ref.base()); }

			bool operator!=(const tree_const_iterator& ref) const { return (_node != ref.base()); }

			bool operator==(const tree_iterator<T>& ref) const { return (_node == ref.base()); }

			bool operator!=(const tree_iterator<T>& ref) const { return (_node != ref.base()); }

		private:
			NodePtr min_value_node(NodePtr node) {
				if (node->left == NULL)
					return (node);
				return (min_value_node(node->left));
			}

			NodePtr max_value_node(NodePtr node) {
				if (node->right == NULL)
					return (node);
				return (max_value_node(node->right));
			}
	};

}


#endif
