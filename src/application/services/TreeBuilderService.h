#ifndef TREEBUILDERSERVICE_H
#define TREEBUILDERSERVICE_H

#include "../../domain/entities/AbstractSyntaxTree.h"
#include "../../domain/services/CommandExecutor.h"

class TreeBuilderService {
    private:
        const std::filesystem::path C = "./domain/entities/grammars/cpp.so";
        const std::filesystem::path JAVA = "./domain/entities/grammars/java.so";

    public:
        TreeBuilderService();
        ~TreeBuilderService();
        AbstractSyntaxTree* build(std::filesystem::path&, std::filesystem::path&);
};


/**
 * @brief Constructor for the TreeBuilderService class.
 */
TreeBuilderService::TreeBuilderService(){}


/**
 * @brief Destructor for the TreeBuilderService class.
 */
TreeBuilderService::~TreeBuilderService(){}



AbstractSyntaxTree* TreeBuilderService::build(std::filesystem::path &original, std::filesystem::path& plagiarized) {
    std::filesystem::path path = "tools/AST.py";

    std::string command = "python3 " + path.string() + " java " + JAVA.string() + " " + original.string() + " " + plagiarized.string();
    std::string deconstructed_tree = CommandExecutor::execute(command);

    return nullptr;
}

#endif // TREEBUILDERSERVICE_H