#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "ctmpl.h"

int main() {
    std::vector<std::map<std::string, ctmpl::object>> xs;
    xs.push_back({
        { "enable", true },
        { "url", "http://example.com" },
        { "value", "Example" },
    });
    xs.push_back({
        { "enable", false },
        { "url", "undefined" },
        { "value", "Test" },
    });
    xs.push_back({
        { "enable", true },
        { "url", "http://google.com" },
        { "value", "Google" },
    });

    std::map<std::string, ctmpl::object> t;
    t["title"] = "Sample Site";
    t["xs"] = xs;

    try {
        std::string html = "";
        std::ifstream is ("sample.html", std::ifstream::binary);
        if (is) {
            is.seekg (0, is.end);
            int length = is.tellg();
            is.seekg (0, is.beg);
            char * buffer = new char [length];
            is.read (buffer,length);
            if (is) {
                html = std::string(buffer, length);
            }
            is.close();
            delete[] buffer;
            ctmpl::parse(html, t);
        }
    } catch (ctmpl::parse_error& error) {
        std::cerr << error.long_error() << std::endl;
    }
}
