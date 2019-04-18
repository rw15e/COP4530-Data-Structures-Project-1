// Assignment 1 COP4530
// Ryan Winter
// 9/28/17 (Fall 2017)

template <class T>
void TList<T>::setEmpty(){ // sets list to empty
	size = 0;
	first = nullptr;
	last = nullptr;
}

template <class T>
TList<T>::TList(){ // default constructor (create empty linked list)
	setEmpty(); // set list to empty
}

template <class T>
TList<T>::TList(T val, int num){ // create list that has num copies of val
	setEmpty();	// set list to empty at first
	
	for(int i = 0; i < num; i++)
		InsertFront(val);
}

template <class T>
TList<T>::~TList(){  // destructor
	auto iter = GetIterator();
	
	for(int i = 1; i < size; i++){ // loop through the list and delete backwards(so we clean them all up)
		iter.Next();
		delete iter.ptr->prev;
		if(i == size)
			delete iter.ptr; // dont forget final Node!
	}
}

template <class T>
TList<T>::TList(const TList& L){  // copy contructor
	auto iter = L.GetIterator();
	setEmpty();	

	for(int i = 0; i < L.GetSize(); i++){ // loop through whole list iterating through and inserting at back (to copy contents)
		InsertBack(iter.GetData());
		iter.Next();
	}
}

template <class T>
TList<T> TList<T>::operator=(const TList& L){ // copy assignment operator overload
	Clear(); // clear the list before copying
	auto iter = L.GetIterator();
	for(int i = 0; i < L.GetSize(); i++){ // loop through whole list iterating through and inserting at back
		InsertBack(iter.GetData());
		iter.Next();
	}
	return *this;
}

template <class T>
TList<T>::TList(TList && L){	// move constructor
	first = L.first; // copy all data to corresponding variables
	last = L.last;
	size = L.size;
}

template <class T>
TList<T> TList<T>::operator=(TList && L){ // move assignment operator
	int temp = 0;
	Node<T> *tPtr = first;
	first = L.first; // move value of L.first
	L.first = tPtr;    // switch pointers for "first"
	tPtr = last;  // switch the ptrs for "last"
	last = L.last;
	L.last = tPtr;
	temp = size;  // copy the list sizes to temp variable
	size = L.size;
	L.size = temp;
	return *this;
}

template <class T>
bool TList<T>::IsEmpty() const{   // check if list is empty (return true if it is, false otherwise)
	if(size == 0) 
		return true;
	return false;
}

template <class T>
void TList<T>::Clear(){ 	// clear list
	for(int i = 0; i < size; i++)
		RemoveFront;
	setEmpty(); // makes sure list is all set to empty
}

template <class T>
int TList<T>::GetSize() const{ // return size of list
	return size;
}

template <class T>
void TList<T>::InsertFront(const T& d){ // insert d as first element
	Node<T> *n = new Node<T>(d);
	
	if(size == 0){
		first = n;
		last = n;
		size++;
	}
	else{
		n->next = first;
		first->prev = n;
		first = n;
		size++;
	}
}

template <class T>
void TList<T>::InsertBack(const T& d){	// insert d as last element
	Node<T> *n = new Node<T>(d);

	if(size == 0){
		first = n;
		last = n;
		size++;
	}
	else{
		n->prev = last;
		last->next = n;
		last = n;
		size++;
	}
}

template <class T>
void TList<T>::RemoveFront(){ // remove first item in list
	if(size == 1){  // if size == 1 we can just delete it and reset its values 
		delete first; 
		setEmpty(); // set default (empty list) values
	}
	if(size > 1){   // if size > 1 we have to shift pointers around and remove item
		Node<T> *tPtr = first->next;
		tPtr->prev = 0;
		delete first;
		first = tPtr; // reset ptrs new value
		size--;  // decrement the size of list
	}
}

template <class T>
void TList<T>::RemoveBack(){ // remove last item in list
	if(size == 1){  // if size of list == 1 we can just delete it and reset its values 
		delete last; 
		setEmpty(); // set default (empty list) values
	}
	if(size > 1){   // if size of list > 1 we have to shift pointers around and remove item
		Node<T> *tPtr = last->prev;
		tPtr->next = 0;
		delete last;
		last = tPtr; // reset ptrs new value
		size--;  // decrement the size of list
	}
}

template <class T>
T& TList<T>::GetFirst() const{  // return first element
	return first->data;
}

template <class T>
T& TList<T>::GetLast() const{  // return last element
	return last->data;
}

template <class T>
TListIterator<T> TList<T>::GetIterator() const{  // return iterator to first element
	TListIterator<T> iter;
	iter.ptr = first;
	return iter;
}

template <class T>
TListIterator<T> TList<T>::GetIteratorEnd() const{ // return iterator to last element
	TListIterator<T> iter;
	iter.ptr = last;
	return iter;
}

template <class T>
void TList<T>::Insert(TListIterator<T> pos, const T& d){
	Node<T> *prevNode = nullptr;
	Node<T> *tempNode = new Node<T>(d);
	if(pos.HasPrevious() == true) // if there is a previous node, copy its contents to prevNode
		prevNode = pos.ptr->prev;
	else
		prevNode = nullptr;

	tempNode->next = pos.ptr;  // switch pointers
	pos.ptr->prev = tempNode;
	
	if(prevNode == nullptr)  // if this is first of list, set properly
		first = tempNode; 
	else{
		prevNode->next = tempNode;
		tempNode->prev = prevNode;	
	}
	size++;
}

template <class T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos){ // remove data at pos
	Node<T> *currentP = pos.ptr;
	Node<T> *prevP = currentP->prev;
	Node<T> *nextP = currentP->next;
	pos.Next(); // iterate to next and swap pointers so it can be returned and current can be deleted
	prevP->next = nextP;
	nextP->prev = prevP;
    delete currentP;
    size--;
	return pos;
}

template <class T>
void TList<T>::Print(std::ostream& os, char delim) const{
	auto iter = this->GetIterator();

	for(int i = 0; i < size; i++){  // loop through whole list and send to output stream iterating through list inside of loop
		os << iter.GetData() << delim;
		iter.Next();
	}
}

template <class T>
TListIterator<T>::TListIterator(){	 // default constructor
	ptr = nullptr; // set pointer to the nullptr
}

template <class T>
bool TListIterator<T>::HasNext() const{ // is there a next item?
	if(ptr->next == nullptr)
		return false;
	else
		return true;
}

template <class T>
bool TListIterator<T>::HasPrevious() const{  // is there a previous item?
	if(ptr->prev == nullptr)
		return false;
	else
		return true;
}

template <class T>
TListIterator<T> TListIterator<T>::Next(){ // move to next
	if(HasNext() == true) 
		ptr = ptr->next;
	return *this;
}

template <class T>
TListIterator<T> TListIterator<T>::Previous(){  // move to previous
	if(HasPrevious() == true) 
		ptr = ptr->prev;
	return *this;
}

template <class T>
T& TListIterator<T>::GetData() const{  // return data element of current node
	return ptr->data;
}