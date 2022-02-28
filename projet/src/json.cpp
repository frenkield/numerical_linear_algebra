#include "json.hpp"

JSON::JSON(std::ostream &stream) : stream_(stream) {
    stream_ << "{";
    comma_add_ = false;
    comma_start_ = false;
}

void JSON::close() {
    stream_ << "\n}\n";
}

JSON& JSON::start(std::string key) {
    if (comma_start_) {
        stream_ << ",";
    }
    stream_ << "\n  \"" << key << "\": {";
    comma_start_ = true;
    comma_add_ = false;
    return *this;
}

void JSON::end() {
    stream_ << "\n  }";
    comma_add_ = false;
}

void JSON::addCommaIfNecessary() {
    if (comma_add_) {
        stream_ << ",";
    }
}

JSON& JSON::add(std::string key, int val) {
    addCommaIfNecessary();
    stream_ << "\n    \"" << key << "\": " << std::to_string(val);
    comma_add_ = true;
    return *this;
}

JSON& JSON::add(std::string key, double val) {
    addCommaIfNecessary();
    stream_ << "\n    \"" << key << "\": " << val;
    comma_add_ = true;
    return *this;
}

JSON& JSON::add(std::string key, std::string val) {
    addCommaIfNecessary();
    stream_ << "\n    \"" << key << "\": \"" << val << "\"";
    comma_add_ = true;
    return *this;
}

JSON& JSON::add(std::string key, std::vector<double> &val) {

    addCommaIfNecessary();
    stream_ << "\n    \"" << key << "\": [";

    bool first = true;

    for(typename std::vector<double>::iterator it = val.begin(); it != val.end(); ++it) {

        if (first) {
            first = false;
        } else {
            stream_ << ", ";
        }

        stream_ << *it;
    }

    stream_ << "]";
    return *this;
}
