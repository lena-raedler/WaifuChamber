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

template <typename Expr>
bool parse2(const std::vector<std::string>& inputVector);

template <typename Iterator, typename Expr>
bool parseExpression(Iterator first, Iterator last, const Expr expr);

bool transform(const std::string& filePath);
template <typename Iterator> bool parseLine(Iterator first, Iterator last);
bool readFile(const std::string &filePath, std::vector<std::string> &inputVector);


int main(int argc,char **argv) {
    Magick::InitializeMagick(*argv);
    std::string filePath = "picture.ppm";

    std::vector<std::string> inputVector;
    //readFile("../picture.ppm", inputVector);
    readFile(filePath, inputVector);

    if (parse(inputVector)) {
    //if (parse2(inputVector)) {
        std::cout   << "Parse successful!" << std::endl;
        transform(filePath);
    }
    else {
        std::cerr << "Parse failed :(" << std::endl;
    }
}


template <typename Expr>
bool parse2(const std::vector<std::string>& inputVector) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using qi::int_;
    using qi::char_;
    using qi::_1;
    using qi::_pass;
    using qi::phrase_parse;

    std::string header = inputVector[0] + ' ' + inputVector[1] + ' ' + inputVector[2];
    Expr exprHeader = ( char_('P') >> (char_('3') | char_('6')) )
                      >> (int_ >> int_)
                      >> int_ [ _pass = (_1>=0 && _1<=255) ];

    bool flag = parseExpression(header.begin(), header.end(), exprHeader);
    return flag;
}

template <typename Iterator, typename Expr>
bool parseExpression(Iterator first, Iterator last, const Expr expr) {

    // Parse the header
    bool parseSuccess = phrase_parse(
            first,                          /*< start iterator >*/
            last,                           /*< end iterator >*/
            expr,
            boost::spirit::ascii::space     /*< the skip-parser >*/
    );

    if (first != last) // fail if we did not get a full match
        parseSuccess = false;
    return parseSuccess;
}


bool transform(const std::string& filePath) {
    // Construct the image object. Seperating image construction from the
    // the read operation ensures that a failure to read the image file
    // doesn't render the image object useless.
    Magick::Image image;
    try {
        // Read a file into image object
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

    if (first != last) // fail if we did not get a full match
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