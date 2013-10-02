#include <exception>
#include <time.h>

class timespecOperatorsException : public std::exception { };

double getDouble(const timespec& ts);
bool operator==(const timespec& lhs, const timespec& rhs);
bool operator>(const timespec& lhs, const timespec& rhs);
bool operator>=(const timespec& lhs, const timespec& rhs);
timespec operator+(const timespec& lhs, const timespec& rhs);
timespec operator-(const timespec& lhs, const timespec& rhs);
timespec operator*(const unsigned& lhs, const timespec& rhs);
timespec operator/(const timespec& lhs, const unsigned& rhs);
long double operator/(const timespec& lhs, const timespec& rhs);
