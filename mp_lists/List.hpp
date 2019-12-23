/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}

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
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (length_ > 0) {
    while (head_ != NULL) {
      ListNode * temp = NULL;
      if (head_->next != NULL) {
        temp = head_->next;
      } else {
        delete head_;
        break;
      }
      delete head_;
      head_ = temp;
     }
     head_ = NULL;
     tail_ = NULL;

  }
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
  ListNode * newNode = new ListNode(ndata);

  if (length_ == 0) {

    head_ = newNode;
    tail_ = newNode;
    length_ = 1;

  } else {

    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
    length_++;

  }


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
  ListNode * newNode = new ListNode(ndata);
  if (length_ == 0) {

    head_ = newNode;
    tail_ = newNode;
    length_ = 1;

  } else {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
    length_++;
  }


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
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1

  if (splitPoint >= length_) {
    return NULL;
  }
  if (splitPoint <= 0) {
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }

  tail_ = curr->prev;
  curr->prev->next = NULL;
  curr->prev = NULL;

  return curr;
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

    ListNode * curr = head_;
    ListNode * temp = NULL;
    int count = 0;

    while (curr != tail_) {
      temp = curr->next;
      if (count % 2 == 1) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        tail_->next = curr;
        curr->prev = tail_;
        curr->next = NULL;
        tail_ = curr;
      }
      count++;
      curr = temp;
    }

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
  /// @todo Graded in MP3.2
  if (startPoint == NULL || endPoint == NULL || startPoint == endPoint) {
    return;
  }
  if (startPoint != endPoint) {
		ListNode * curr  = startPoint;
		ListNode * endNext  = endPoint->next;
    ListNode * startPrev = startPoint->prev;
		ListNode * start = startPoint;
    ListNode * end = endPoint;

		while (curr != endNext) {
			swap(curr->prev, curr->next);
			curr = curr->prev;
		}

		if (startPrev == NULL) {
			end->prev = NULL;
			head_ = end;
		} else {
			startPrev->next = end;
			end->prev = startPrev;
		}

		if (endNext == NULL) {
			start->next = NULL;
			tail_ = start;
		} else {
			endNext->prev = start;
			start->next = endNext;
		}
		startPoint = end;
		endPoint = start;
	}
  return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n > 1 && length_ != 0) {
        ListNode* start = head_;
        ListNode* end   = head_;
        while(start != NULL) {
            for(int i = 1; i < n; i++)
                if (end->next != NULL) {
                    end = end->next;
                }
                reverse(start, end);
                start = end->next;
                end = start;
        }
    }
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
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  } else {

    ListNode * output = NULL;
    if (first->data < second->data) {
      output = first;
      first = first->next;
    } else {
      output = second;
      second = second->next;
    }

    ListNode * curr = output;

    while(first != NULL  && second != NULL) {
      if (first->data < second->data)
        {
            first->prev = curr;
            curr->next = first;
            first = first->next;
        }
        else
        {
            second->prev = curr;
            curr->next = second;
            second = second->next;

        }

        curr = curr->next;
    }

    if (first == NULL && second != NULL) {
  		curr->next = second;
  		second->prev = curr;
  	}
  	if (second == NULL && first != NULL) {
  		curr->next = first;
  		first->prev = curr;
  	}
    return output;
  }

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength <= 1) {
    return start;
  }

  ListNode * mid = split(start, chainLength/2);

  start = mergesort(start, chainLength/2);
  mid = mergesort(mid, chainLength/2 + chainLength%2);

  return merge(start, mid);
}
