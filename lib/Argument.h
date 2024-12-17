#pragma once
#include <string>
#include <vector>
#include <iostream>


class Argument {
protected:
    std::string long_argument_;
    char        short_argument_;
    std::string description_;
    bool        is_multivalue_ = false;
    bool        has_default_value_ = false;
    size_t      min_size_ = 0;
    bool        is_positional_ = false;
public:
    bool               CheckArg(std::string);
    bool               CheckDefault();
    const std::string& GetLongArgument();
    const char&        GetShortArgument();
    size_t             GetMinSize();
    bool               CheckMultiValue();
    bool               CheckPositional();
    const std::string& GetDescription();

    // constructor w/o description
    Argument(const std::string& long_arg)
                    : long_argument_(long_arg) {};

    Argument(const char& short_arg, const std::string& long_arg)
                    : short_argument_(short_arg)
                    , long_argument_(long_arg) {};

    Argument(const char& short_arg)
                    : short_argument_(short_arg) {};

    // constructor with description
    Argument(const std::string& long_arg, const std::string& description)
                    : long_argument_(long_arg)
                    , description_(description){};

    Argument(const char& short_arg, const std::string& long_arg, const std::string& description)
                    : short_argument_(short_arg) 
                    , long_argument_(long_arg)
                    , description_(description){};
};

class IntArg : public Argument {
private:
    int32_t*              storage_value_pointer_ = nullptr;
    std::vector<int32_t>* storage_values_pointer_ = nullptr;
public:
    using Argument::Argument;
    int32_t              default_value{};
    std::vector<int32_t> data;
    IntArg&              MultiValue();
    IntArg&              MultiValue(int32_t size);
    void                 Default(const int32_t&);
    void                 StoreValue(int32_t&);
    void                 StoreValues(std::vector<int32_t>& values);
    void                 UpdateStorage();
    IntArg&              Positional();
    int32_t              GetDefaultValue();
};

class StringArg : public Argument {
private:
    std::string*              storage_value_pointer_ = nullptr;
    std::vector<std::string>* storage_values_pointer_ = nullptr;
public:
    using Argument::Argument;
    std::string              default_value{};
    std::vector<std::string> data{};
    StringArg&               MultiValue(int32_t size);
    StringArg&               MultiValue();
    void                     Default(const std::string&);
    void                     StoreValue(std::string&);    
    void                     StoreValues(std::vector<std::string>& values);
    void                     UpdateStorage();
    StringArg&               Positional();
    const std::string&       GetDefaultValue();
};

class Flag : public Argument {
private: 
    bool* storage_value_pointer_ = nullptr;
    bool  default_value_ = false;
public:
    using Argument::Argument;
    bool value{};
    void Default(const bool&);
    void StoreValue(bool&);
    void UpdateStorage();
    bool FindShortFlag(std::string);
    bool GetDefaultValue();
};

class HelpArg {
private:
    std::string long_argument_{};
    char        short_argument_{};
    std::string description_{};
    bool        value_ = false;
    bool        empty_ = true;
public:
    HelpArg() = default;    
    HelpArg(const char& short_key, const std::string& long_key, const std::string& description, const bool& empty) 
        : short_argument_(short_key)
        , long_argument_(long_key)
        , description_(description)
        , empty_(empty) {};

    void SetValue(const bool&);
    bool GetValue();
    const std::string& GetDescription();
    const std::string& GetLongArg();
    const char& GetShortArg();
    bool Empty();
};