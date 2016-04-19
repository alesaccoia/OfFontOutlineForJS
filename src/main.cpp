#include "ofMain.h"


//========================================================================
int main( int argc, char** argv ){  
  if (argc < 4) {
    cout << "Usage:\nOfFontOutlineForJS fontName dimensionInPixel string [minimumDistanceBetweenPointsInPx]" << endl;
    cout << "if the string is ALPHABET, then all the alphabet is outputted as a single file " << endl;
    exit(1);
  }
  
  string fontName(argv[1]);
  int fontDimension(atoi(argv[2]));
  string stringToConvert(argv[3]);
  
  bool allAlphabet = false;
  if (stringToConvert == "ALPHABET") {
    allAlphabet = true;
  }
  float minimumdistanceInPx;
  
  bool resample = argc == 5;
  if (resample) minimumdistanceInPx = atof(argv[4]);

  ofSetupOpenGL(1024,800,OF_WINDOW);			// <-------- setup the GL context
  
  ofTrueTypeFont font;
  font.loadFont(fontName, fontDimension, true, false, true);
  if (!font.isLoaded()) {
    cerr << "Font name not recognized or impossible to read font" << endl;
    exit(1);
  }
  
  ofPoint startingPoint, previousPoint;
  
  char c = '0' - 1;
  
  
  cout << "var charsOutlines = [];" << endl;
  
  do {
    if (allAlphabet) {
      ++c;
      if (c == ('9' + 1)) c = 'A';
      if (c == ('Z' + 1)) c = 'a';
      if (c == ('z' + 1)) break;
      stringToConvert = c;
    }
    
    string varName = "charsOutlines[\'" + stringToConvert + "\']";
    
    cout << varName << " = [];" << endl;
    
    vector<ofTTFCharacter> chars = font.getStringAsPoints(stringToConvert);
    for (unsigned int i = 0; i < chars.size(); ++i) {
      vector < ofPolyline > lines = chars[i].getOutline();
      if (!allAlphabet) {
        cout << varName << "[" << i << "] = [];" << endl;
      }
      for (unsigned int li = 0; li < lines.size(); ++li) {
        if (!allAlphabet) {
          cout << varName << "[" << i << "][" << li << "] = [" << endl;
        } else {
          cout << varName << "[" << li << "] = [" << endl;
        }
        startingPoint = previousPoint = lines[li][1];
        cout << "  { x: " << startingPoint.x << ", y: " << startingPoint.y << "}";
        for (unsigned int j = 2; j < lines[li].size(); ++j) {
          ofPoint& currentPoint = lines[li][j];
          if (!resample || (currentPoint.distance(previousPoint) >= minimumdistanceInPx)) {
            cout << "," << endl;
            previousPoint = currentPoint;
            cout << "  { x: " << currentPoint.x << ", y: " << currentPoint.y << "}";
          }
        }
        cout << endl << "];" << endl;
      } // end polylines for a char
      cout << endl;
    } // end char
    
  } while (allAlphabet);
}
