#include <iostream>
#include <stack>
using namespace std;

class Tower{
  int Index;
  stack<int> disks;
public:
   Tower(int i): Index(i), disks(){}
  int index() { return Index;}
  void add(int i)
  {
    if( !disks.empty() && i > disks.top() ){
      cout << "move the disk error" <<endl;
      return;
    }
    disks.push(i);
  }
    
  void MoveTop(Tower &t)
  {
    int top =  disks.top();
    t.add(top);
    disks.pop();
    cout<< "Move " << top <<" from Tower" << this->index()
             << " To Tower" << t.index() <<endl;
    
  }

  void MoveDisk(int n, Tower &destination, Tower &buffer)
  {
    if(n > 0){
      //cout << "index = " << this->index() <<endl;
      //cout << "size = " << disks.size() <<endl;
      MoveDisk(n - 1, buffer, destination);
      MoveTop(destination);
      buffer.MoveDisk(n - 1, destination, *this);
    }
  }
};

int main(int argc, char *argv[])
{
  Tower tower1(1);
  Tower tower2(2);
  Tower tower3(3);
  int i;
  int n = 5;

  for(i = 5; i > 0; i--)
    tower1.add(i);
  tower1.MoveDisk(n, tower3, tower2);
  return 0;
}
