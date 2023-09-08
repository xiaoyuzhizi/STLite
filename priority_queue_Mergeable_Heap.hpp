#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

	/**
	 * a container like std::priority_queue which is a heap internal.
	 */
	template<typename T, class Compare = std::less<T>>
	class priority_queue {
		
		class Node {
			friend class priority_queue;

			Node* left;
			Node* right;
			T data;
			int dist;
		public:

			Node(const T& other, Node* l = nullptr, Node* r = nullptr, int d = 0) :data(other), left(l), right(r), dist(d) {}
		};
		typedef Node* node;

		size_t Size;
		node root;
		
		void Delete(node r) {
			if (!r)
				return;
			Delete(r->left);
			Delete(r->right);
			delete r;
			return;
		}
		node Copy(node other) {
			if (!other)
				return nullptr;
			node tmp = new Node(other->data, Copy(other->left), Copy(other->right), other->dist);
			return tmp;
		}
		node merge(node x, node y)
		{

			Compare compare;
			node tmp;
			if (!x || !y) return x ? x : y;
			if (compare(x->data, y->data)) {
				tmp = x;
				x = y;
				y = tmp;
			}
			x->right = merge(x->right, y);
			if (!x->left || x->left->dist < x->right->dist) {
				tmp = x->left;
				x->left = x->right;
				x->right = tmp;
			}
			if (x->right)
				x->dist = x->right->dist + 1;
			else x->dist = 0;
			return x;



		}
	public:

		
		/**
		 * TODO constructors
		 */
		priority_queue() :root(nullptr), Size(0) {}


		priority_queue(const priority_queue& other) {
			root = Copy(other.root);
			Size = other.Size;
		}
		/**
		 * TODO deconstructor
		 */
		~priority_queue() {
			Delete(root);
		
		}
		/**
		 * TODO Assignment operator
		 */
		priority_queue& operator=(const priority_queue& other) {
			if (&other == this)
				return *this;
			Delete(root);
			root = Copy(other.root);
			Size = other.Size;
			return *this;
		
		
		}
		/**
		 * get the top of the queue.
		 * @return a reference of the top element.
		 * throw container_is_empty if empty() returns true;
		 */
		const T& top() const {
			if (!Size)
				throw container_is_empty();
			return root->data;
		}


		/**
		 * merge two priority_queues with at least O(logn) complexity.
		 * clear the other priority_queue.
		 */
		void merge(priority_queue& other) {
			root = merge(root, other.root);
			Size += other.Size;
			other.Size = 0;
			other.root = nullptr;
			return;

		}




		/**
		 * TODO
		 * push new element to the priority queue.
		 */
		void push(const T& e) {
			node tmp = new Node(e);
			root = merge(root, tmp);
			++Size;
			return;
		}
		/**
		 * TODO
		 * delete the top element.
		 * throw container_is_empty if empty() returns true;
		 */
		void pop() {
			if (!Size)
				throw container_is_empty();
			node tmp = root;

			//delete root;
			root = merge(root->left, root->right);
			--Size;
			delete tmp;
			return;

		}
		/**
		 * return the number of the elements.
		 */
		size_t size() const {
			return Size;

		}
		/**
		 * check if the container has at least an element.
		 * @return true if it is empty, false if it has at least an element.
		 */
		bool empty() const {
			return (!Size);

		}
		


	};

}

#endif








