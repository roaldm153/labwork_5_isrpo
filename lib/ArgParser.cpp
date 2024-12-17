#include <charconv>
#include <cstdlib>
#include <string>

#include "ArgParser.h"
#include "Argument.h"


namespace ArgumentParser {

IntArg& ArgParser::AddIntArgument(const std::string& long_arg) {
    IntArg argument(long_arg);
    int_data_.push_back(argument);

    return int_data_[int_data_.size() - 1];
}

IntArg& ArgParser::AddIntArgument(const char& short_arg, const std::string& long_arg) {
    IntArg argument(short_arg, long_arg);
    int_data_.push_back(argument);

    return int_data_[int_data_.size() - 1];
}

IntArg& ArgParser::AddIntArgument(const std::string& long_arg, const std::string& description) {
    IntArg argument(long_arg, description);
    int_data_.push_back(argument);

    return int_data_[int_data_.size() - 1];
}

IntArg& ArgParser::AddIntArgument(
    const char& short_arg
    , const std::string& long_arg
    , const std::string& description
) {
    IntArg argument(short_arg, long_arg, description);
    int_data_.push_back(argument);

    return int_data_[int_data_.size() - 1];
}

StringArg& ArgParser::AddStringArgument(const std::string& long_arg) {
    StringArg argument(long_arg);
    str_data_.push_back(argument);

    return str_data_[str_data_.size() - 1];
}

StringArg& ArgParser::AddStringArgument(const char& short_arg, const std::string& long_arg) {
    StringArg argument(short_arg, long_arg);
    str_data_.push_back(argument);

    return str_data_[str_data_.size() - 1];
}

StringArg& ArgParser::AddStringArgument(
    const char& short_arg
    , const std::string& long_arg
    , const std::string& description
) {
    StringArg argument(short_arg, long_arg, description);
    str_data_.push_back(argument);

    return str_data_[str_data_.size() - 1];
}

StringArg& ArgParser::AddStringArgument(const std::string& long_arg, const std::string& description) {
    StringArg argument(long_arg, description);
    str_data_.push_back(argument);

    return str_data_[str_data_.size() - 1];
}

Flag& ArgParser::AddFlag(const std::string& arg) {
    Flag flag(arg);
    flag_data_.push_back(flag);

    return flag_data_[flag_data_.size() - 1];
}

Flag& ArgParser::AddFlag(const char& short_arg, const std::string& long_arg) {
    Flag flag(short_arg, long_arg);
    flag_data_.push_back(flag);

    return flag_data_[flag_data_.size() - 1];
}

Flag& ArgParser::AddFlag(
    const char& short_arg
    , const std::string& long_arg
    , const std::string& description
) {
    Flag flag(short_arg, long_arg, description);
    flag_data_.push_back(flag);

    return flag_data_[flag_data_.size() - 1];
}

Flag& ArgParser::AddFlag(const std::string& long_arg, const std::string& description) {
    Flag flag(long_arg, description);
    flag_data_.push_back(flag);

    return flag_data_[flag_data_.size() - 1];
}

/*
    -p=value - short_arg_var1
    -p value - shor_arg_var2
    --param=value - long_arg_var1
    --param value - long_arg_var2
*/
bool ArgParser::TryFindStringArgument(
    const std::vector<std::string>& cmd_line
    , StringArg& arg
    , std::unordered_map<std::string, bool>& parsed
) {
    bool is_parsed = arg.CheckDefault();
    for (size_t index = 0; index < cmd_line.size(); ++index) {
        std::string long_arg_var1 = "--" + arg.GetLongArgument() + "=";
        std::string short_arg_var1 = {'-', arg.GetShortArgument(), '='};
        int32_t result_long_arg_var1 = cmd_line[index].find(long_arg_var1);
        int32_t result_short_arg_var1 = cmd_line[index].find(short_arg_var1);  

        std::string long_arg_var2 = "--" + arg.GetLongArgument();
        std::string short_arg_var2 = {'-', arg.GetShortArgument()};
        bool result_long_arg_var2 = (cmd_line[index] == long_arg_var2);
        bool result_short_arg_var2 = (cmd_line[index] == short_arg_var2);

        if (result_long_arg_var1 == 0) {
            arg.data.push_back(cmd_line[index].substr(long_arg_var1.size()));
            arg.UpdateStorage();
            parsed[cmd_line[index]] = true;
            is_parsed = true;
        }

        if (result_short_arg_var1 == 0) {
            arg.data.push_back(cmd_line[index].substr(short_arg_var1.size()));
            arg.UpdateStorage();
            parsed[cmd_line[index]] = true;
            is_parsed = true;
        }

        if (result_long_arg_var2 && index + 1 < cmd_line.size() && cmd_line[index + 1][0] != '-') {
            arg.data.push_back(cmd_line[index + 1]);
            arg.UpdateStorage();
            parsed[cmd_line[index + 1]] = true;
            is_parsed = true;
        }

        if (result_short_arg_var2 && index + 1 < cmd_line.size() && cmd_line[index + 1][0] != '-') {
            arg.data.push_back(cmd_line[index + 1]);
            arg.UpdateStorage();
            parsed[cmd_line[index + 1]] = true;
            is_parsed = true;
        }
    }

    return is_parsed;
}

bool IsNumber(const std::string& str) {
    size_t i = 0;
    while (i < str.size()) {
        if (!('0' <= str[i] && '9' >= str[i])) {
            if (i == 0 && str[i] == '-') {
                ++i;
                continue;
            }
            return false;
        }
        ++i;
    }

    return true;
}

bool ArgParser::TryFindIntArgument(
        const std::vector<std::string>& cmd_line
        , IntArg& arg
        , std::unordered_map<std::string, bool>& parsed
) {
    bool is_parsed = arg.CheckDefault();
    for (size_t index = 0; index < cmd_line.size(); ++index) {
        std::string long_arg_var1 = "--" + arg.GetLongArgument() + "=";
        std::string short_arg_var1 = {'-', arg.GetShortArgument(), '='};
        int32_t result_long_arg_var1 = cmd_line[index].find(long_arg_var1);
        int32_t result_short_arg_var1 = cmd_line[index].find(short_arg_var1);  

        std::string long_arg_var2 = "--" + arg.GetLongArgument();
        std::string short_arg_var2 = {'-', arg.GetShortArgument()};
        bool result_long_arg_var2 = (cmd_line[index] == long_arg_var2);
        bool result_short_arg_var2 = (cmd_line[index] == short_arg_var2);

        if (result_long_arg_var1 == 0) {
            int32_t result;
            std::string number = cmd_line[index].substr(long_arg_var1.size());
            std::from_chars(number.data(), number.data() + number.size(), result);
            arg.data.push_back(result);
            arg.UpdateStorage();
            parsed[cmd_line[index]] = true;
            is_parsed = true;
        }

        if (result_short_arg_var1 == 0) {
            std::string number = cmd_line[index].substr(short_arg_var1.size());
            int32_t result;
            std::from_chars(number.data(), number.data() + number.size(), result);
            arg.data.push_back(result);
            arg.UpdateStorage();
            parsed[cmd_line[index]] = true;
            is_parsed = true;
        }

        if (result_long_arg_var2 && index + 1 < cmd_line.size() && IsNumber(cmd_line[index + 1])) {
            std::string number = cmd_line[index + 1];
            int32_t result;
            std::from_chars(number.data(), number.data() + number.size(), result);
            arg.data.push_back(result);
            arg.UpdateStorage();
            parsed[cmd_line[index + 1]] = true;
            is_parsed = true;
        }

        if (result_short_arg_var2 && index + 1 < cmd_line.size() && IsNumber(cmd_line[index + 1])) {
            std::string number = cmd_line[index + 1];
            int32_t result;
            std::from_chars(number.data(), number.data() + number.size(), result);
            arg.data.push_back(result);
            arg.UpdateStorage();
            parsed[cmd_line[index + 1]] = true;
            is_parsed = true;
        }
    }

    return is_parsed;
}

bool ArgParser::TryFindFlag(
        const std::vector<std::string>& cmd_line
        , Flag& flag
        , std::unordered_map<std::string, bool>& parsed
) {
    bool is_parsed = flag.CheckDefault();
    for (size_t index = 0; index < cmd_line.size(); ++index) {
        std::string long_arg = "--" + flag.GetLongArgument();
        std::string short_arg = {'-', flag.GetShortArgument()};
        bool is_equal_long_arg = (long_arg == cmd_line[index]);
        int32_t return_value_short_arg = parsed[cmd_line[index]] ? -1 : cmd_line[index].find(short_arg);

        if (is_equal_long_arg) {
                flag.value = true;
                flag.UpdateStorage();
                parsed[cmd_line[index]] = true;
                is_parsed = true;
        }

        if (return_value_short_arg == 0) {
            flag.value = true;
            flag.UpdateStorage();
            is_parsed = true;
            parsed[cmd_line[index]] = true;
            if (short_arg.size() < cmd_line[index].size()) {
                for (size_t k = 0; k < flag_data_.size(); ++k) {
                    if (flag_data_[k].FindShortFlag(cmd_line[index].substr(short_arg.size()))) {
                        flag_data_[k].value = true;
                        flag_data_[k].UpdateStorage();
                    }
                }
            }
        }
    }

    return is_parsed;
}

bool ArgParser::TryFindHelpArgument(
        const std::vector<std::string>& cmd_line
        , HelpArg& help
        , std::unordered_map<std::string, bool>& parsed
) {
    bool is_parsed = false;
    for (size_t index = 0; index < cmd_line.size(); ++index) {
        std::string long_arg = "--" + help.GetLongArg();
        std::string short_arg = {'-', help.GetShortArg()};
        bool is_equal_long_arg = (cmd_line[index] == long_arg);
        bool is_equal_short_arg = (cmd_line[index] == short_arg);

        if (is_equal_long_arg) {
            help.SetValue(true);
            parsed[cmd_line[index]] = true;
            is_parsed = true;
        }

        if (is_equal_short_arg) {
            help.SetValue(true);
            parsed[cmd_line[index]] = true;
            is_parsed = true;
        }
    }

    return is_parsed;
}

bool ArgParser::Parse(std::vector<std::string> cmd_line) {
    if (int_data_.empty() && str_data_.empty() && flag_data_.empty()) {
        return true;
    }
    std::unordered_map<std::string, bool> parsed;

    bool is_parsed = false;
    if (!help_data_.Empty()) {
        is_parsed |= TryFindHelpArgument(cmd_line, help_data_, parsed);
    }

    for (size_t i = 0; i < str_data_.size(); ++i) {
        if (!str_data_[i].CheckPositional()) {
            is_parsed |= TryFindStringArgument(cmd_line, str_data_[i], parsed);
        }
    }

    for (size_t i = 0; i < int_data_.size(); ++i) {
        if (!int_data_[i].CheckPositional()) {
            is_parsed |= TryFindIntArgument(cmd_line, int_data_[i], parsed);
        }
    }

    for (size_t i = 0; i < flag_data_.size(); ++i) {
        is_parsed |= TryFindFlag(cmd_line, flag_data_[i], parsed);
    }

    for (size_t i = 0; i < str_data_.size(); ++i) {
        if (str_data_[i].CheckPositional()) {
            for (size_t j = 0; j < cmd_line.size(); ++j) {
                if (!parsed[cmd_line[j]]) { 
                    str_data_[i].data.push_back(cmd_line[j]);
                    str_data_[i].UpdateStorage();
                    is_parsed = true;
                    parsed[cmd_line[j]] = true;
                }
            }
        }
    }

    for (size_t i = 0; i < int_data_.size(); ++i) {
        if (int_data_[i].CheckPositional()) {
            for (size_t j = 0; j < cmd_line.size(); ++j) {
                if (!parsed[cmd_line[j]] && IsNumber(cmd_line[j])) {
                    int32_t result;
                    std::from_chars(cmd_line[j].data(), cmd_line[j].data() + cmd_line[j].size(), result);
                    int_data_[i].data.push_back(result);
                    int_data_[i].UpdateStorage();
                    is_parsed = true;
                    parsed[cmd_line[j]] = true;
                }
            }
        }
    }

    for (size_t i = 0; i < int_data_.size(); ++i) {
        if (int_data_[i].CheckMultiValue() && int_data_[i].GetMinSize() > int_data_[i].data.size() && help_data_.Empty()) {
            return false;
        }
    }

    for (size_t i = 0; i < str_data_.size(); ++i) {
        if (str_data_[i].CheckMultiValue() && str_data_[i].GetMinSize() > str_data_[i].data.size() && help_data_.Empty()) {
            return false;
        }
    }

    return is_parsed;
}

std::string ArgParser::GetStringValue(const std::string& arg) {
    size_t i = 0;
    while (i < str_data_.size() && !str_data_[i].CheckArg(arg)) {
        ++i;
    }

    if (i >= str_data_.size()) {
        std::cerr << "Error: You are trying to get value of unexistable argument!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (str_data_[i].data.empty()) {
        return str_data_[i].default_value;
    } else {
        return str_data_[i].data[0];
    }
}

std::string ArgParser::GetStringValue(const std::string& arg, size_t index) {
    size_t i = 0;
    while (i < str_data_.size() && !str_data_[i].CheckArg(arg)) {
        ++i;
    }

    if (i >= str_data_.size()) {
        std::cerr << "Error: You are trying to get value of unexistable argument!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (index >= str_data_[i].data.size()) {
        std::cerr << "Error: Index out of data size!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return str_data_[i].data[index];
}

int32_t ArgParser::GetIntValue(const std::string& arg) {
    size_t i = 0;
    while (i < int_data_.size() && !int_data_[i].CheckArg(arg)) {
        ++i;
    }

    if (i >= int_data_.size()) {
        std::cerr << "Error: You are trying to get value of unexistable argument!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (int_data_[i].data.empty()) {
        return int_data_[i].default_value;
    } else {
        return int_data_[i].data[0];
    }
}

int32_t ArgParser::GetIntValue(const std::string& arg, size_t index) {
    size_t i = 0;
    while (i < int_data_.size() && !int_data_[i].CheckArg(arg)) {
        ++i;
    }

    if (i >= int_data_.size()) {
        std::cerr << "Error: You are trying to get value of unexistable argument!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (index >= int_data_[i].data.size()) {
        std::cerr << "Error: Index out of data size!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return int_data_[i].data[index];
}

bool ArgParser::GetFlag(const std::string& arg) {
    size_t i = 0;
    while (i < flag_data_.size() && !flag_data_[i].CheckArg(arg)) {
        ++i;
    }

    if (i >= flag_data_.size()) {
        std::cerr << "Error: You are trying to get value of unexistable flag!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    if (flag_data_[i].CheckDefault()) {
        return flag_data_[i].GetDefaultValue();
    }

    return flag_data_[i].value;
}

void ArgParser::AddHelp(const char& short_arg, const std::string& long_arg, const std::string& description) {
    HelpArg help(short_arg, long_arg, description, false);
    help_data_ = help;
}

bool ArgParser::Help() {
    return !help_data_.Empty();
}

std::string ArgParser::HelpDescription() {
    std::string help_description = help_data_.GetDescription();
    std::string program_description = description_;
    std::string main_description = program_description + '\n' + help_description + '\n';

    for (size_t i = 0; i < str_data_.size(); ++i) {
        std::string short_arg = {'-', str_data_[i].GetShortArgument()};
        const int32_t kSpaceKey = 6;
        const int32_t kShortArgPos = 1;
        if (short_arg[kShortArgPos] == kSpaceKey) {
            short_arg = "without short argument";
        }
        main_description += '\n'
                            + short_arg
                            + ", --" + str_data_[i].GetLongArgument() 
                            + "=<string>" 
                            + ", " + str_data_[i].GetDescription()
                            + (str_data_[i].CheckDefault() ? " [default = " + str_data_[i].GetDefaultValue() + "] " : " ");
        if (str_data_[i].CheckMultiValue()) {
            main_description += "[repeated, min args = " + std::to_string(str_data_[i].GetMinSize()) + "]\n";
        } else {
            main_description += "\n";
        }
    }

    for (size_t i = 0; i < int_data_.size(); ++i) {
        std::string short_arg = {'-', int_data_[i].GetShortArgument()};
        const int32_t kSpaceKey = 6;
        const int32_t kShortArgPos = 1; 
        if (short_arg[kShortArgPos] == kSpaceKey) {
            short_arg = "without short argument";
        }
        main_description += short_arg
                            + ", --" + int_data_[i].GetLongArgument() 
                            + "=<int>" 
                            + ", " + int_data_[i].GetDescription()
                            + (int_data_[i].CheckDefault() ? " [default = " + std::to_string(int_data_[i].GetDefaultValue()) 
                            + "] " : " ");
        if (int_data_[i].CheckMultiValue()) {
            main_description += "[repeated, min args = " + std::to_string(int_data_[i].GetMinSize()) + "]\n";
        } else {
            main_description += "\n";
        }
    }

    for (size_t i = 0; i < flag_data_.size(); ++i) {
        std::string short_arg = {'-', flag_data_[i].GetShortArgument()};
        std::string default_value;
        if (flag_data_[i].GetDefaultValue()) {
            default_value = "true";
        } else {
            default_value = "false";
        }
        main_description += short_arg
                            + ", --" + flag_data_[i].GetLongArgument() 
                            + ", " + flag_data_[i].GetDescription()
                            + (flag_data_[i].CheckDefault() ? " [default = " + default_value
                            + "] " : " ")
                            + "\n";
    }

    std::string short_arg = {'-', help_data_.GetShortArg()};
    main_description += '\n'
                        + short_arg
                        + ", --" + help_data_.GetLongArg()
                        + ", Display this help and exit\n";

    return main_description;
}
} // namespace ArgumentParser