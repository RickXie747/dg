#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:

 //Constructors

  //Default Constructor
  explicit EuclideanVector(int a) noexcept;

  EuclideanVector(int a, double b) noexcept;

  EuclideanVector(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end) noexcept;

  //Copy Constructor
  EuclideanVector(const EuclideanVector& source) noexcept;

  //Move Constructor
  EuclideanVector(EuclideanVector&& o) noexcept;

//Destructor
  ~EuclideanVector() = default;


//Operations

  //Copy Assignment
  EuclideanVector& operator=(const EuclideanVector& rhs) noexcept;

  //Move Assignment
  EuclideanVector& operator=(EuclideanVector&& o) noexcept;

  //Subscript
  double& operator[] (int i) noexcept;

  double operator[] (int i) const noexcept;

  //Addition
  EuclideanVector& operator+=(const EuclideanVector& rhs);

  //Subtraction
  EuclideanVector& operator-=(const EuclideanVector& rhs);

  //Multiplication
  EuclideanVector& operator*=(const double rhs) noexcept;

  //Division
  EuclideanVector& operator/=(const double rhs);

  //Vector Type Conversion
  explicit operator std::vector<double>() noexcept;

  //List Type Conversion
  explicit operator std::list<double>() noexcept;

//Methods
  double at(int i) const;

  double& at(int i);

  int GetNumDimensions() const noexcept;

  double GetEuclideanNorm();
  
  EuclideanVector CreateUnitVector();

//Friends

  //Equal
  friend bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept{
    if (lhs.dimensions_ != rhs.dimensions_) {
      return false;
    }
    return std::equal(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, rhs.magnitudes_.get());
  }

  //Not Equal
  friend bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept{
    if (lhs.dimensions_ != rhs.dimensions_) {
      return true;
    }
    return !(std::equal(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, rhs.magnitudes_.get()));
  }

  //Addition
  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    if (lhs.dimensions_ != rhs.dimensions_)
      throw EuclideanVectorError("Dimensions of LHS(" +  std::to_string(lhs.dimensions_)+ 
                                  ") and RHS(" + std::to_string(rhs.dimensions_)
                                   +") do not match");
    EuclideanVector result(lhs.dimensions_);
    std::transform(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, 
                  rhs.magnitudes_.get(),
                  result.magnitudes_.get(),
                  [] (double a, double b) {return a + b;});
    return result;
  }

  //Subtraction
  friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    if (lhs.dimensions_ != rhs.dimensions_)
      throw EuclideanVectorError("Dimensions of LHS(" +  std::to_string(lhs.dimensions_)+ 
                                  ") and RHS(" + std::to_string(rhs.dimensions_)
                                   +") do not match");
    EuclideanVector result(lhs.dimensions_);
    std::transform(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, 
                  rhs.magnitudes_.get(),
                  result.magnitudes_.get(),
                  [] (double a, double b) {return a - b;});
    return result;
  }

  //Multiplication
  friend 	double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept{
    return std::inner_product(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, 
                              rhs.magnitudes_.get(), 0.0);
  }

  //Multiply
  friend EuclideanVector operator*(const EuclideanVector& lhs, double rhs) noexcept{
    EuclideanVector result(lhs.dimensions_);
    std::transform(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, 
                  result.magnitudes_.get(),
                  [&] (double a) {return a * rhs;});
    return result;
  }

  friend EuclideanVector operator*(double lhs , const EuclideanVector& rhs) noexcept{
    EuclideanVector result(rhs.dimensions_);
    std::transform(rhs.magnitudes_.get(), rhs.magnitudes_.get() + rhs.dimensions_, 
                  result.magnitudes_.get(),
                  [&] (double a) {return a * lhs;});
    return result;
  }

  //Divide
  friend EuclideanVector operator/(const EuclideanVector& lhs, double rhs) {
  if (rhs == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
    EuclideanVector result(lhs.dimensions_);
    std::transform(lhs.magnitudes_.get(), lhs.magnitudes_.get() + lhs.dimensions_, 
                  result.magnitudes_.get(),
                  [&] (double a) {return a / rhs;});
    return result;
  }

  //Output Stream
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept{
    os << '[';
    for (int i = 0; i < v.dimensions_; i++) {
      os << v.magnitudes_[i]; 
      if (i < v.dimensions_ - 1) {
        os << " ";
      }
    }
    return os << ']';
  }

 private:
  std::unique_ptr<double[]> magnitudes_;
  int dimensions_ = 0;
  
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
