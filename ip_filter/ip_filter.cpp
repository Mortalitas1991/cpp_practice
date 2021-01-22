#include "./ip_filter.h"

#include <algorithm>

std::string get_ip(const std::string& line)
{
	std::string ip;
	for (auto c : line) {
		if (c == ' ' || c == '\t') return ip;
		ip += c;
	}

	return ip;
}

std::vector<std::string> get_ips(std::fstream& in)
{
	std::vector<std::string> pool;
	for (std::string line; std::getline(in, line);) {
		pool.push_back(get_ip(line));
	}

	pool.shrink_to_fit();
	return pool;
}

uint32_t ip_to_uint(const std::string& ip) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    uint32_t addr = 0;

    const std::string copy = ip;

    if (sscanf(copy.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d) != 4)
        return 0;

    addr = a << 24;
    addr |= b << 16;
    addr |= c << 8;
    addr |= d;
    
    return addr;
}

bool ips_compare(const std::string& a, const std::string& b)
{
	uint32_t first = ip_to_uint(a);	
	uint32_t second = ip_to_uint(b);

	return first > second;
}
