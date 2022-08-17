#include "LargeInt.h"
#include <iostream>
#include <fstream>



int main(int argc, char const *argv[])
{
  std::ofstream ofst("output.txt");
  
  bigint::LargeInt a("712381273817238971298379812389182931");
  bigint::LargeInt b("-6236718188217617627816782178");


std::cout<<a<<"\n";
std::cout<<b;

  ofst << "a output: ";
  ofst << a.num_to_str()<<"\n";

  ofst << "b output: ";
  ofst << b.num_to_str()<<"\n";

  ofst << "a + b: ";
  ofst << (a+b).num_to_str()<<"\n";

  ofst << "a - b: ";
  ofst << (a-b).num_to_str()<<"\n";

  ofst << "a * b: ";
  ofst << (a*b).num_to_str()<<"\n";

  ofst << "a / b: ";
  ofst << (a/b).num_to_str()<<"\n"; 
}
