#include "SuperClass.h"

int main(int argc, char *argv[])
{
	SuperClass* super = new SuperClass(argc, argv);
	delete super;

	return 0;
}
