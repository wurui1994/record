#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void
SavePPM(const char*filename)
{
    cube c=randi<cube>(100,100,3, distr_param(0,255));
    c.save(filename,ppm_binary);
}

