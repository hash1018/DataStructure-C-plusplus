//Array.h

#ifndef _ARRAY_H
#define _ARRAY_H
#include <memory.h>
typedef signed long int Long;
template <typename T>

class Array {

public:
	Array(Long capacity = 100);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);

	/*
	1. call this function for putting element into Array when the length of array is same as the capacity of array.
	2. variable object is to be inserted into Array, variable size is to add capacity of Array.
	*/
	Long AppendFromRear(T object, Long size);

	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	//2017.03.30 새거 추가
	void EmptyArray();

	//Delete all elements and Reallocate arrays with new size of capacity.
	void EmptyArray(Long capacity);

	//variable capacity must be higher than current capacity.
	void ResizeCapacity(Long capacity);


	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*Compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*Compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*Compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*Compare)(void*, void*));
	void BubbleSort(int(*Compare)(void*, void*));
	void SelectionSort(int(*Compare)(void*, void*));
	void InsertSort(int(*Compare)(void*, void*));
	void MergeSort(const Array& one, const Array& other, int(*Compare)(void*, void*));
	Long GetCapacity() const;
	Long GetLength() const;
	Array& operator =(const Array& source);
	T& operator [](Long index);
	T* operator +(Long index);
	T& GetAt(Long index);

private:
	T(*front);
	Long capacity;
	Long length;


};

template <typename T>
T& Array<T>::GetAt(Long index) {

	return this->front[index];
}


template <typename T>
Array<T>::Array(Long capacity) {

	this->front = new T[capacity];
	this->length = 0;
	this->capacity = capacity;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& source) {

	if (this->front != 0) {

		delete[]this->front;
		this->front = 0;
	}

	this->front = new T[source.capacity];
	this->capacity = source.capacity;

	//Long i = 0;
	/*                                    //Original Flow Chart Version.
	while (i < source.length){

	this->front[i] = source.front[i];
	i++;
	}
	*/

	//Faster Way applied for C/C++
	memcpy(this->front + 0, source.front + 0, sizeof(T)*source.length);


	this->length = source.length;
	return *this;

}

template <typename T>
T& Array<T>::operator[](Long index) {

	return this->front[index];
}

template <typename T>
T* Array<T>:: operator+(Long index) {

	return this->front + index;
}

template <typename T>
Array<T>::Array(const Array& source) {

	this->front = new T[source.capacity];
	this->capacity = source.capacity;

	/*
	Long i = 0;                             //Original Flow Char Version.
	while (i < source.length){

	this->front[i] = source.front[i];
	i++;
	}
	*/

	//Faster Way applied for C/C++
	memcpy(this->front + 0, source.front + 0, sizeof(T)*source.length);


	this->length = source.length;
}

template <typename T>
Array<T>::~Array() {

	if (this->front != 0) {

		delete[]this->front;
	}
}

template <typename T>
Long Array<T>::Store(Long index, T object) {

	this->front[index] = object;
	this->length++;
	return index;
}

template <typename T>
Long Array<T>::Insert(Long index, T object) {

	T(*temp);
	//Long i = 0;  //Origianl Flow Chart Version.
	//Long j = 0;

	temp = new T[this->capacity + 1];


	/*                                  //Origianl Flow Chart Version.
	while (i < index){

	temp[i] = this->front[j];
	j++;
	i++;
	}

	i++;

	while (j < this->length){

	temp[i] = this->front[j];
	i++;
	j++;
	}
	*/

	//Faster Way applied for C/C++
	memcpy(temp + 0, this->front + 0, sizeof(T)*index);
	memcpy(temp + (index + 1), this->front + index, sizeof(T)*(this->length - index));

	if (this->front != 0) {

		delete[]this->front;
	}

	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}


template <typename T>
Long Array<T>::AppendFromFront(T object) {

	Long index = 0;
	T(*temp);
	//Long i = 0;
	temp = new T[this->capacity + 1];

	/*    Original Flow Chart Version.
	while (i < this->length){

	temp[i + 1] = this->front[i];
	i++;
	}
	*/

	//Faster Way applied for C/C++
	memcpy(temp + 1, this->front + 0, sizeof(T)*this->length);

	if (this->front != 0) {

		delete[]this->front;
	}

	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;
	return index;
}

template <typename T>
Long Array<T>::AppendFromRear(T object) {

	//Long index = 0;

	Long index = this->length;
	T(*temp);
	temp = new T[this->capacity + 1];

	/*  Original Flow Chart Version.
	while (index < this->length){

	temp[index] = this->front[index];
	index++;
	}
	*/

	//Faster Way applied for C/C++
	memcpy(temp + 0, this->front + 0, sizeof(T)*this->length);


	if (this->front != 0) {

		delete[]this->front;
	}

	this->front = temp;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;
	return index;
}


/*
1. call this function for putting element into Array when the length of array is same as the capacity of array.
2. variable object is to be inserted into Array, variable size is to add capacity of Array.
*/
template <typename T>
Long Array<T>::AppendFromRear(T object, Long size) {

	Long index = this->length;
	T(*temp);
	temp = new T[this->capacity + size];

	memcpy(temp + 0, this->front + 0, sizeof(T)*this->length);


	if (this->front != 0) {

		delete[]this->front;
	}

	this->front = temp;
	this->capacity += size;
	this->front[index] = object;
	this->length++;
	return index;
}
template <typename T>
Long Array<T>::Delete(Long index) {

	T(*temp) = 0;
	//Long i = 0;
	//Long j = 0;
	if (this->capacity > 1) {

		temp = new T[this->capacity - 1];

		//Added Here
		//Faster Way applied for C/C++
		memcpy(temp + 0, this->front + 0, sizeof(T)*index);
		memcpy(temp + index, this->front + (index + 1), sizeof(T)*(this->length - index - 1));
	}
	/*
	while (i < this->length){

	if (i != index){

	temp[j] = this->front[i];
	j++;
	}
	i++;
	}
	*/
	if (this->front != 0) {

		delete[] this->front;
		this->front = 0;

	}

	if (this->capacity>1) {

		this->front = temp;
	}

	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template<typename T>
Long Array<T>::DeleteFromFront() {

	Long index;
	//Long i = 1;
	T(*temp) = 0;
	if (this->capacity > 1) {

		temp = new T[this->capacity - 1];

		//Added Here
		//Faster Way applied for C/C++
		memcpy(temp + 0, this->front + 1, sizeof(T)*(this->length - 1));
	}

	/*  //Original Flow Chart Version.
	while (i < this->length){

	temp[i - 1] = this->front[i];
	i++;
	}
	*/

	if (this->front != 0) {

		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity>1) {

		this->front = temp;
	}

	this->length--;
	this->capacity--;
	index = -1;
	return index;
}

template <typename T>
Long Array<T>::DeleteFromRear() {

	Long index = -1;
	T(*temp) = 0;
	//Long i = 0;
	if (this->capacity > 1) {

		temp = new T[this->capacity - 1];

		//Added Here
		memcpy(temp + 0, this->front + 0, sizeof(T)*(this->length - 1));
	}

	/*  Original Flow Chart Version.
	while (i < this->capacity - 1){

	temp[i] = this->front[i];
	i++;
	}
	*/

	if (this->front != 0) {

		delete[]this->front;
		this->front = 0;
	}

	if (this->capacity>1) {

		this->front = temp;
	}

	this->capacity--;
	this->length--;
	return index;
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*Compare)(void*, void*)) {

	Long index = -1;
	Long i = 0;
	while (i < this->length && Compare(this->front + i, key) != 0) {

		i++;
	}
	if (i < this->length) {

		index = i;
	}

	return index;
}

template <typename T>
void Array<T>::Clear() {

	if (this->front != 0) {

		delete[]this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}

template <typename T>
void Array<T>::EmptyArray() {

	if (this->front != 0) {

		delete[]this->front;
		this->front = new T[this->capacity];
	}
	this->length = 0;
}


//Delete all elements and Reallocate arrays with new size of capacity.
template <typename T>
void Array<T>::EmptyArray(Long capacity) {

	if (this->front != 0) {
	
		delete[]this->front;
		this->front = new T[capacity];
	}
	this->capacity = capacity;
	this->length = 0;
}


//variable capacity must be higher than current capacity.
//compared to function "EmptyArray" , this function doesn't remove current elements in arrays.
template <typename T>
void Array<T>::ResizeCapacity(Long capacity) {

	if (capacity <= this->capacity)
		return;

	T(*temp) = 0;
	temp = new T[capacity];

	if (this->front != 0) {
		memcpy(temp + 0, this->front + 0, sizeof(T)*this->length);
		delete[] this->front;
	}

	this->front = temp;
	this->capacity = capacity;
}

template <typename T>
Long Array<T>::Modify(Long index, T object) {

	this->front[index] = object;
	return index;
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*Compare)(void*, void*)) {

	Long min = 0;
	Long mid;
	Long max;
	Long index = -1;

	max = this->length - 1;

	mid = (min + max) / 2;
	while (min <= max&& Compare(this->front + mid, key) != 0) {

		if (Compare(this->front + mid, key) > 0) {

			max = mid - 1;

		}
		else {

			min = mid + 1;
		}
		mid = (max + min) / 2;
	}

	if (min <= max) {

		index = mid;
	}

	return index;
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*Compare)(void*, void*)) {
	*count = 0;
	Long i = 0;
	Long j = 0;
	*indexes = new Long[this->length];

	while (i < this->length) {

		if (Compare(this->front + i, key) == 0) {

			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*Compare)(void*, void*)) {

	Long min = 0;
	Long mid;
	Long max;
	Long i = 0;
	Long j = 0;
	*indexes = 0;

	max = this->length - 1;
	mid = (min + max) / 2;
	while (min <= max && Compare(this->front + mid, key) != 0) {

		if (Compare(this->front + mid, key) > 0) {

			max = mid - 1;
		}
		else {

			min = mid + 1;
		}
		mid = (min + max) / 2;
	}
	i = mid - 1;
	while (i >= 0 && Compare(this->front + i, key) == 0) {

		i--;
	}
	i++;
	mid = i;
	while (i < this->length && Compare(this->front + i, key) == 0) {

		(*count)++;
		i++;
	}

	if ((*count)>0) {

		*indexes = new Long[(*count)];

	}
	while (j < (*count)) {

		(*indexes)[j] = mid;
		mid++;
		j++;
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*Compare)(void*, void*)) {

	T temp;
	Long i = 0;
	Long j;
	while (i < this->length - 1) {

		j = 0;
		while (j < this->length - i - 1) {

			if (Compare(this->front + j, this->front + (j + 1))>0) {

				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*Compare)(void*, void*)) {

	T temp;
	Long i = 0;
	Long j;
	Long key;

	while (i < this->length - 1) {

		key = i;
		j = i + 1;
		while (j < this->length) {

			if (Compare(this->front + key, this->front + j)>0) {

				key = j;
			}
			j++;
		}

		if (i != key) {

			temp = this->front[key];
			this->front[key] = this->front[i];
			this->front[i] = temp;
		}
		i++;
	}
}

template <typename T>
void Array<T>::InsertSort(int(*Compare)(void*, void*)) {

	T key;
	Long index;
	Long location;
	Long i = 1;
	Long j;

	while (i < this->length) {

		key = this->front[i];
		index = i;
		j = 0;
		while (Compare(this->front + j, &key) < 0) {

			j++;
		}

		location = j;
		while (location < index) {

			this->front[index] = this->front[index - 1];
			index--;
		}
		this->front[location] = key;
		i++;
	}
}

template <typename T>
void Array<T>::MergeSort(const Array& one, const Array& other, int(*Compare)(void*, void*)) {

	Long index = 0;
	Long i = 0;
	Long j = 0;
	if (this->front != 0) {

		delete[]this->front;
	}

	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;
	this->length = 0;
	while (i < one.length && j < other.length) {

		if (Compare(one.front + i, other.front + j) < 0) {

			this->front[index] = one.front[i];
			index++;
			this->length++;
			i++;
		}
		else {

			this->front[index] = other.front[j];
			index++;
			this->length++;
			j++;
		}
	}

	while (i < one.length) {

		this->front[index] = one.front[i];
		index++;
		this->length++;
		i++;
	}

	while (j < other.length) {

		this->front[index] = other.front[j];
		index++;
		this->length++;
		j++;
	}


}
template<typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;



}
template <typename T>
inline Long Array<T>::GetLength() const {

	return this->length;
}


#endif //_ARRAY_H