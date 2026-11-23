#ifndef STREETLIGHT_H
#define STREETLIGHT_H

#include <string>

struct Streetlight {
    int id;
    std::string street;
    std::string status;

    Streetlight() : id(0), street(""), status("Working") {}
    Streetlight(int _id, std::string _street, std::string _status) 
        : id(_id), street(_street), status(_status) {}
};

#endif
