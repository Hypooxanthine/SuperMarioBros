#include "Util.h"

size_t getUserIntRange(const std::string& label, const size_t& min, const size_t& max)
{
	size_t out = 0;

	do
	{
		std::cout << label << " [" << min << "-" << max << "] :	";
		std::cin >> out;
	} while (out < min || out > max);

	return out;
}
