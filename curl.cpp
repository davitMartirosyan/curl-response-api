#include <cpr.h>
#include <iostream>

int main(void)
{
	auto r = cpr::Get(Url{"https://google.com"});

	std::cout << r.text << std::endl;
}