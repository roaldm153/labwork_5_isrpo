#include <cstdlib>

#include "Argument.h"


IntArg& IntArg::MultiValue(int32_t size) {
    if (size < 0) {
        std::cerr << "Error: Invalid argument" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    this->is_multivalue_ = true;
    this->min_size_ = size;

    return *this;
}

IntArg& IntArg::MultiValue() {
    this->is_multivalue_ = true;
    this->min_size_ = 0;

    return *this;
}

StringArg& StringArg::MultiValue(int32_t size) {
    if (size < 0) {
        std::cerr << "Error: Invalid argument" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    this->is_multivalue_ = true;
    this->min_size_ = size;

    return *this;
}

StringArg& StringArg::MultiValue() {
    this->is_multivalue_ = true;
    this->min_size_ = 0;

    return *this;
}

void IntArg::Default(const int32_t& value) {
    default_value = value;
    has_default_value_ = true;
}

void StringArg::Default(const std::string& value) {
    default_value = value;
    has_default_value_ = true;
}

void Flag::Default(const bool& value) {
    default_value_ = value;
    has_default_value_ = true;
}

bool Argument::CheckDefault() {
    return has_default_value_;
}

size_t Argument::GetMinSize() {
    return min_size_;
}

bool Argument::CheckMultiValue() {
    return is_multivalue_;
}

void IntArg::StoreValue(int32_t& value) {
    storage_value_pointer_ = &value;
}

void IntArg::StoreValues(std::vector<int32_t>& values) {
    storage_values_pointer_ = &values;
}

void StringArg::StoreValue(std::string& value) {
    storage_value_pointer_ = &value;
}

void StringArg::StoreValues(std::vector<std::string>& values) {
    storage_values_pointer_ = &values;
}

void Flag::StoreValue(bool& value) {
    storage_value_pointer_ = &value;
}

bool Argument::CheckArg(std::string arg) {
    return (long_argument_ == arg);
}

const std::string& Argument::GetLongArgument() {
    return long_argument_;
}

const char& Argument::GetShortArgument() {
    return short_argument_;
}

void IntArg::UpdateStorage() {
    if (!is_multivalue_) {
        if (storage_value_pointer_ != nullptr && data.size() == 1) {
            *storage_value_pointer_ = data[0];
        }
    } else {
        if (storage_values_pointer_ != nullptr && !data.empty()) {
            *storage_values_pointer_ = data;
        }
    }
}

void StringArg::UpdateStorage() {
    if (!is_multivalue_) {
        if (storage_value_pointer_ != nullptr && data.size() == 1) {
            *storage_value_pointer_ = data[0];
        }
    } else {
        if (storage_values_pointer_ != nullptr && !data.empty()) {
            *storage_values_pointer_ = data;
        }
    }
}

void Flag::UpdateStorage() {
    if (storage_value_pointer_ != nullptr) {
        *storage_value_pointer_ = value;
    }
}

bool Flag::FindShortFlag(std::string str) {
    char short_arg = this->GetShortArgument();
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == short_arg) {
            return true;
        }
    }

    return false;
}

bool Flag::GetDefaultValue() {
    return default_value_;
}

IntArg& IntArg::Positional() {
    is_positional_ = true;

    return *this;
}

StringArg& StringArg::Positional() {
    is_positional_ = true;
    
    return *this;
}

bool Argument::CheckPositional() {
    return is_positional_;
}

bool HelpArg::GetValue() {
    return value_;
}

const std::string& HelpArg::GetDescription() {
    return description_;
}

const std::string& HelpArg::GetLongArg() {
    return long_argument_;
}

const char& HelpArg::GetShortArg() {
    return short_argument_;
}

void HelpArg::SetValue(const bool& value) {
    value_ = value;
}

bool HelpArg::Empty() {
    return empty_;
}

const std::string& Argument::GetDescription() {
    return description_;
}

int32_t IntArg::GetDefaultValue() {
    return default_value;
}

const std::string& StringArg::GetDefaultValue() {
    return default_value;
}