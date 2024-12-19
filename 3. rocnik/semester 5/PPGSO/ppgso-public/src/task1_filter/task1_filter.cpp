// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>

// Size of the framebuffer
const unsigned int SIZE = 512;

// A simple RGB struct will represent a pixel in the framebuffer
struct Pixel {
  // TODO: Define correct data type for r, g, b channel
  char r;
  char g;
  char b;
};

int main() {
    // Initialize a framebuffer
    auto framebuffer = new Pixel[SIZE][SIZE];

    // TODO: Open file lena.raw (this is 512x512 RAW GRB format)
    std::ifstream file;
    file.open("lena.raw", std::ios::binary);
    if (!file) {
        std::cout << "File not created\n";
    } else {
        std::cout << "opened\n";
    }
    // TODO: Read data to framebuffer and close the file
    file.read(reinterpret_cast<char *>((unsigned char *) framebuffer), SIZE * SIZE * 3);
    file.close();
    // Traverse the framebuffer
  for (unsigned int y = 0; y < SIZE; y++) {
    for (unsigned int x = 0; x < SIZE; x++) {
      // TODO: Apply pixel operation gradient
        /*int rndm = (rand() % 70);
        framebuffer[x][y].r = (unsigned char) ((rndm + framebuffer[x][y].r) > 255 ? 255 : (rndm + framebuffer[x][y].r));

      framebuffer[x][y].r = 1.5*framebuffer[x][y].r;
      framebuffer[x][y].g = 1.5*framebuffer[x][y].g;
      framebuffer[x][y].b = 1.5*framebuffer[x][y].b;
      */
        float fraction = (float) x / 512;
        framebuffer[x][y].r += fraction * 255;

    }
  }

  // TODO: Open file result.raw
    std::ofstream output;
    output.open("result.raw", std::ios::binary);
  std::cout << "Generating result.raw file ..." << std::endl;

  // TODO: Write the framebuffer to the file and close it
    output.write(reinterpret_cast<const char *>((unsigned char *) framebuffer), SIZE * SIZE * 3);
  std::cout << "Done." << std::endl;
  delete[] framebuffer;
  return EXIT_SUCCESS;
}
