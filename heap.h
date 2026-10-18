#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  std::vector<T> data_;   
  size_t m_;
  PComparator c_;

  size_t bestChild(size_t idx) const;
  size_t bestChildFrom(size_t k, size_t last, size_t best) const;
  void trickleUp(size_t idx);
  void trickleDown(size_t idx);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m_(m), c_(c) {}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}

// k is the next best child, best is the best child so far
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::bestChildFrom(size_t k, size_t last, size_t best) const
{
  if(k >= last || k >= data_.size()) return best;
  if(c_(data_[k], data_[best])) best = k;
  return bestChildFrom(k + 1, last, best);
}

// best child finder

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::bestChild(size_t idx) const
{
  size_t first = m_ * idx + 1;
  if(first >= data_.size()) return data_.size();   // no children
  return bestChildFrom(first + 1, first + m_, first);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t idx)
{
  if(idx == 0) return;
  size_t parent = (idx - 1) / m_;
  if(c_(data_[idx], data_[parent])){
    std::swap(data_[idx], data_[parent]);
    trickleUp(parent);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t idx)
{
  size_t best = bestChild(idx);
  if(best < data_.size() && c_(data_[best], data_[idx])){
    std::swap(data_[best], data_[idx]);
    trickleDown(best);
  }
}





// push func
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size()-1);
}




// We will start top() you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_[0];

}


// We will start pop() you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }

  data_[0] = data_.back();
  data_.pop_back();

  trickleDown(0);
}



#endif

