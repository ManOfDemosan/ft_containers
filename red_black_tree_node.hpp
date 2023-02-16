#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

namespace ft {
	enum Color {
			RED,
			BLACK,
			DUB_BLACK
		};

	template <typename T>
	struct RedBlackTreeNode {
		T value;
		Color color;
		RedBlackTreeNode *left;
		RedBlackTreeNode *right;
		RedBlackTreeNode *parent;

		RedBlackTreeNode() : value(), color(RED), left(NULL), right(NULL), parent(NULL) {}
		// RedBlackTreeNode(const T &value) : value(value), color(RED), left(NULL), right(NULL), parent(NULL) {}
		RedBlackTreeNode(const T &value, Color color = RED, RedBlackTreeNode *left = NULL, RedBlackTreeNode *right = NULL, RedBlackTreeNode *parent = NULL) : value(value), color(color), left(left), right(right), parent(parent) {}
		RedBlackTreeNode(const RedBlackTreeNode &other) : value(other.value), color(other.color), left(other.left), right(other.right), parent(other.parent) {}
		
		~RedBlackTreeNode() {}
		
		RedBlackTreeNode &operator=(const RedBlackTreeNode &other) {
			if (this != &other) {
				value = other.value;
				color = other.color;
				left = other.left;
				right = other.right;
				parent = other.parent;
			}
			return *this;
		}

		bool operator==(const RedBlackTreeNode &other) const {
			return value == other.value;
		}

		bool operator!=(const RedBlackTreeNode &other) const {
			return value != other.value;
		}

		// bool operator<(const RedBlackTreeNode &other) const {
		// 	return value < other.value;
		// }

		// bool operator<=(const RedBlackTreeNode &other) const {
		// 	return value <= other.value;
		// }

		// bool operator>(const RedBlackTreeNode &other) const {
		// 	return value > other.value;
		// }

		// bool operator>=(const RedBlackTreeNode &other) const {
		// 	return value >= other.value;
		// }
	};

	template <class T1, class T2>
	bool operator==(const RedBlackTreeNode<T1> &lhs, const RedBlackTreeNode<T2> &rhs) {
		return lhs == rhs;
	}

	template <class T1, class T2>
	bool operator!=(const RedBlackTreeNode<T1> &lhs, const RedBlackTreeNode<T2> &rhs) {
		return lhs != rhs;
	}

	// template <class T1, class T2>
	// bool operator<(const RedBlackTreeNode<T1> &lhs, const RedBlackTreeNode<T2> &rhs) {
	// 	return lhs.value < rhs.value;
	// }

	// template <class T1, class T2>
	// bool operator<=(const RedBlackTreeNode<T1> &lhs, const RedBlackTreeNode<T2> &rhs) {
	// 	return lhs.value <= rhs.value;
	// }

	// template <class T1, class T2>
	// bool operator>(const RedBlackTreeNode<T1> &lhs, const RedBlackTreeNode<T2> &rhs) {
	// 	return lhs.value > rhs.value;
	// }

	// template <class T1, class T2>
	// bool operator>=(const RedBlackTreeNode<T1> &lhs, const RedBlackTreeNode<T2> &rhs) {
	// 	return lhs.value >= rhs.value;
	// }
};
#endif
