// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Image.h"
#include "processing.h"
using namespace std;

int main(int argc, char *argv[] ) {
  string filename(argv[1]);
  string outFile(argv[2]);
  ifstream fin;
  ofstream fout;
  fin.open(filename);
  fout.open(outFile);
  if(!fin.is_open()) {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }
  if(!fout.is_open()) {
    cout << "Error opening file: " << outFile << endl;
    return 1;
  }

  Image *img = new Image;
  Image_init(img, fin);

  if(argc == 4) {
    int newWidth = atoi(argv[3]);
    if(newWidth <= 0 || newWidth > Image_width(img)) {
      cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
       << "WIDTH and HEIGHT must be less than or equal to original" << endl;
       delete img;
       return 1;
    }
    seam_carve(img, newWidth, Image_height(img));
    Image_print(img, fout);
  }
  else if (argc == 5) {
    int newWidth = atoi(argv[3]);
    int newHeight = atoi(argv[4]);
    if(newWidth <= 0 || newWidth > Image_width(img) 
    || newHeight <= 0 || newHeight > Image_height(img)) {
      cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
       << "WIDTH and HEIGHT must be less than or equal to original" << endl;
       delete img;
       return 1;
    }
    seam_carve(img, newWidth, newHeight);
    Image_print(img, fout);
  }
  else {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     delete img;
    return 1;
  }

  delete img;
  return 0;
}
