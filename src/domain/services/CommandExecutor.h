#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <iostream>
#include <string>
#include <cstdio> 

class CommandExecutor {
    public:
        static std::string execute(std::string&);
};

std::string CommandExecutor::execute(std::string& command) {
    std::filesystem::path output = std::filesystem::temp_directory_path() / ("output.txt");
    std::string _command = command + " >> " + output.string();

    std::remove(output.c_str());
    system(_command.c_str());

    return output.string();
}

#endif // COMMANDEXECUTOR_H