#include <functional>
template<typename T> class BinaryTree {
private:

	struct Node {
		const T data;
		Node const* left;
		Node const* right;
	};

	std::function<bool(T, T)> comparator;
	Node const* root;

	BinaryTree(std::function<bool(T, T)> comparator, Node const* root) :
		comparator(comparator), root(root) {}

public:

	BinaryTree(std::function<bool(T, T)> comparator) :
		BinaryTree(comparator, nullptr) {}

	BinaryTree with(T object) const noexcept {
		return BinaryTree(
			comparator,
			root == nullptr
			? new Node{ object }
			: comparator(object, root->data)
			? new Node{
				root->data,
				root->left,
				BinaryTree(comparator, root->right)
					.with(object)
					.root
			}
			: new Node{
				root->data,
				BinaryTree(comparator, root->left)
					.with(object)
					.root,
				root->right
			}
		);
	}

	void forEach(std::function<void(T)> сonsumer) const noexcept {
		std::function<void(Node const*)> iterate = 
			[&iterate, &сonsumer](Node const* node) {
			if (node == nullptr) return;
			сonsumer(node->data);
			iterate(node->left);
			iterate(node->right);
		};
		iterate(root);
	}
};
