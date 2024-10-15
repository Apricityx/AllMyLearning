#ifndef ARRAY_CONT_H
#define ARRAY_CONT_H

//**************************the following is the class delcaration*********************************//
template<class T>
class ArrayCont
{
private:
	int capacity;
	const static int initCapacity = 5;
	int size;
	T* elemArray;

	void Extend();
	bool isFull() const;

public:

	ArrayCont();

	int getSize() const;

	void Add(const T& newElem);

	~ArrayCont(); //destructor

	class Iterator
	{
		friend class ArrayCont<T>;
	private:
		T* curr;
	public:

		Iterator(T* head);
		Iterator();

		Iterator operator++(int); //post-increment

		T& operator*() const;

		bool operator==(Iterator other) const;

	};//class Iterator

	Iterator Begin() const; //position at the first item

	Iterator End() const; //position beyond the last item

};



//*****************the following is the container method implementation*******************************//
template<class T>
ArrayCont<T>::ArrayCont()
{
	size = 0;
	capacity = initCapacity;
	elemArray = new T[capacity];
}

template<class T>
int ArrayCont<T>::getSize() const
{
	return size;
}

template<class T>
bool ArrayCont<T>::isFull() const
{
	return (size == capacity);
}

template<class T>
void ArrayCont<T>::Add(const T& newElem)
{
	if (!isFull())
	{
		elemArray[size] = newElem;
		size++;
	}
	else
	{
		Extend();
		Add(newElem);
	}
}

template<class T>
ArrayCont<T>::~ArrayCont()
{
	delete[] elemArray; //garbage collection
}

template<class T>
void ArrayCont<T>::Extend()
{
	capacity = capacity * 2;
	T* temp = new T[capacity];

	for (int i = 0; i < size; i++)
		temp[i] = elemArray[i];

	delete[] elemArray;

	elemArray = temp;
}


//*****************the following is the iterator method implementation*******************************//

template<class T>
ArrayCont<T>::Iterator::Iterator()
{
	curr = NULL;
}

template<class T>
ArrayCont<T>::Iterator::Iterator(T* head)
{
	curr = head;
}

template<class T>
typename ArrayCont<T>::Iterator ArrayCont<T>::Iterator::operator++(int)
{
	Iterator temp = *this; //copy construct
	curr++;
	return temp;
}

template<class T>
T& ArrayCont<T>::Iterator::operator*() const
{
	return *curr;
}

template<class T>
bool ArrayCont<T>::Iterator::operator==(Iterator other) const
{
	return curr == other.curr;
}


//*****************the following is the two special iterators *******************************//
template<class T>
typename ArrayCont<T>::Iterator ArrayCont<T>::Begin() const
{
	return Iterator(elemArray);
}

template<class T>
typename ArrayCont<T>::Iterator ArrayCont<T>::End() const
{
	return Iterator(elemArray + size);
}

#endif