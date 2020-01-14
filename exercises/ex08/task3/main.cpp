//
// Created by bnorb on 12.01.20.
//

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <ImageMagick-7/Magick++.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool parse(const std::vector<std::string>& inputVector);
bool transform(const std::string& filePath);
template <typename Iterator> bool parseLine(Iterator first, Iterator last);
bool readFile(const std::string &filePath, std::vector<std::string> &inputVector);


int main(int argc, char **argv) {
    Magick::InitializeMagick(*argv);
    std::string filePath = "picture.ppm";
    std::vector<std::string> inputVector;

    if (readFile(filePath, inputVector)) {
        std::cout << "File read successfully!" << std::endl;
    } else {
        std::cerr << "Could not read in file :x" << std::endl;
    }

    if (parse(inputVector)) {
        std::cout   << "Parse successful!" << std::endl;
        transform(filePath);
    } else {
        std::cerr << "Parse failed :(" << std::endl;
    }
}


bool transform(const std::string& filePath) {
    // Construct the image object. Separating image construction from the
    // the read operation ensures that a failure to read the image file
    // doesn't render the image object useless.
    Magick::Image image;
    try {
        // Read a file into image object if the parser yielded a successful result
        image.read(filePath);

        // Crop the image to specified size (width, height, xOffset, yOffset)
        //image.crop( Magick::Geometry(100,100, 100, 100) );
        image.rotate(90);

        // Write the image to a file
        image.write( "picture3.ppm" );
    }
    catch( std::exception &error_ ) {
        std::cerr << "Something went wrong while transforming the image: " << error_.what() << std::endl;
        return false;
    }
    return true;
}


// https://stackoverflow.com/questions/40866528/how-to-write-a-boostspiritqi-parser-to-parse-an-integer-range-from-0-to-std
bool parse(const std::vector<std::string>& inputVector) {
    std::string toParse;
    for (const auto& s : inputVector) {
        toParse += s + " ";
    }
    std::cout << toParse << std::endl;

    bool flag = parseLine(toParse.begin(), toParse.end());
    return flag;
}

template <typename Iterator>
bool parseLine(Iterator first, Iterator last) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    using qi::int_;
    using qi::char_;
    using qi::_1;
    using qi::_pass;
    using qi::phrase_parse;
    using ascii::space;

    bool parseSuccess = phrase_parse(
            first,                          /*< start iterator >*/
            last,                           /*< end iterator >*/
            ( char_('P') >> (char_('3') | char_('6')) )
                    >> (int_ >> int_)
                    >> int_ [ _pass = (_1>=0 && _1<=255) ]
                    >> *(int_ [ _pass = (_1>=0 && _1<=255) ] >> int_ [ _pass = (_1>=0 && _1<=255) ] >> int_ [ _pass = (_1>=0 && _1<=255) ]),   /*< the parser >*/
            space                           /*< the skip-parser >*/
    );

    if (first != last) // Tests for a full match. Partial matches are considered false.
        parseSuccess = false;
    return parseSuccess;
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