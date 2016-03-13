/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Brandon Smith
 * @date 1/27/16
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

#include<iostream>

template <class T>
class DoublyLinkedList 
{
 public:
   DoublyLinkedList();
   ~DoublyLinkedList();
   void append(T* data);
   bool empty() const { return (head == nullptr); }
   T* remove();
   T* first();
   T* next();

 private:
   class Node 
   {
    public:
      Node();
      Node(T* data);
      Node* next;
      Node* prev;
      T* data;
   };
   Node* head;
   Node* tail;
   Node* current;
};

/*
 * @brief  Node constructor.
 */

template <class T>
DoublyLinkedList<T>::Node::Node(T* data)
{
  this->data = data;
  next = nullptr;
  prev = nullptr;
  data = nullptr;
}

/**
 * @brief Default Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node() 
{
  next = nullptr;
  prev = nullptr;
  data = nullptr;
}

/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{

  head = nullptr;
  tail = nullptr;
  current = nullptr;
}

/**
 * @brief   DoublyLinkedList destructor.
 */
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  
  current = head;

  while(current != nullptr)
  {
    Node* temp = current;
    current = current->next;
    delete temp->data;
    delete temp;
  }
}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data)
{
  if(head == nullptr)
  { 
    head = new Node(data);
    tail = head;
    current = head;
  }
  else 
  { 
    current = tail;
    tail->next = new Node(data);
    tail = tail->next;
    tail->prev = current;
    current = tail;
  }
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first()
{
  current = head;
  if(current == nullptr)
  {
    return nullptr;
  }
  return current->data;
}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next()
{
  if(current == nullptr || current->next == nullptr)
  {
    return nullptr;
  }
  current = current->next;
  return current->data;
}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove() {

  Node* temp = current;

  if(current == nullptr)
  {
    return nullptr;
  }

  if(current->prev != nullptr)
  {
    current->prev->next = current->next;
  }
  else
  {
    head = current->next;
  }

  if(current->next != nullptr)
  {
    current->next->prev = current->prev;
  }
  else
  {
    tail = current->prev;
  }

  current = temp->next;
  delete temp;

  if(current == nullptr) //if node removed was tail node, return null
  {
    return nullptr;
  }

  return current->data;
}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
