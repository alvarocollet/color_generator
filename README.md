# Color Generator
Create sets of visually distinctive colors for easy visualization in plots. The colors are generated procedurally, so you can create a large number of colors with no repetition (up to 255*7 = 1785 distinct colors). However, it is hard to notice the actual differences between colors past the first 15-20 colors.

This is a self-contained, header-only library (only dependent on STL vectors). This code is based on a stack overflow discussion available [here](http://stackoverflow.com/questions/309149/generate-distinctly-different-rgb-colors-in-graphs).

Its usage is very simple. Just #include "color_generator.h" in a cpp file and create the ColorGenerator object:

```
ColorGenerator<RGBColor> colorGenerator(NumColors); // precompute a list of NumColors
```

The `RGBColor` template type is any object that can be initialized as `T{ red_color, green_color, blue_color };`
Then, to access your generated colors:

```
RGBColor c = colorGenerator[idx]; // Color number 'idx', returns object of type 'RGBColor'
```

Or, alternatively, you query an arbitrariy (not precomputed) color:

```
RGBColor c;
colorGenerator.GenerateColor(idx /* index of color */, c /* output, passed by ref */);
Enjoy!
