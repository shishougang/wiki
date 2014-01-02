/* #include <iostream>
using namespace std;
struct StaticBlock {
    StaticBlock(){
        cout << "hello" << endl;
    }
};


static StaticBlock staticBlock;

int main(int, char * args[]){

  cout << "main" <<endl;
  return 0;
}
*/

#include <iostream>
using namespace std;


#define UHD_STATIC_BLOCK(_x)\
void _x(void);\
static _uhd_static_fixture _x##_fixture(&_x, #_x);\
void _x(void)


    //! Helper for static block, constructor calls function
  struct _uhd_static_fixture{
      _uhd_static_fixture(void (*fcn)(void), const char *name){
    try{
        fcn();
    }
    catch(const std::exception &e){
        std::cerr << "Exception in static block " << name << std::endl;
        std::cerr << "  " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "Exception in static block " << name << std::endl;
    }
}
  };



UHD_STATIC_BLOCK(hello){
cout << "static" <<endl;
}

int main(int argc, char *argv[])
{

cout<< "main" <<endl;
  return 0;
}
