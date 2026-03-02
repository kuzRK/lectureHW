#include <iostream>

template< class T >
struct BiList {
  T val;
  BiList<T> * next;
  BiList<T> * prev;
};
template< class T >
BiList<T>* add(BiList<T>* h, const T& d);

template< class T >
BiList<T>* insert(BiList<T>* h, const T& d);

template< class T >
BiList<T>* cut(BiList<T>* h);

template< class T >
BiList<T>* erase(BiList<T>* h);

template< class T >
BiList<T>* clear(BiList<T>* h, BiList<T>* e);

template< class T, class F >
F traverse(F f, BiList<T>* h, BiList<T>* e);

template< class T >
BiList<T>* add(BiList<T>* h, const T& d)
{
  BiList<T> * node = new BiList<T>{d, h, nullptr};
  if (h) {
    h->prev = node;
  }
  return node;
}
template< class T >
BiList<T>* insert(BiList<T>* h, const T& d)
{
  BiList<T>* node = add(h->next, d);
  node->prev = h;
  h->next = node;
  return node;
}
template< class T >
BiList<T>* cut(BiList<T>* h)
{
  BiList<T>* newHead = h->next;
  if (newHead) {
    newHead->prev = nullptr;
  }
  delete h;
  return newHead;
}
template< class T >
BiList<T>* erase(BiList<T>* h)
{
  h->next = cut(h->next);
  if (h->next) {
    h->next->prev = h;
  }
  return h;
}
template< class T >
BiList<T>* clear(BiList<T>* h, BiList<T>* e)
{
  while (h != e) {
    h = cut(h);
  }
  return e;
}
template< class T, class F >
F traverse(F f, BiList<T>* h, BiList<T>* e)
{
  for (; h != e; h = h->next) {
    f(h->val);
  }
  return f;
}
struct sum {
  std::string result = "";
  void operator()(char c){ result +=c; }
};
template< class T >
BiList<T>* ArrToList(const T* arr, size_t s)
{
  BiList<T>* head = add(nullptr, arr[0]);
  BiList<T>* tail = head;
  for (size_t i = 0; i < s; i++) {
    tail = insert(tail, arr[i]);
  }
  return head;
}
int main()
{
  char arr[] = {'B', 'C', 'D'};
  BiList<char>* head = ArrToList(arr,3);
  head = add(head, 'A');
  erase(head);
  sum s = traverse(sum{}, head, nullptr);
  std::cout << s.result << "\n";
  clear(head, nullptr);
}
