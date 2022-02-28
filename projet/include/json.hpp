#ifndef JSON_H
#define JSON_H

#include <fstream>
#include <string>
#include <vector>

class JSON {

private:
    std::ostream& stream_;
    bool comma_add_;
    bool comma_start_;

public:
    JSON(std::ostream& stream);
    JSON& start(std::string key);
    void end();
    void addCommaIfNecessary();
    JSON& add(std::string key, int val);
    JSON& add(std::string key, double val);
    JSON& add(std::string key, std::string val);
    JSON& add(std::string key, std::vector<double>& val);
    void close();
};

#endif // JSON_H
