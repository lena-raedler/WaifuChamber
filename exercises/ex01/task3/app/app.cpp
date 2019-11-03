//#include "bar.hpp"
//#include "baz.hpp"
//#include "foo.hpp"
#include "../libBar/bar.hpp"
#include "../libFoo/foo.hpp"
#include "../libBaz/baz.hpp"

int main()
{
	foo();
	bar();
	baz();
}
