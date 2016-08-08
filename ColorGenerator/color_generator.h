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

#ifndef __COLOR_GENERATOR__
#define __COLOR_GENERATOR__

#include <vector>

namespace AC {

    // Class to create a fixed set of distinct colors, based on the method at: 
    // http://stackoverflow.com/questions/309149/generate-distinctly-different-rgb-colors-in-graphs
    //
    // The template parameter T is any color representation you want. The only constraint is that it must support
    // a constructor with three input parameters, as T(red, green, blue).
    template <class T>
    class ColorGenerator
    {
    public:
        typedef ColorGenerator<T> SP;

        // Constructor
        ColorGenerator(size_t numColors) { Reset(numColors); }

        /// <summary> Allocate memory and generate set of N visually distinct colors of type T. </summary>
        /// <param name="numColors"> Number of colors to generate in set. </param>
        void Reset(size_t numColors);

        /// <summary> Generates a new color (no precomputations!). This algorithm is deterministic, so the same index will always generate the same color.
        /// This function is used to generate a pre-computed set of NumColors for rapid access through the operator[]. </summary>
        /// <param name="index"> Zero-based index of the color to generate. This index can be arbitrarily high (not necessarily within the range of numColors). </param>
        /// <param name="color"> [out] The generated color. </returns>
        void GenerateColor(size_t index, T& color);

        /// <summary> Pick color from set of pre-computed colors. This is much faster than calling GenerateColor(). 
        /// Note that this index will wrap around the list of specified colors. </summary>
        const T operator[](size_t index) const { return m_colors[index % m_colors.size()]; }

        /// <summary> Query number of generated colors </summary>
        const size_t size() const { return m_colors.size(); }

        /// <summary> Query whole list of colors for const access </summary>
        const std::vector<T>& Colors() const { return m_colors; }
        
        /// <summary> Query whole list of colors for non-const access (use at your own risk) </summary>
        std::vector<T>& Colors() { return m_colors; }

    private:
        std::vector<T> m_colors;  // Vector of pre-computed colors for rapid access
        static const int c_NumPatterns = 7;

        /// <summary> Reverse bits (MSB->LSB) in unsigned char, so that (for example) 11010000 becomes 00001011. </summary>
        /// <param name="b"> The unsigned char to reverse. </param>
        /// <returns> . </returns>
        unsigned char ReverseBits(unsigned char b);

        /// <summary> Choose color pattern according to index and intensity I, as: (I, 0, 0), (0, I, 0), (0, 0, I), (I, I, 0), (I, 0, I), (0, I, I), (I, I, I).  </summary>
        /// <param name="index">     Zero-based index of the pattern to choose. The patterns are periodic, so that pattern(index) = pattern(index + c_NumPatterns). </param>
        /// <param name="intensity"> The color intensity. </param>
        /// <param name="color">     [out] The output color. </param>
        void GeneratePattern(size_t index, unsigned char intensity, T& color);

        /// <summary> Generate a color intensity, as: 255, 127, 192, 63, .... Each intensity is repeated c_NumPatterns times. </summary>
        /// <param name="index"> Zero-based index of the intensity to use in the generator. </param>
        /// <returns> The intensity. </returns>
        unsigned char GenerateIntensity(size_t index);
    };

#include "color_generator.inl"
}

#endif