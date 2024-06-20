#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>

std::string rev_endian(const std::string& data);
signed long long read_long(const std::string& data);
std::string read_timestamp(const std::string& data);

#endif // DATA_TYPE_H
