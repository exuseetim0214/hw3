#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
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
  int m_;
  PComparator comp_;



};

// Add implementation of member functions here
//constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
    : m_(m), comp_(c)
{
  if (m_ <2) {
    throw std::invalid_argument("Heap brancking factor need to be greater or equal to 2");
  }
}

//destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

//empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return data_.empty();
}

//size
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return data_.size();
}

//push
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  data_.push_back(item);

  size_t child = data_.size() - 1;
  
  while(child >0){
    size_t parent = (child-1) / m_;
    if(comp_(data_[child], data_[parent])){
      std::swap(data_[child], data_[parent]);
      child = parent;
    }
    else{
      break;
    }
  }

}
// We will start top() for you to handle the case of 
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
      throw std::underflow_error("Heap underflow: top from empty heap");

  }
  return data_.front();
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element



}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap underflow: pop from empty heap");

  }
  data_[0]= data_.back();
  data_.pop_back();

  size_t index =0;
  while(true){
    size_t best = index;
    for(int i = 1; i <= m_; i++){
      size_t child = m_ * index + i;
      if(child < data_.size() && comp_(data_[child], data_[best])){
        best = child;
      }
    }

    if (best == index){
      break;
    }
    std::swap(data_[index], data_[best]);
    index = best;
  }


}



#endif

