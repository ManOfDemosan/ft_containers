#ifndef RED_BACK_TREE_HPP
#define RED_BACK_TREE_HPP

#include "red_black_tree_node.hpp"
#include "red_black_tree_iterator.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include <memory>

namespace ft{

	template <typename T, typename Compare, typename Alloc = std::allocator<T> >
	class red_black_tree {

	// typedefs =========================================================================================
	
		private:
			typedef ft::RedBlackTreeNode<T>									node_type;
			typedef ft::RedBlackTreeNode<T>*								node_ptr;
			typedef typename Alloc::template rebind<node_type>::other	node_alloc_type;

		public:
			typedef T													value_type;
			typedef Compare												value_compare;
			typedef Alloc												allocator_type;
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef ft::tree_iterator<value_type>						iterator;
			typedef ft::tree_const_iterator<value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	// ==================================================================================================


	// private members ==================================================================================
		
		private:
			value_compare	_comp;
			allocator_type	_alloc;
			node_alloc_type	_node_alloc;
			node_ptr		_head_node;
			size_type		_size;

		public :
			red_black_tree(value_compare const& comp, allocator_type const& alloc, node_alloc_type const& node_alloc = node_alloc_type())
				: _comp(comp), _alloc(alloc), _node_alloc(node_alloc), _head_node(NULL), _size(0) {
				_head_node = _node_alloc.allocate(1);
				_node_alloc.construct(_head_node, node_type());
			}
			red_black_tree(const red_black_tree& x) : _comp(x._comp), _alloc(x._alloc), _node_alloc(x._node_alloc), _head_node(NULL), _size(0) {
				_head_node = _node_alloc.allocate(1);
				_node_alloc.construct(_head_node, node_type());
				if(x.get_root() != NULL){
					copy_tree(x.get_root());
				}
			}


			red_black_tree& operator=(const red_black_tree& x) {
				if (this == &x) {
					return *this;
				}
				clear();
				_comp = x._comp;
				_alloc = x._alloc;
				_node_alloc = x._node_alloc;
				if(x.get_root() != NULL){
					copy_tree(x.get_root());
				}
				_size = x._size;
				return *this;
			}

			virtual ~red_black_tree() {
				clear();
				_node_alloc.destroy(_head_node);
				_node_alloc.deallocate(_head_node, 1);
			}

	// ==================================================================================================

	// iterators ========================================================================================

		public:

			iterator				begin() { return iterator(min_value_node(_head_node)); }

			const_iterator			begin() const { return const_iterator(min_value_node(_head_node)); }

			iterator				end() { return iterator(_head_node); }

			const_iterator			end() const { return const_iterator(_head_node); }

			reverse_iterator		rbegin() { return reverse_iterator(end()); }

			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }

			reverse_iterator		rend() { return reverse_iterator(begin()); }

			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
	// ==================================================================================================

	//private member fuc
		private:
			node_ptr get_root()const{
				return _head_node->left;
			}

			void set_root(node_ptr node){
				_head_node->left = node;
				_head_node->right = node;
				if (node != NULL){
					node->parent = _head_node;
				}
			}

			void delete_tree(node_ptr node){
				if (node == NULL)
					return;
				delete_tree(node->left);
				delete_tree(node->right);
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}//delete_tree

			void copy_tree(node_ptr node){
				if (node == NULL)
					return;
				insert_value(node->value);
				copy_tree(node->left);
				copy_tree(node->right);
			}//copy_tree

			void rotate_left(node_ptr node){
				node_ptr right_child = node->right;//입력 노드의 오른쪽 하위에 포인터를 저장합니다.

				if (right_child == NULL)//오른쪽 자식이 null인지 확인합니다. 만약 그렇다면, 그 기능은 아무것도 하지 않고 돌아온다.
					return;
				node->right = right_child->left;
				if (node->right != NULL)
					node->right->parent = node;// 오른쪽 하위노드에 대한 상위 및 하위 포인터를 업데이트하여 오른쪽 하위노드가 회전할 노드의 새 상위노드가 되도록 합니다.
				right_child->parent = node->parent;
				if (get_parent(node) == NULL)//루트노드일때
					set_root(right_child);//원래 노드의 상위를 가리키도록 오른쪽 하위의 상위 포인터를 업데이트합니다.
				else if (node == get_parent(node)->left)// 현재노드가 보모의 노드의 왼쪽노드이면
					get_parent(node)->left = right_child;//트리의 루트의 왼쪽노드를 오른쪽 자식노드를 가리키도록 업데이트합니다. -> 회전한다
				else
					get_parent(node)->right = right_child;//현재의 노드가 부모의 노드의 오른쪽노드이면 루트가 오른쪽 자식노드를 가리키도록 업데이트합니다.
				right_child->left = node;//오른쪽 자식의 왼쪽 자식을 원래 노드로 업데이트합니다.
				node->parent = right_child;//원래 노드의 상위 포인터가 오른쪽 자식노드를 가리키도록 업데이트합니다
			}

			void rotate_right(node_ptr node){
				node_ptr left_child = node->left;

				if (left_child == NULL)
					return;
				node->left = left_child->right;
				if (node->left != NULL)
					node->left->parent = node;
				left_child->parent = node->parent;
				if (get_parent(node) == NULL)
					set_root(left_child);
				else if (node == get_parent(node)->left)
					get_parent(node)->left = left_child;
				else
					get_parent(node)->right = left_child;
				left_child->right = node;
				node->parent = left_child;
			}//rotate_right

		 	node_ptr min_value_node(node_ptr node)const{
				if(node == NULL)
					return node;
				while (node->left != NULL)
					node = node->left;
				return node;
			}//min_value_node

			node_ptr max_value_node(node_ptr node)const{
				if(node == NULL)
					return node; 
				while (node->right != NULL)
					node = node->right;
				return node;
			}//max_value_node

			node_ptr get_parent(node_ptr node){
				if(node == NULL)
					return node; 
				if(node == _head_node)
					return NULL;
				return node->parent;
			}

			node_ptr get_grandparent(node_ptr node){
				node_ptr par = get_parent(node);
				if(par == NULL)
					return NULL;
				return get_parent(par);
			}

			node_ptr get_sibling(node_ptr node){
				node_ptr par = get_parent(node);
				if(par == NULL)
					return NULL;
				if(node == par->left)
					return par->right;
				else
					return par->left;
			}

			node_ptr get_uncle(node_ptr node){
				node_ptr par = get_parent(node);
				if(par == NULL)
					return NULL;
				return get_sibling(par);
			}

			Color get_color(node_ptr node){
				if(node == NULL)
					return BLACK;
				return node->color;
			}

			void set_color(node_ptr node, Color color){
				if(node == NULL)
					return;
				node->color = color;
			}
	// ==================================================================================================

	// capacity =========================================================================================

		public:
			bool empty() const {
				return _size == 0;
			}

			size_type size() const {
				return _size;
			}

			size_type max_size() const {
				return _node_alloc.max_size();
			}
	// insert =============================================================================================

			pair<iterator, bool> insert_node(node_ptr node) {
				node_ptr tmp = get_root();
				node_ptr parent;

				if (tmp == NULL) {
					set_root(node);
					return ft::make_pair(iterator(node), true);
				}
				while (tmp) {
					if (_comp(node->value, tmp->value)) {
						parent = tmp;
						tmp = tmp->left;
					}
					else if (_comp(tmp->value, node->value)) {
						parent = tmp;
						tmp = tmp->right;
					}
					else
						return ft::make_pair(iterator(tmp), false);
				}
				if (_comp(parent->value, node->value)) {
					parent->right = node;
					node->parent = parent;
				} else {
					parent->left = node;
					node->parent = parent;
				}
				return ft::make_pair(iterator(node), true);
			}

			pair<iterator, bool> insert_value(const value_type& val){
				node_ptr node = _node_alloc.allocate(1);

				_node_alloc.construct(node, node_type(val));
				pair<iterator, bool> ret = insert_node(node);
				if(ret.second == true){
					_size++;
					insert_fixup(node);
				}
				else{
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
				}
				return ret;
			}
			void insert_fixup(node_ptr node) {
				node_ptr parent;
				node_ptr grand_parent;

				while (node != get_root() && get_color(node) == RED && get_color(get_parent(node)) == RED) {
					parent = get_parent(node);
					grand_parent = get_grandparent(node);
					if (grand_parent == NULL)
						break;
					node_ptr uncle = get_uncle(node);
					if (get_color(uncle) == RED) {
						set_color(get_parent(node), BLACK);
						set_color(get_uncle(node), BLACK);
						set_color(get_grandparent(node), RED);
						node = get_grandparent(node);
					} else if (parent == grand_parent->left) {
						if (node == parent->right) {
							if (parent == get_grandparent(node)->left) {
								rotate_left(parent);
								node = parent;
								parent = get_parent(node);
							}
							if (parent == get_grandparent(node)->right) {
								rotate_right(parent);
								node = parent;
								parent = get_parent(node);
							}
						}
						else{
							if (parent == grand_parent->left) {
								rotate_right(grand_parent);
							}
							if (parent == grand_parent->right) {
								rotate_left(grand_parent);
							}
							std::swap(parent->color, grand_parent->color);
							node = parent;
						}
					} else if (parent == grand_parent->right) {
						if (node == parent->left) {
							if (parent == get_grandparent(node)->left) {
								rotate_left(parent);
								node = parent;
								parent = get_parent(node);
							}
							if (parent == get_grandparent(node)->right) {
								rotate_right(parent);
								node = parent;
								parent = get_parent(node);
							}
						}
						else{
							if (parent == grand_parent->left) {
								rotate_right(grand_parent);
							}
							if (parent == grand_parent->right) {
								rotate_left(grand_parent);
							}
							std::swap(parent->color, grand_parent->color);
							node = parent;
						}
					}
				}
				set_color(get_root(), BLACK);
			}
		
			pair<iterator, bool> insert(const value_type& val){
				return insert_value(val);
			}

			iterator insert(iterator position, const value_type& val){
				(void)position;
				return insert_value(val).first;
			}


			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL){
				for (InputIterator it = first; it != last; ++it) {
					insert(*it);
				}
			}
		

	// erase ============================================================================================
			void erase(const_iterator position){
				delete_value(*position);
			}

			size_type erase(const value_type& val){
				return delete_value(val);
			}

			void erase(const_iterator first, const_iterator last){
				for (const_iterator it = first; it != last; ) {
					erase(it++);
				}
			}

			size_t delete_value(const value_type& val){
				node_ptr node = delete_node(get_root(), val);
				if(node == NULL)
					return 0;
				delete_fixup(node);
				_size--;
				return 1;
			}

			node_ptr delete_node(node_ptr node, const value_type& val){
				if (node == NULL)
					return node;
				if (_comp(node->value, val))
					return delete_node(node->right, val);
				if (_comp(val, node->value))
					return delete_node(node->left, val);
				if (node->left == NULL || node->right == NULL)
					return node;

				node_ptr tmp = min_value_node(node->right);
				if (tmp->parent == node) {
					if (node->parent && node->parent->left == node)
						node->parent->left = tmp;
					if (node->parent && node->parent->right == node)
						node->parent->right = tmp;
					tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL;
					tmp->parent = node->parent;
					node->parent = tmp;
					node->right = tmp->right;
					tmp->right = node;
					std::swap(tmp->color, node->color);
				} else {
					if (node->parent && node->parent->left == node)
						node->parent->left = tmp;
					if (node->parent && node->parent->right == node)
						node->parent->right = tmp;
					if (tmp->parent->left == tmp)
						tmp->parent->left = node;
					if (tmp->parent->right == tmp)
						tmp->parent->right = node;
					node_ptr tmp2 = tmp->parent;
					node->right->parent = tmp;
					tmp->parent = node->parent;
					node->parent = tmp2;
					tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL;
					tmp2 = tmp->right;
					tmp->right = node->right;
					node->right = tmp2;
					std::swap(tmp->color, node->color);
				}
				return delete_node(tmp->right, val);
			}

			void delete_fixup(node_ptr node){
				if (node == NULL)
					return;
				if (node == get_root()) {//root delete fixup
					if (node->right)
						set_root(node->right);
					else
						set_root(node->left);
						_node_alloc.destroy(node);
						_node_alloc.deallocate(node, 1);
						set_color(get_root(), BLACK);
					return;
				}
				if (get_color(node) == RED || get_color(node->left) == RED|| get_color(node->right) == RED) {
					node_ptr child = node->left != NULL ? node->left : node->right;

					if (node == node->parent->left)
						node->parent->left = child;
					else
						node->parent->right = child;
					if (child != NULL)
						child->parent = node->parent;
					set_color(child, BLACK);
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					return;//delete red node 
				}
				node_ptr s = NULL;
				node_ptr p = NULL;
				node_ptr tmp = node;
				set_color(tmp, DUB_BLACK);
				while (tmp != get_root() && get_color(tmp) == DUB_BLACK) {
					p = tmp->parent;
					s = (tmp == p->left) ? p->right : p->left;
					if (get_color(s) == RED){//case 1
						set_color(s, BLACK);
						set_color(p, RED);
						if (s == p->right)
							rotate_left(p);
						if (s == p->left)
							rotate_right(p);
					}
					else if (get_color(s->left) == BLACK && get_color(s->right) == BLACK){
						set_color(s, RED);
						if (get_color(p) == RED)
							set_color(p, BLACK);
						else
							set_color(p, DUB_BLACK);
						tmp = p;//case 2
					}
					else {
						if ((tmp == p->left && get_color(s->right) == BLACK) 
						|| (tmp == p->right && get_color(s->left) == BLACK)){
							if (s == p->right) {
								set_color(s->left, BLACK);
								set_color(s, RED);
								rotate_right(s);
								s = p->right;
							}
							if (s == p->left) {
								set_color(s->right, BLACK);
								set_color(s, RED);
								rotate_left(s);
								s = p->left;
							}
						}
						if (s == p->right) {
							set_color(s, get_color(p));
							set_color(p, BLACK);
							set_color(s->right, BLACK);
							rotate_left(p);
						}
						if (s == p->left) {
							set_color(s, get_color(p));
							set_color(p, BLACK);
							set_color(s->left, BLACK);
							rotate_right(p);
						}
						break;
					}
				}
				if (node == node->parent->left)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
				set_color(get_root(), BLACK);
			}
			

	// swap =============================================================================================

			void swap(red_black_tree& ref) {
				if (this == &ref) {
					return;
				}
				value_compare	tmp_comp = ref._comp;
				allocator_type	tmp_alloc = ref._alloc;
				node_alloc_type	tmp_node_alloc = ref._node_alloc;
				node_ptr		tmp_head_node = ref._head_node;
				size_type		tmp_size = ref._size;

				ref._comp = _comp;
				ref._alloc = _alloc;
				ref._node_alloc = _node_alloc;
				ref._head_node = _head_node;
				ref._size = _size;

				_comp = tmp_comp;
				_alloc = tmp_alloc;
				_node_alloc = tmp_node_alloc;
				_head_node = tmp_head_node;
				_size = tmp_size;
			}

	// ==================================================================================================

	// clear ============================================================================================

			void clear() {
				delete_tree(_head_node->parent);
				set_root(NULL);
				_size = 0;
			}

	// ==================================================================================================

	// find =============================================================================================
		iterator find(const value_type& v) const {
				node_ptr tmp = get_root();
				
				while (tmp != NULL) {
					if (!_comp(tmp->value, v) && !_comp(v, tmp->value)) {
						break;
					} else if (_comp(tmp->value, v)) {
						tmp = tmp->right;
					} else {
						tmp = tmp->left;
					}
				}
				if (tmp == NULL) {
					return (iterator(this->_head_node));
				}
				return (iterator(tmp));
			}

	// ==================================================================================================

	// count ============================================================================================


			size_type count(const value_type& v) const {
				iterator tmp = find(v);
				if (tmp == end()) {
					return 0;
				}
				size_type count = 0;
				for (iterator it = tmp; it != end(); ++it) {
					if (!_comp(*it, v) && !_comp(v, *it)) {
						++count;
					}
				}
				return count;
			}

	// ==================================================================================================





	};
}

#endif