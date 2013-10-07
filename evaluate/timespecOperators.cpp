#include "timespecOperators.h"


// TODO: handle truncation errors on tv_nsec
// TODO: Test for overflows is actually done by GCC's -trapv-flag.
//       Do explicit tests in sourcecode instead!


const unsigned billion = 1000000000;


double getDouble(const timespec& ts) {
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}


bool operator==(const timespec& lhs, const timespec& rhs) {
  return ( (lhs.tv_sec == rhs.tv_sec) and (lhs.tv_nsec == rhs.tv_nsec) );
}


bool operator>(const timespec& lhs, const timespec& rhs) {
  return ( (lhs.tv_sec > rhs.tv_sec) or
           ((lhs.tv_sec == rhs.tv_sec) and (lhs.tv_nsec > rhs.tv_nsec)) );
}


bool operator>=(const timespec& lhs, const timespec& rhs) {
  return ( (lhs > rhs) || (lhs == rhs) );
}


timespec operator+(const timespec& lhs, const timespec& rhs) {
  timespec result;
  result.tv_sec = lhs.tv_sec + rhs.tv_sec;
  result.tv_sec += (lhs.tv_nsec + rhs.tv_nsec) / billion;
  result.tv_nsec = (lhs.tv_nsec + rhs.tv_nsec) % billion;
  return result;
}


timespec operator-(const timespec& lhs, const timespec& rhs) {

  timespecOperatorsException illegalOperation;
  if (rhs > lhs) throw illegalOperation;

  timespec result;
  if (lhs.tv_nsec < rhs.tv_nsec) {
    result.tv_sec = lhs.tv_sec - rhs.tv_sec - 1;
    result.tv_nsec = lhs.tv_nsec - rhs.tv_nsec + billion;
  } else {
    result.tv_sec = lhs.tv_sec - rhs.tv_sec;
    result.tv_nsec = lhs.tv_nsec - rhs.tv_nsec;
  }
  return result;
}


timespec operator*(const unsigned& lhs, const timespec& rhs) {
  timespec result;
  result.tv_sec = lhs * rhs.tv_sec;
  result.tv_sec += ((long long)lhs * (long long)rhs.tv_nsec) / (long long)billion;
  result.tv_nsec = ((long long)lhs * (long long)rhs.tv_nsec) % (long long)billion;
  return result;
}


timespec operator/(const timespec& lhs, const unsigned& rhs) {
  /* TODO: calculation without scaling to nanoseconds to reduce
     dependency of fundamental type implementation!!! */
  long long lhs_nsec = (long long)lhs.tv_sec * (long long)billion + (long long)lhs.tv_nsec;
  long long result_nsec = lhs_nsec / (long long)rhs;
  timespec result;
  result.tv_sec = result_nsec / billion;
  result.tv_nsec = result_nsec % billion;
  return result;
}


long double operator/(const timespec& lhs, const timespec& rhs) {
  /* TODO: calculation without scaling to nanoseconds to reduce
     dependency of fundamental type implementation!!! */
  long long lhs_nsec = (long long)lhs.tv_sec * (long long)billion + (long long)lhs.tv_nsec;
  long long rhs_nsec = (long long)rhs.tv_sec * (long long)billion + (long long)rhs.tv_nsec;
  return (long double)lhs_nsec / (long double)rhs_nsec;
}


timespec min(const timespec& lhs, const timespec& rhs) {
  return (lhs > rhs ? rhs : lhs);
}


timespec max(const timespec& lhs, const timespec& rhs) {
  return (lhs > rhs ? lhs : rhs);
}
