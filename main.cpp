#include <iostream>
#include <fstream>
#include "ip_regles.h"
#include "port_regles.h"

using namespace std;

int main()
{
     ip_regles test;
     cout << test.get_regle("192.168.1.1") << endl;

     return 0;
}
