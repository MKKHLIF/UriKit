#include <iostream>
#include <uri/uri.h>

int main()
{
	const Uri uri;
	uri.parse("htt++ps://www.google.com/search?q=cpp+uri+parser");
	std::cout << "Scheme: " << uri.getScheme() << std::endl;
	return 0;
}
