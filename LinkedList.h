//LinkedList.h

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef signed long int Long;
template <typename T>

class LinkedList{

public:
	class Node{

		friend class LinkedList;
	public:
		Node(){
		
			this->previous = 0;
			this->next = 0;
		}
		Node(T object){
		
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node *next){
		
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		Node(Node *previous, T object){
		
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(Node *previous, T object, Node *next){
		
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		~Node(){
		
		}

		Node(const Node& source){
		
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
		}

		Node& operator=(const Node& source){
		
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
			return *this;
		}

		T& GetObject() const{
		
			return const_cast<T&>(this->object);
		}

	private:
		Node *previous;
		T object;
		Node *next;


	};

public:
	LinkedList();
	LinkedList(const LinkedList& source);
	~LinkedList();
	Node *InsertBefore(Node *index, T object);
	Node *InsertAfter(Node *index, T object);
	Node *AppendFromHead(T object);
	Node *AppendFromTail(T object);
	Node *Delete(Node *index);
	Node *DeleteFromHead();
	Node *DeleteFromTail();
	void DeleteAllItems();
	Node *LinearSearchUnique(void *key, int(*Compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*Compare)(void*, void*));
	Node *First();
	Node *Previous();
	Node *Next();
	Node *Last();
	LinkedList& operator=(const LinkedList& source);
	T& operator[](Long index);
	Long GetLength() const;
	Node* GetCurrent() const;
	
private:
	Node *head;
	Node *tail;
	Long length;
	Node *current;
	


};

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::GetCurrent() const{

	return this->current;
}

template <typename T>
inline Long LinkedList <T>::GetLength() const{

	return this->length;
}

template <typename T>
LinkedList <T>::LinkedList(){

	this->head = 0;
	this->tail = 0;
	this->current = 0;
	this->length = 0;
}

template <typename T>
LinkedList <T>::LinkedList(const LinkedList& source){

	LinkedList<T>::Node *it = 0;
	LinkedList<T>::Node *index = 0;
	LinkedList<T>::Node *itr = 0;

	it = source.head;
	if (it != 0){
	
		this->head = new Node(it->object);
		index = this->head;
		this->tail = this->head;
		itr = it;
		it = it->next;
		
	}

	while (itr != source.tail){
	
		index->next = new Node(it->object);
		index->next->previous = index;
		index = index->next;
		this->tail = index;
		it = it->next;
		itr = itr->next;
	}

	index = this->head;
	it=source.head;

	while (it != source.current){
	
		index = index->next;
		it = it->next;
	}

	this->current = index;
	this->length = source.length;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::InsertBefore(Node *index, T object){

	if (this->head != index){
	
		this->current = new Node(index->previous, object, index);

	}
	else{
	
		this->current = new Node(object, index);
	}

	if (this->head != index){
	
		index->previous->next = this->current;
	}
	else{
	
		this->head = this->current;
	}

	index->previous = this->current;
	this->length++;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::InsertAfter(Node *index, T object){

	if (this->tail != index){
	
		this->current = new Node(index, object, index->next);
	}
	else{
	
		this->current = new Node(index, object);
	}
	if (this->tail != index){
	
		index->next->previous = this->current;
	}
	else{
	
		this->tail = this->current;
	}
	index->next = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList <T>::Node * LinkedList<T>::AppendFromHead(T object){

	if (this->head != 0){
	
		this->current = new Node(object, this->head);
	}
	else{
		this->current = new Node(object);
	
	}

	if (this->head != 0){
	
		this->head->previous = this->current;
	}
	else{
	
		this->tail = this->current;
	}

	this->head = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::AppendFromTail(T object){

	if (this->tail != 0){
	
		this->current = new Node(this->tail, object);

	}
	else{
	
		this->current = new Node(object);

	}

	if (this->tail != 0){
	
		this->tail->next = this->current;
	}
	else{
	
		this->head = this->current;
	}

	this->tail = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::Delete(Node *index){

	if (index == this->head && index == this->tail){
	
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	else if (index == this->head){
	
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}

	else if (index == this->tail){
	
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else{
	
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->previous;
	}

	if (index != 0){
	
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::DeleteFromHead(){

	LinkedList<T>::Node *index;
	index = this->head;
	if (this->head != this->tail){
	
		this->head->next->previous = this->head->next;
		this->head = this->head->next;
		this->current = this->head;
	}
	else{
	
		this->head = 0;
		this->current = 0;
		this->tail = 0;
	}

	if (index != 0){
	
		delete index;
		index = 0;
	}
	this->length--;
	return index;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::DeleteFromTail(){

	LinkedList<T>::Node *index;
	index = this->tail;
	if (this->tail != this->head){
	
		this->tail->previous->next = this->tail->previous;
		this->tail = this->tail->previous;
		this->current = this->tail;
	}
	else{
	
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	if (index != 0){
	
		delete index;
		index = 0;
	}

	this->length--;
	return index;
}


template <typename T>
void LinkedList <T>::DeleteAllItems(){

	LinkedList<T>::Node *index = 0;
	LinkedList<T>::Node *it = 0;

	while (index != this->tail){

		this->current = this->head->next;
		it = this->head;
		this->head = this->current;
	

	if (it != 0){

		delete it;
	}
	index = it;


	}

	this->head = 0;
	this->tail = 0;
	this->current = 0;
	this->length = 0;
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::LinearSearchUnique(void *key, int(*Compare)(void*, void*)){

	LinkedList<T>::Node *index = 0;
	LinkedList<T>::Node *previous = 0;
	LinkedList<T>::Node *it;
	it = this->head;

	while (previous != this->tail && Compare(&it->object, key) != 0){
	
		previous = it;
		it = it->next;
	}

	if (previous != this->tail){
	
		index = it;
	}

	return index;
}

template <typename T>
void LinkedList<T>::LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*Compare)(void*, void*)){

	Long i = 0;
	LinkedList<T>::Node *previous = 0;
	LinkedList<T>::Node *index = 0;
	*count = 0;

	if (*indexes != 0){
	
		delete[] *indexes;
	}
	*indexes = new Node*[this->length];
	index = this->head;
	while (previous != this->tail && index != 0){
	
		if (Compare(&(index->object), key) == 0){

			(*indexes)[i] = index;
			(*count)++;
			i++;
		
			
		}
		previous = index;
		index = index->next;
	
	}
}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::First(){

	this->current = this->head;
	return this->current;
}
template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::Previous(){

	this->current = this->current->previous;
	return this->current;
}
template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::Next(){

	this->current = this->current->next;
	return this->current;

}

template <typename T>
typename LinkedList<T>::Node * LinkedList<T>::Last(){

	this->current = this->tail;
	return this->tail;
}

template <typename T>
T& LinkedList<T>::operator[](Long index){

	Long i = 0;
	LinkedList<T>::Node *it = this->head;

	while (i < index){
	
		it = it->next;
		i++;
	}

	return it->object;
}

template <typename T>
LinkedList<T>::~LinkedList(){
	LinkedList<T>::Node *it = 0;
	LinkedList<T>::Node *index = 0;
	while (index != this->tail){
	
		this->current = this->head->next;
		it=this->head;
		this->head = this->current;

		if (it != 0){
		
			delete it;
		}
		index = it;
	}

}
//LinkedList& operator=(const LinkedList& source);
template <typename T>
LinkedList <T>& LinkedList <T>::operator=(const LinkedList& source){

	LinkedList<T>::Node *index = 0;
	LinkedList<T>::Node *it = 0;
	LinkedList<T>::Node *itr = 0;

	while (index != this->tail){
	
		this->current = this->head->next;
		it = this->head;
		this->head = this->current;
		if (it != 0){
		
			delete it;
		}
		index = it;
	}
	this->head = 0;
	this->tail = 0;
	this->current = 0;

	it = source.head;

	if (it != 0){
	
		this->head = new Node(it->object);
		index = this->head;
		this->tail = this->head;
		itr = it;
		it = it->next;
	}

	while (itr != source.tail){
	
		index->next = new Node(it->object);
		index->next->previous = index;
		index = index->next;
		this->tail = index;
		it = it->next;
		itr = itr->next;
	}

	index = this->head;
	it = source.head;
	while (it != source.current){
	
		index = index->next;
		it = it->next;
	}
	this->current = index;
	this->length = source.length;

	return *this;

}




#endif //_LINKEDLIST_H
