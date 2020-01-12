//
// Created by bnorb on 12.01.20.
//

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool parse(const std::vector<std::string>& inputVector);
template <typename Iterator> bool parseLine(Iterator first, Iterator last);
bool readFile(const std::string &filePath, std::vector<std::string> &inputVector);
bool writeFile(const std::string &filePath, const std::vector<std::string> &outputVector);

int main() {
    std::vector<std::string> inputVector;
    readFile("../picture.ppm", inputVector);

    if (parse(inputVector)) {
        std::cout << "Parse successful!" << std::endl;
    }

    writeFile("../picture2.ppm", inputVector);
}


bool parse(const std::vector<std::string>& inputVector) {
    /*
    for (const auto& s : inputVector) {
        if (!parseLine(s.begin(), s.end()))
            return false;
    }*/

    std::string toParse;
    for (const auto& s : inputVector) {
        toParse += s + " ";
    }
    std::cout << toParse << std::endl;
    bool flag = parseLine(toParse.begin(), toParse.end());

    //std::string s = "1, 2, 0";
    //bool flag = parseLine(s.begin(), s.end());

    return flag;
}

template <typename Iterator>
bool parseLine(Iterator first, Iterator last) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    using qi::int_;
    using qi::char_;
    using qi::_3;
    using qi::phrase_parse;
    using ascii::space;

    bool r = phrase_parse(
            first,                          /*< start iterator >*/
            last,                           /*< end iterator >*/
            (char_('P') >> int_)
                    >> (int_ >> int_)
                    >> (int_)
                    >> *(int_ >> int_ >> int_),   /*< the parser >*/
            space                           /*< the skip-parser >*/
    );

    if (first != last) // fail if we did not get a full match
        return false;
    return r;
}


bool readFile(const std::string &filePath, std::vector<std::string> &inputVector) {
    std::ifstream infile(filePath);

    if(!infile) {
        std::cerr << "Cannot open input file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
        inputVector.push_back(line);
    }
    return true;
}


bool writeFile(const std::string &filePath, const std::vector<std::string> &outputVector) {
    std::ofstream outFile(filePath);

    if(!outFile) {
        std::cerr << "Cannot open output file." << std::endl;
        return false;
    }

    for (const std::string& s : outputVector) {
        outFile << s << std::endl;
    }

    return true;
}