#include <iostream>
#include <cmath>
#include "util.h"
#include "pkg.h"
#include "ani.h"
#include "mex.h"

using namespace std;


void read_pkg(const char *filename)
{
	Pkg pkg(filename);
	pkg.info();
	pkg.save();
}

void read_ani(const char *filename)
{
    Ani ani(filename);
    ani.info();
}

void read_mex(const char *filename)
{
    Mex mex(filename);
    mex.info();
}

int main(int argc, char* argv[])
{
	//for(int i = 1; i < argc; i ++)
	//	read_pkg(argv[i]);
	//read_pkg("../raw/Character.package");
	read_ani("res/mwandou05.ani");
	//read_mex("res/mwandou05.mex");
}

