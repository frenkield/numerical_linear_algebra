#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>

class Logger {

private:
    template <typename T>
    static void printRaw(T t) {
        std::cout << t;
    }

    template<typename T, typename... Args>
    static void printRaw(T t, Args... args) {
        std::cout << t << " ";
        printRaw(args...);
    }

public:

    template <typename T>
    static void print(std::vector<T> vect) {

        bool first = true;

        for(typename std::vector<T>::iterator it = vect.begin(); it != vect.end(); ++it) {

            if (first) {
                first = false;
            } else {
                std::cout << " ";
            }

            std::cout << *it;
        }

        std::cout << std::endl;
    }

    template<typename T, typename... Args>
    static void print(T t, Args... args) {
        printRaw(t, args...);
        std::cout << std::endl;
    }
};

#endif // LOGGER_H

