#include <iostream>
using namespace std;

void func(istream &in, ostream &out)
{
   int i;
   in >> i;
   out << "output :" << i << endl;
}

int main()
{
   func(cin, cout);
   return 0;
}
