#### How it works
First we need to install ImageMagick and its C++ API Magick++. Additionally we need to install boost. Adding boost spirit is done by simply adding the needed header files into the code. 

We are working with CLion, but we haven't managed to get Magick++ to compile within it. Therefore we compile the program using the terminal with the following command: 

- c++ `Magick++-config --cxxflags --cppflags` -O2 -o main main.cpp \
  `Magick++-config --ldflags --libs`
  
This command was taken from one of the ImageMagic URLs provided below in the Resource chapter. 


#### Resources
We used the example code provided in the boost spirit documentation as the basis for our code: 
- https://www.boost.org/doc/libs/1_72_0/libs/spirit/doc/html/spirit/qi/tutorials/warming_up.html#spirit.qi.tutorials.warming_up.trivial_example__4_parsing_a_comma_delimited_list_of_numbers

The sample image was taken from: 
- https://en.wikipedia.org/wiki/Netpbm_format

ImageMagic with Magick++: 
- https://linuxconfig.org/how-to-install-imagemagick-7-on-ubuntu-18-04-linux
- https://imagemagick.org/script/magick++.php