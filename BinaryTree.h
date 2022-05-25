#include <functional>
template<typename T> class BinaryTree {
private:

	struct Node {
		const T data;
		const Node* left;
		const Node* right;
	};

	const std::function<bool(const T&, const T&)> comparator;
	const Node* root;

	void forEach(std::function<void(const T&)> сonsumer, const Node* node) const noexcept {
		if (node == nullptr) return;
		сonsumer(node->data);
		forEach(сonsumer, node->left);
		forEach(сonsumer, node->right);
	}

	BinaryTree(std::function<bool(const T&, const T&)> comparator, const Node* root) :
		comparator(comparator), root(root) {}

public:

	BinaryTree(std::function<bool(const T&, const T&)> comparator) :
		BinaryTree(comparator, 0) {}

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

	void forEach(std::function<void(const T&)> сonsumer) const noexcept {
		forEach(сonsumer, root);
	}
};
