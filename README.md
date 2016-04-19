## Command line programe that outputs a JS style array of points that represent the outline of the string given as an argument

This is a command line program, using **Openframeworks**. (On mac you need to build it and use the Contents/MacOS application)

The goal of this is to use it for those typographic effects with canvas, THREE or processing.js that require the knowledge of the convex hull of a string of characters.
It can resample the output shape so the number of output segments is smaller.

The command line syntax is

OfRenderJSAlphabet fontName dimensionInPixel string [minimumDistanceBetweenPointsInPx]

It will output a JS formatted array to the standard console output, containing the segments that form the string of characters. Of course it's possible to pipe the output in a file.
if string equals ALPHABET, the whole alphabet will be output. Example output:

var charsOutlines = [];
charsOutlines['0'] = [];
charsOutlines['0'][0] = [
  { x: 35.9844, y: -76},
  { x: 30.2559, y: -75.5861},
  { x: 24.9739, y: -74.3385},
  { x: 20.1859, y: -72.2481},
  { x: 15.9395, y: -69.306},
  { x: 12.2822, y: -65.5033},
  { x: 9.26165, y: -60.831},
  .....
];

### Arguments

fontName can be either the name of a font installed in the OS (tested on OSX only) or the path to a font file. 

Dimension: the font dimension specified in Pixels.

String is optional: if specified

minimumDistanceBetweenPointsInPx: basically resamples the shape, keeping just the points that have at least a certain distance from the previous one
