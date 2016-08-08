/*
The MIT License (MIT)
Copyright (c) 2016 Alvaro Collet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
Neither name of this software nor the names of its contributors may be used to
endorse or promote products derived from this software without specific
prior written permission.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <array>
#include <iostream>
#include <iomanip>
#include "color_generator.h"

//struct RGBColor
//{
//    unsigned char color[3];
//
//    RGBColor(unsigned char r, unsigned char g, unsigned char b) : color{ r, g, b } {}
//};

int main(int argc, char *argv[])
{
    typedef std::array<unsigned char, 3> RGBColor;
    int numColors = 20;
    bool showExamples = true;
    if (argc == 2)
    {
        numColors = atoi(argv[1]);
        showExamples = false;
    }
    else
    {
        std::cout << "Usage: ColorGenerator.exe [NumSampleColors]" << std::endl;
        std::cout << "Choosing default number of " << numColors << " sample colors..." << std::endl;
    }

    // EXAMPLE 1: Precomputed set of colors
    AC::ColorGenerator<RGBColor> colors(numColors);

    std::cout << std::endl << "Accessing generated set of " << colors.size() << " colors." << std::endl;
    for (size_t i = 0; i < colors.size(); ++i)
    {
        std::cout << "R: " << std::setw(5) << int(colors[i][0]) << " G: " << std::setw(5)  << int(colors[i][1]) << " B: " << std::setw(5) << int(colors[i][2]) << std::endl;
    }

    // If running this program with no arguments, just highlight the different ways to call this API
    if (showExamples)
    {
        // EXAMPLE 2: Arbitrary, non-precomputed index 
        RGBColor c;
        int colorIdx = 353; // arbitrary index
        colors.GenerateColor(colorIdx, c);
        std::cout << std::endl << "Color at index " << colorIdx << ". R: " << std::setw(5) << int(c[0]) << " G: " << std::setw(5) << int(c[1]) << " B: " << std::setw(5) << int(c[2]) << std::endl;

        // EXAMPLE 3: Precomputed colors, accessing through STL iterator 
        std::cout << std::endl << "Accessing generated set of " << colors.size() << " colors through an iterator." << std::endl;
        for (RGBColor& color : colors.Colors())
        {
            std::cout << "R: " << std::setw(5) << int(color[0]) << " G: " << std::setw(5) << int(color[1]) << " B: " << std::setw(5) << int(color[2]) << std::endl;
        }
    }
    return 0;
}

