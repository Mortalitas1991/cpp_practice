#include "conan.h"

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

bool ips_compare(const std::string& a, const std::string& b)
{
	int f = std::stoi(a);
	int s = std::stoi(b);
	if (f != s) {
		return f >= s;
	}

	auto first_dot = a.find_first_of('.');
	auto second_dot = b.find_first_of('.');

	if (first_dot == std::string::npos || second_dot == std::string::npos) {
		return f >= s;
	}

	return ips_compare(a.substr(first_dot + 1), b.substr(second_dot + 1));
}
