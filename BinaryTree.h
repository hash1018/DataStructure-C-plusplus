//BinaryTree.h
#ifndef _BINARYTREE_H
#define _BINARYTREE_H

typedef signed long int Long;
template <typename T>

class BinaryTree{

public:
	class Node{

		friend class BinaryTree;
	public:
		Node(){
		
			this->left = 0;
			this->right = 0;
		}
		Node(T key){
		
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		static Node* MakeTree(T(*keys), Long high, Long low){
		
			Long mid;
			Node *current = 0;
			if (low <= high){
			
				mid = (low + high) / 2;
				current = new Node(keys[mid]);

				current->left = Node::MakeTree(keys, mid - 1, low);
				current->right = Node::MakeTree(keys, high, mid + 1);
			}

			return current;
		}
		void CopyToBuffer(T(*keys), Long *count){
		
			if (this != 0){
			
				this->left->CopyToBuffer(keys, count);
				keys[*count] = this->key;
				(*count)++;
				this->right->CopyToBuffer(keys, count);
			}
		}
		Node(const Node& source){

			this->key = source.key;
			this->left = 0;
			this->right = 0;
			if (source.left != 0){

				this->left = new Node(source.left);
			}
			if (source.right != 0){

				this->right = new Node(source.right);
			}
		}
		Node& operator =(const Node& source){

			this->key = source.key;
			this->left = 0;
			this->right = 0;
			if (source.left != 0){

				this->left = new Node(source.left);
			}
			if (source.right != 0){

				this->right = new Node(source.right);
			}

			return *this;
		}
		T& GetKey() const{
		
			return const_cast<T&>(this->key);
		}
		~Node(){
		
			if (this->left != 0){
			
				delete this->left;
			}
			if (this->right != 0){
			
				delete this->right;
			}
		}
		void DeleteAllItems(){
		
			if (this != 0){
			
				this->left->DeleteAllItems();
				this->right->DeleteAllItems();
				this->left = 0;
				this->right = 0;
				delete this;
			}
		}

		Node *GetLeft() const{
		
			return this->left;
		}
		Node *GetRight() const{
		
			return this->right;
		}

	private:
		Node *left;
		T key;
		Node *right;

	};

	public:
		BinaryTree();
		BinaryTree(const BinaryTree& source);
		~BinaryTree();
		Node *Insert(T key);
		Node *Search(T key);
		Node *Delete(T key);
		void MakeBalance();
		Node *MakeTree(T(*keys), Long count);
		void DeleteAllItems();
		void CopyToBuffer(T*(*keys), Long *count);
		BinaryTree& operator =(const BinaryTree& source);
		Long GetLength() const;
		Long GetBalance() const;
		Node* GetRoot() const;
		private:
			Node *root;
			Long length;
			Long balance;


};

template <typename T>
inline Long BinaryTree<T>::GetLength() const{

	return this->length;
}
template <typename T>
inline Long BinaryTree<T>::GetBalance() const{

	return this->balance;
}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::GetRoot() const{

	return this->root;
}

template <typename T>
BinaryTree<T>::BinaryTree(){

	this->root = 0;
	this->balance = 0;
	this->length = 0;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source){

	if (source.root != 0){
	
		this->root = new Node(*source.root);
	}

	this->length = source.length;
	this->balance = source.balance;
}

template <typename T>
BinaryTree& BinaryTree<T>::operator =(const BinaryTree& source){

	if (source.root != 0){
	
		delete this->root;
	}

	this->root = new Node(*source.root);
	this->length = source.length;
	this->balance = source.balance;

	return *this;

}

template <typename T>
BinaryTree <T>::~BinaryTree(){

	if (this->root != 0){
	
		delete this->root;
	}
}