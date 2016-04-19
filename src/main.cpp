#include "ofMain.h"


//========================================================================
int main( int argc, char** argv ){  
  if (argc < 4) {
    cout << "Usage:\nOfFontOutlineForJS fontName dimensionInPixel string [minimumDistanceBetweenPointsInPx]" << endl;
    exit(1);
  }
  
  string fontName(argv[1]);
  int fontDimension(atoi(argv[2]));
  string stringToConvert(argv[3]);
  float minimumdistanceInPx;
  
  bool resample = argc == 5;
  if (resample) minimumdistanceInPx = atof(argv[4]);

  ofSetupOpenGL(1024,800,OF_WINDOW);			// <-------- setup the GL context
  
  ofTrueTypeFont font;
  font.loadFont(fontName, fontDimension, true, false, true);
  
  ofPoint startingPoint, previousPoint;
  
  string varName = "charsOutlines";
  
  cout << "var charsString = \"" << stringToConvert << "\";" << endl;
  cout << "var charsOutlines = [];" << endl;
  
  vector<ofTTFCharacter> chars = font.getStringAsPoints(stringToConvert);
  for (unsigned int i = 0; i < chars.size(); ++i) {
    vector < ofPolyline > lines = chars[i].getOutline();
    cout << varName << "[" << i << "] = [];" << endl;
    for (unsigned int li = 0; li < lines.size(); ++li) {
      cout << varName << "[" << i << "][" << li << "] = [" << endl;
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
}
