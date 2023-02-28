#include "maths.h"

int exp(int a, int b) {
    int _return = 1;
    for (int i = 0; i < b; i++)
    {
        _return *= a;
    }
    
    return _return;
}