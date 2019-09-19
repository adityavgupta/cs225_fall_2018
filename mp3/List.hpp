/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  // @todo Graded in MP3.1
_destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
	while(head_ != tail_) {
		head_ = head_->next;
		delete head_->prev;
	}
	//delete tail_->prev;
	delete tail_;

	length_ = 0;
	head_ = nullptr;
	tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* front = new ListNode(ndata);
	if(head_ == nullptr) {
		head_ = front;
		tail_ = front;
	}
	else {
		head_->prev = front;
		front->next = head_;
		front->prev = nullptr;
		head_ = front;
	}
	++length_;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
	ListNode* back = new ListNode(ndata);
	if(tail_ == nullptr) {
		tail_ = back;
		head_ = back;
	}
	else {
		tail_->next = back;
		back->next = nullptr;
		back->prev = tail_;
		tail_ = back;
	}
	length_++;

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1

ListNode* s = startPoint;
ListNode* n;

/*while(s != endPoint && s != nullptr) {
	std::swap(s->prev, s->next);
	s = s->prev;
}

std::swap(endPoint->prev, endPoint->next);
std::swap(endPoint->prev, startPoint->next);
std::swap(startPoint, endPoint);*/
if(startPoint == endPoint)
	return;

 ListNode* current = startPoint;
 ListNode* currend = endPoint->next;
 ListNode* temp = nullptr;

  while(current != currend) {
	  temp = current->prev;
	  current->prev = current->next;
	  current->next = temp;
	  current = current->prev;
  }
  temp = endPoint;

  ListNode* temp2 = endPoint->prev;
  endPoint->prev = startPoint->next;
  startPoint->next = temp2;

  current = startPoint;
  startPoint = endPoint;
  endPoint = current;
 }
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode* s = head_;
  ListNode* e = tail_;

  if(length_ <= 1 || n == 1 || head_ == nullptr){
	  return;
  }

 while(s && e) {
	  e = s;
	  for(int i = 0; i < n; i++) {
		  if(e != nullptr)
			  e  = e->next;
	  }
	  if(s == head_) {
		  if(e == nullptr) {
			  reverse(head_, tail_);
		  }
		  else
			  reverse(head_, e->prev);
	  } else {
		  if(e == nullptr)
			  reverse(s->prev->next, tail_);
		  else
			  reverse(s->prev->next, e->prev);
		}
	  s = e;
	}
}
/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
	if(head_ == NULL || tail_ == NULL || length_ == 0)
		return;

	ListNode* t = head_;
	ListNode* e = tail_;
	ListNode* t_rem;
	ListNode* t2;

	while(t->next != e) {
		t_rem = t->next;
		t2 = t_rem->next;

		t->next = t2;
		t2->prev = t;

		e->next = t_rem;
		t_rem->prev = e;
		t_rem->next = NULL;

		e = t_rem;
		t = t->next;
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(start == NULL)
	  return NULL;

 /* if(splitPoint == 1)
	  return start;*/

  ListNode* c = start;
  ListNode* t;
  int ct = 0;

  while(ct < splitPoint) {
	  c = c->next;
	  ct++;
  }

  if(c) {
	  t = c->prev;
	  c->prev = NULL;
	  t->next = NULL;
  }
  return c;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
	if(!first && second)
		return second;
	if(!second && first)
		return first;
	if(!second && !first)
		return NULL;


	ListNode* currentF = first;
	ListNode* currentS = second;
	ListNode* newHead;
	ListNode* newNext;

	if(first->data < second->data) {
		newHead = first;
		currentF = currentF->next;
	}

	else {
		newHead = second;
		currentS = currentS->next;
	}

	newNext = newHead;

	while(currentF && currentS) {

		if(currentF->data < currentS->data) {
			newNext->next = currentF;
			currentF->prev = newNext;
			newNext = currentF;
			currentF = currentF->next;
		}

		else {
			newNext->next = currentS;
			currentS->prev = newNext;
			newNext = currentS;
			currentS = currentS->next;
		}
	}

	while(currentS) {
		newNext->next = currentS;
		currentS->prev = newNext;
		newNext = currentS;
		currentS = currentS->next;
	}

	while(currentF) {
		newNext->next = currentF;
		currentF->prev = newNext;
		newNext = currentF;
		currentF = currentF->next;
	}

	return newHead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1)
	  return start;

  ListNode* other = split(start, chainLength/2);
  //ListNode* first = start;
//	std::cout << "here" << std::endl;
  start = mergesort(start, chainLength/2);
  other = mergesort(other, chainLength - chainLength/2);

  return merge(start, other);
}
