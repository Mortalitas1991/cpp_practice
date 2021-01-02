#pragma once

#include <string>
#include <vector>
#include <fstream>

std::string get_ip(const std::string&);
std::vector<std::string> get_ips(std::fstream&);
bool ips_compare(const std::string&, const std::string&);