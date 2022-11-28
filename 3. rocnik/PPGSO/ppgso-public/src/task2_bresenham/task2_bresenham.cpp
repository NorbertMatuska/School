// Task 3 - Implement Bresenham drawing alg.
//        - Draw a star using lines
//        - Make use of std::vector to define the shape
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <ppgso/ppgso.h>

# define PI 3.1415926535

// Size of the framebuffer
const unsigned int SIZE = 512;

struct Point {
  int x,y;
};

// Bresenham drawing algorithm
void drawLine(ppgso::Image &framebuffer, Point &from, Point &to) {
    {
        int tox = to.x;
        int fromx = from.x;
        int toy = to.y;
        int fromy = from.y;

        if (to.x < from.x) {
            std::swap(fromx, tox);
            std::swap(fromy, toy);
        }

        if (from.x == to.x && from.y == to.y)
            return;

        int dx, dy, dx_abs, dy_abs;
        dx = tox - fromx;
        dy = toy - fromy;
        dx_abs = abs(dx);
        dy_abs = abs(dy);

        int base_coor, catching_coor, end_coor, plus_error, minus_error, base_error;
        if (dy_abs <= dx_abs) {
            base_coor = fromx;
            catching_coor = fromy;
            end_coor = tox;
            plus_error = dy_abs;
            minus_error = dy_abs - dx_abs;
            base_error = 2 * dy_abs - dx_abs;
        } else {
            if (dy > 0) {
                catching_coor = fromx;
                base_coor = fromy;
                end_coor = toy;
            } else {
                catching_coor = tox;
                base_coor = toy;
                end_coor = fromy;
            }
            plus_error = dx_abs;
            minus_error = dx_abs - dy_abs;
            base_error = 2 * dx_abs - dy_abs;
        }


        while (base_coor <= end_coor) {
            if (base_coor >= 0 && base_coor < SIZE && catching_coor >= 0 && catching_coor < SIZE)
                if (dy_abs <= dx_abs)
                    framebuffer.setPixel(base_coor, catching_coor, 255, 255, 255);
                else
                    framebuffer.setPixel(catching_coor, base_coor, 255, 255, 255);
            base_coor += 1;
            if (base_error < 0)
                base_error += 2 * plus_error;
            else {
                if (dy > 0)
                    catching_coor += 1;
                else
                    catching_coor -= 1;

                base_error += 2 * (minus_error);
            }
        }
    }
}




int main()
{
  // Use ppgso::Image as our framebuffer
  ppgso::Image framebuffer(SIZE, SIZE);

  std::vector<Point> points;
    int offset_x = SIZE / 2, offset_y = SIZE / 2;
    int r1 =150, r2 = 200;

    for (int i = 0; i < 13; i++) {
        int x = r1 * sin(i * PI / 6);
        int y = r1 * cos(i * PI / 6);
        points.push_back({x + offset_x, y + offset_y});
        //printf("R1 x: %d y: %d\n", x+offset_x, y+offset_y);

        x = r2 * sin(i * PI / 6);
        y = r2 * cos(i * PI / 6);
        points.push_back({x + offset_x, y + offset_y});
        //printf("R2 x: %d y: %d\n", x+offset_x, y+offset_y);

    }
  // Draw lines
  for(unsigned int i = 0; i < points.size() - 1; i++) {
      drawLine(framebuffer, points[i], points[i + 1]);
  }

    // Save the result
  std::cout << "Generating task2_bresenham.bmp file ..." << std::endl;
  ppgso::image::saveBMP(framebuffer, "task2_bresenham.bmp");

  std::cout << "Done." << std::endl;
  return EXIT_SUCCESS;
}

