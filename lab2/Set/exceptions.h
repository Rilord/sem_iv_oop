#pragma once

#include <exception>
#include <string>

using std::string;

class base_exception : public std::exception {
    protected:
        string err_msg;

    public:
        base_exception(std::string file, std::string class_name, 
                unsigned int line, time_t time, 
                string err_name) {
            err_msg = "In file: " + file + "in class: " + class_name + "in line: " +  std::to_string(line) + "\nat " 
            + ctime(&time) + "error:" + err_name + "\n";
        }

        virtual const char * what(void) const noexcept override {
            return this->err_msg.c_str();
        }

};

class wrong_alloc_exception : base_exception {
    public:
        wrong_alloc_exception(std::string file, std::string class_name, 
                    unsigned int line, time_t time, 
                    string err_name) : base_exception(file, class_name, line, time, err_name){};
        const char * what(void) const noexcept override {
            std::string message = "\n[ERROR] Can't alloc memory. " + err_msg;
            char *cmessage = new char[1 + message.size()];
            std::strcpy(cmessage, message.c_str());
            return cmessage;
        }
};

class wrong_iterator_exception : base_exception {
    public:
        wrong_iterator_exception(std::string file, std::string class_name, 
                    unsigned int line, time_t time, 
                    string err_name) : base_exception(file, class_name, line, time, err_name){};
        const char * what(void) const noexcept override {
            std::string message = "\n[ERROR] Wrong iterator. " + err_msg;
            char *cmessage = new char[1 + message.size()];
            std::strcpy(cmessage, message.c_str());
            return cmessage;
        }
};

