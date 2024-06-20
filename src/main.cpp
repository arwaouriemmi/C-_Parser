#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
#include "utils/decode.cpp"
#include "utils/data_type.h"

int main(int argc, char *argv[])
{
    // Initializing IO path variables
    std::string read_file_path;
    std::string write_file_path;

    // Initializing the string containing raw packets
    std::string packet;

    // Initializing output data structure
    DataStructure::string_array outputs;
    DataStructure::string_array_init(outputs);

    if (argc == 3)
    {
        // Command Line Arguments, needs read and write path
        read_file_path = argv[1];
        write_file_path = argv[2];
    }
    else
    {
        // Unknown commands, exit with error status
        return -1;
    }

    std::ifstream raw_file(read_file_path);

    if (raw_file.is_open())
    {
        
        int packet_counter = 0;
        // Processing packet by packet
        while (std::getline(raw_file, packet))
        {
          

            // Cleaning unwanted '\n' from the packets
            packet.erase(remove(packet.begin(), packet.end(), '\n'), packet.end());

            // Decoding the packets
            Decode::packet_parse(packet, outputs);
             packet_counter++;
             std::cout << "Processed packet count: " << packet_counter << std::endl;
        }

        raw_file.close();

        // Writing files to disk
        io::save_file(write_file_path, outputs);
    }
    else
    {
        // Unable to open the files
        return -1;
    }

    return 0;
}
