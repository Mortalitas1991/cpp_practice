#include <algorithm>
#include <fstream>
#include <iostream>
//#include <filesystem>

#include "./ip_filter.h"

//namespace fs = std::filesystem;

int main(int, char const**)
{
    try
    {
        //fs::path p;

        //std::fstream in(p.parent_path() += "../conan/ip_pool.tsv", std::ios_base::in);
        //std::fstream out(p.parent_path() += "../conan/ip_pool_out.tsv", std::ios_base::out);

        std::fstream in("../../ip_filter/ip_filter.tsv", std::ios_base::in);
        std::fstream out("../../ip_filter/ip_filter_out.tsv", std::ios_base::out);
        if(!in.is_open() || !out.is_open()) throw std::runtime_error("Can't open the file!");

        std::vector<std::string> pool = get_ips(in);
        std::sort(pool.begin(), pool.end(), ips_compare);

        for (const auto& ip : pool) {
            out << ip << '\n';
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
