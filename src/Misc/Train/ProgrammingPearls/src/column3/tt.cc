#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  const int a[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
  a[0] = 100;
  cout << a[0] << endl;
  return 0;
}
