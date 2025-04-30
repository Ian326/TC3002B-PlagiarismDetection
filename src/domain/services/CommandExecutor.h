#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <filesystem>
#include <string>


/**
 * @class CommandExecutor
 * @brief This class is responsible for executing system commands and returning the output.
 */
class CommandExecutor {
    private:
        const static std::filesystem::path TEMP_DIR;
    
    public:
        CommandExecutor();
        ~CommandExecutor();
        
        static std::string execute(std::string&);
};


/**
 * @brief Constructor for the CommandExecutor class.
 */
CommandExecutor::CommandExecutor(){}


/**
 * @brief Destructor for the CommandExecutor class.
 */
CommandExecutor::~CommandExecutor(){}


/**
 * @brief Executes a system command and returns the output.
 * @param command The command to be executed. 
 * @throws std::runtime_error if the command cannot be executed.
 * @return The output of the command.
 */
std::string CommandExecutor::execute(std::string& command) {;
    char buffer[128];
    std::string result = "";
    
    std::FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("CommandExecutor: cannot open pipe");
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }

    pclose(pipe);

    std::filesystem::path outputLocation = TEMP_DIR / "output.txt";
    std::ofstream output;

    output.open(outputLocation.c_str(), std::ios::out);
    output << result;
    output.close();

    return outputLocation.string();
}

const std::filesystem::path CommandExecutor::TEMP_DIR = std::filesystem::temp_directory_path();

#endif // COMMANDEXECUTOR_H