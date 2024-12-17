#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "Argument.h"


namespace ArgumentParser {
class ArgParser {
private:
    std::vector<IntArg>    int_data_{};
    std::vector<StringArg> str_data_{};
    std::vector<Flag>      flag_data_{};
    std::string            description_{};
    HelpArg                help_data_;

    bool TryFindStringArgument(
        const std::vector<std::string>&
        , StringArg&
        , std::unordered_map<std::string, bool>&
    );

    bool TryFindIntArgument(
        const std::vector<std::string>&
        , IntArg&
        , std::unordered_map<std::string, bool>&
    );

    bool TryFindFlag(
        const std::vector<std::string>&
        , Flag&
        , std::unordered_map<std::string, bool>&
    );

    bool TryFindHelpArgument(
        const std::vector<std::string>&
        , HelpArg&
        , std::unordered_map<std::string, bool>&
    );

public: 
    ArgParser(const std::string& description): description_(description) {};

    IntArg&     AddIntArgument(const std::string&);
    IntArg&     AddIntArgument(const char&, const std::string&);
    IntArg&     AddIntArgument(const std::string&, const std::string&);
    IntArg&     AddIntArgument(const char&, const std::string&, const std::string&);

    StringArg&  AddStringArgument(const std::string&);
    StringArg&  AddStringArgument(const char&, const std::string&);
    StringArg&  AddStringArgument(const std::string&, const std::string&);
    StringArg&  AddStringArgument(const char&, const std::string&, const std::string&);

    Flag&       AddFlag(const std::string&);
    Flag&       AddFlag(const char&, const std::string&);
    Flag&       AddFlag(const std::string&, const std::string&);
    Flag&       AddFlag(const char&, const std::string&, const std::string&);

    void        AddHelp(const char&, const std::string&, const std::string&);
    bool        Help();
    std::string HelpDescription();

    bool        Parse(std::vector<std::string>);
    std::string GetStringValue(const std::string&);
    std::string GetStringValue(const std::string&, size_t index);
    int32_t     GetIntValue(const std::string&);
    int32_t     GetIntValue(const std::string&, size_t index);
    bool        GetFlag(const std::string&);
};
} // namespace ArgumentParser