#include "LargeInt.h"
#include <string>         
#include <algorithm>      

using namespace bigint;

LargeInt::LargeInt()
{
	number.push_back(0);
	sign = true;
}

LargeInt::LargeInt(std::string num) {
	int didits_pos = isdigit(num.at(0)) ? 0 : 1;
	sign = num.at(0) == '-' ? false : true;

	for (unsigned int i = didits_pos; i < num.length(); i++)
		number.push_back(num.at(i) - '0');

	deleteZero();
}

LargeInt::LargeInt(uint32_t num) : LargeInt(std::to_string(num)) {}


void LargeInt::deleteZero() {
	while (number.size() > 1 && number.at(0) == 0)
		number.erase(number.begin(), number.begin() + 1);
}


std::string LargeInt::num_to_str() const {
	std::string str;
	if (!sign)
		str += "-";
	for (unsigned int i = 0; i < number.size(); i++)
		str += std::to_string(number.at(i));
	return str;
}


bool LargeInt::operator>(const LargeInt& rhs) const {
	if (sign == true && rhs.sign == false)
		return true;
	if (sign == false && rhs.sign == true)
		return false;

	if (number.size() > rhs.number.size())
		return sign;
	if (number.size() < rhs.number.size())
		return !sign;

	for (size_t i = 0; i < number.size(); i++) {
		if (number.at(i) > rhs.number.at(i))
			return sign;
		if (number.at(i) < rhs.number.at(i))
			return !sign;
	}
	return false;
}

bool LargeInt::operator<(const LargeInt& rhs) const {
	return false == (*this == rhs) && false == (*this > rhs);
}

bool LargeInt::operator==(const LargeInt& rhs) const {
	return (sign == rhs.sign && number == rhs.number);
}

LargeInt LargeInt::abs() const {
	LargeInt a(*this);
	a.sign = true;
	return a;
}
int LargeInt::digit(int index) const {
	return index >= 0 ? number[index] : 0;
}


   std::ostream& bigint::operator <<(std::ostream& ostream, const bigint::LargeInt& number) 
   {
   	return ostream<<number.num_to_str();
   }



const LargeInt LargeInt::operator+(const LargeInt& rhs) const
{
	LargeInt sum;
	if (number.at(0) == 0 && rhs.number.at(0) == 0)
		return sum;
	if (sign == rhs.sign) {
		sum.number.clear();
		sum.sign = sign;
		unsigned int cf = 0;                       //carry flag
		int index1 = number.size() - 1;
		int index2 = rhs.number.size() - 1;
		while (index1 >= 0 || index2 >= 0) {
			auto digitsum = this->digit(index1) + rhs.digit(index2) + cf;

			cf = digitsum / 10;
			digitsum %= 10;

			sum.number.push_back(digitsum);
			index1--;
			index2--;
		}
		if (cf != 0)
			sum.number.push_back(cf);
		std::reverse(sum.number.begin(), sum.number.end());
	}
	else {
		if (this->abs() > rhs.abs()) {
			sum = this->abs() - rhs.abs();
			sum.sign = sign;
		}
		else {
			sum = rhs.abs() - this->abs();
			sum.sign = rhs.sign;
		}
	}
	return sum;
}

const LargeInt LargeInt::operator-(const LargeInt& rhs) const
{
	LargeInt sub;
	if (number.at(0) == 0 && rhs.number.at(0) == 0)
		return sub;
	if (sign == rhs.sign) {
		sub.number.clear();
		sub.sign = sign;
		unsigned int cf = 0;  //carry flag
		int index1 = number.size() - 1;
		int index2 = rhs.number.size() - 1;
		while (index1 >= 0 || index2 >= 0) {
			if(this->abs() < rhs.abs()) {
				auto digitsum = (rhs.digit(index2) + 10) - (this->digit(index1) + cf);
				cf = (digitsum >= 10) ? 0 : 1;
		        digitsum %= 10;
		  		sub.number.push_back(digitsum);
			}
			else {
				auto digitsum = (this->digit(index1) + 10) - (rhs.digit(index2) + cf);
				cf = (digitsum >= 10) ? 0 : 1;
				digitsum %= 10;
				sub.number.push_back(digitsum);
			}
			index1--;
			index2--;
		}
		if (cf != 0)
			sub.number.push_back(cf);
		std::reverse(sub.number.begin(), sub.number.end());

		//sign
		if(sign==false && rhs.sign==false && this->abs() == rhs.abs())
			sub.sign=false;
		if(sign==true && rhs.sign==true && this->abs() == rhs.abs())
			return sub=0;
		if(sign==false && rhs.sign==false)
			sub.sign=(this->abs() < rhs.abs()) ? true : false;
		if(sign==true && rhs.sign==true)
			sub.sign=(this->abs() > rhs.abs()) ? true : false;
		}

	else {
			sub = this->abs() + rhs.abs();
			sub.sign = (rhs.sign==false) ? true : false;
	}
	sub.deleteZero();
	return sub;
}


LargeInt LargeInt::digitMultiply(uint32_t digit) const {
	LargeInt result;
	result.number.clear();
	result.sign = true;
	unsigned int cf = 0;                                           //carry flag
	for (int i = number.size() - 1; i >= 0; i--) {
		unsigned int digitmult = number.at(i) * digit + cf;
		if (digitmult > 9) {
			cf = digitmult / 10;
			digitmult %= 10;
		}
		else
			cf = 0;
		result.number.push_back(digitmult);
	}
	if (cf != 0)
		result.number.push_back(cf);
	std::reverse(result.number.begin(), result.number.end());
	return result;
}

const LargeInt LargeInt::operator*(const LargeInt& rhs) const {
	LargeInt digit_mult;
	LargeInt d_sum;
	unsigned int zeros_ins = 0;
	for (int i = rhs.number.size() - 1; i >= 0; i--) {
		unsigned int digit = rhs.number.at(i);
		digit_mult = this->digitMultiply(digit);
		digit_mult.number.insert(digit_mult.number.end(), zeros_ins++, 0);
		d_sum = d_sum + digit_mult;
	}
	if (sign != rhs.sign)
		d_sum.sign = false;
	return d_sum;
}


const LargeInt LargeInt::operator/(const LargeInt& rhs) const {
  LargeInt buffer;                
  LargeInt result;
  LargeInt divider = rhs.abs();   
  result.number.clear();         
  buffer.number.clear();

  if (rhs == LargeInt(0))                                    
    throw std::overflow_error("Division by zero");

  for (size_t i = 0; i < number.size(); ++i) {
    buffer.number.push_back(number[i]);
    buffer.deleteZero();
    if (buffer < divider) {
      result.number.push_back(0);
      continue;
    }
    int count;
    for (count = 0; buffer > divider || buffer == divider; ++count) {
      buffer = buffer - divider;
    }
    result.number.push_back(count);
  }
  result.deleteZero();

  result.sign = true;
  if(sign != rhs.sign && result.number[0] != 0)
    result.sign = false;

  return result;
}
