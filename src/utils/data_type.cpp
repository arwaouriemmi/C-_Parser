#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <ctime>  // For time-related functions
#include "data_type.h"
namespace DataType
{

std::string rev_endian(const std::string& data) {
    // Check if the input string length is even
    if (data.length() % 2 != 0) {
        throw std::invalid_argument("Input string must have an even number of characters.");
    }

    std::string temp;
    // Reverse the endianness by swapping the byte pairs
    for (int i = data.length() - 2; i >= 0; i -= 2) {
        temp += data[i];
        temp += data[i + 1];
    }
    return temp;
}

signed long long read_long(const std::string& data) {
    try {
        std::string reversed_data = rev_endian(data);
        // Convert the hexadecimal string to a signed long long
        signed long long output = stoll(reversed_data, nullptr, 16);
        return output;
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("stoll out of range: " + std::string(e.what()));
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid argument: " + std::string(e.what()));
    }
}

std::string read_timestamp(const std::string& data) {
    signed long long timestamp = read_long(data);
    
    // Convert the raw timestamp to a human-readable format if it's a UNIX timestamp in nanoseconds
    time_t seconds = timestamp / 1000000000; // Convert nanoseconds to seconds
    struct tm* ptm = gmtime(&seconds);
    char buffer[32];
    // Format the date and time, in UTC
    strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
    return std::string(buffer) + " UTC";
}

    signed long read_price(std::string data)
    {
        // Effectively same as long
        return read_long(data);
    }

    unsigned long read_int(std::string data)
    {
        // int is 4 bytes unsigned
        data = rev_endian(data);
        unsigned long output = stoul(data, 0, 16);
        return output;
    }

    unsigned long read_event_time(std::string data)
    {
        // event time is same as integer data type
        return read_int(data);
    }

    unsigned int read_short(std::string data)
    {
        // short is a 2 byte unsigned integer
       // data = rev_endian(data);
        short output = stoul(data, 0, 16);
        return output;
    }

    unsigned int read_byte(std::string data)
    {
        // byte is unsigned integer
        //stoul converts string to hex to unsigned int
        data = rev_endian(data);
        int output = stoul(data, 0, 16);
        return output;
    }


    // Read strings
    //see -> https://stackoverflow.com/a/3790707
    unsigned char hexval(unsigned char c)
    {
        if ('0' <= c && c <= '9')
            return c - '0';
        else if ('a' <= c && c <= 'f')
            return c - 'a' + 10;
        else if ('A' <= c && c <= 'F')
            return c - 'A' + 10;
        else
            abort();
    }

    void hex2ascii(const std::string &in, std::string &out)
    {
        out.clear();
        out.reserve(in.length() / 2);
        for (std::string::const_iterator p = in.begin(); p != in.end(); p++)
        {
            unsigned char c = hexval(*p);
            p++;
            if (p == in.end())
                break;                 // incomplete last digit - should report error
            c = (c << 4) + hexval(*p); // + takes precedence over <<
            out.push_back(c);
        }
    }

    std::string read_string(std::string data)
    {
        //Reads string
        std::string output;
        hex2ascii(data, output);

        // Erase empty spaces
        std::string::iterator end_pos = std::remove(output.begin(), output.end(), ' ');
        output.erase(end_pos, output.end());

        return output;
    }

    // Convert flag to binary representation
    // see -> https://stackoverflow.com/a/18311086
    const char *hex_char_to_bin(char c)
    {
        // TODO handle default / error
        switch (toupper(c))
        {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
        };

        //remove warning with default argument
        return "0000";
    }

    std::string hex_str_to_bin_str(const std::string &hex)
    {
        // TODO use a loop from <algorithm> or smth
        std::string bin;
        for (unsigned i = 0; i != hex.length(); ++i)
            bin += hex_char_to_bin(hex[i]);
        return bin;
    }

}