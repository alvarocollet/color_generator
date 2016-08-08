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

//----------------------------------------------------------------------------
template <typename T>
unsigned char AC::ColorGenerator<T>::ReverseBits(unsigned char b)
{
    // Reverse bits in range [0, 255], so that, e.g., 11010000 becomes 00001011.
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

//----------------------------------------------------------------------------
template <typename T>
void AC::ColorGenerator<T>::GeneratePattern(size_t index, unsigned char intensity, T& color)
{
    switch (index % c_NumPatterns) {
    case 0:
        color = T{ intensity, 0, 0 }; break;
    case 1:
        color = T{ 0, intensity, 0 }; break;
    case 2:
        color = T{ 0, 0, intensity }; break;
    case 3:
        color = T{ intensity, intensity, 0 }; break;
    case 4:
        color = T{ intensity, 0, intensity }; break;
    case 5:
        color = T{ 0, intensity, intensity }; break;
    case 6:
        color = T{ intensity, intensity, intensity }; break;
    }
}

//----------------------------------------------------------------------------
template <class T>
unsigned char AC::ColorGenerator<T>::GenerateIntensity(size_t index)
{
    // The generated intensities are 255, 127, 191, 63...
    unsigned char value = static_cast<unsigned char>((index / c_NumPatterns) % 256);
    return static_cast<unsigned char>(~ReverseBits(value));
}

//----------------------------------------------------------------------------
template <class T>
void AC::ColorGenerator<T>::Reset(size_t numColors)
{
    m_colors.resize(numColors);
    for (size_t i = 0; i < numColors; ++i)
        GenerateColor(i, m_colors[i]);
}

//----------------------------------------------------------------------------
template <class T>
void AC::ColorGenerator<T>::GenerateColor(size_t index, T& color)
{
    GeneratePattern(index, GenerateIntensity(index), color);
}
