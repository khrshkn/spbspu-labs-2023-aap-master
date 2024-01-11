#include "shape.hpp"
#include "parallelogram.hpp"
#include "rectangle.hpp"
#include "concave.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main()
{
  redko::Shape** shapes = new redko::Shape * [1000] {};
  point_t* points = nullptr;
  int shapesCounter = 0;
  std::string shape, type = "";
  bool some_descr_is_wrong = false;
  bool shapes_are_scaled = false;
  double x, y;
  std::stringstream shapeStream("");

  while (!std::cin.eof())
  {
    std::getline(std::cin, shape);
    shapeStream << shape;
    shapeStream >> type;
    if (type == "SCALE")
    {
      if (shapesCounter == 0)
      {
        std::cerr << "no shapes to scale\n";
        return 2;
      }
      double coefficient;
      if (!(shapeStream >> x >> y >> coefficient) || coefficient <= 0)
      {
        std::cerr << "wrong scale parameters\n";
        return 2;
      }
      double areasSum = 0;
      double scaledAreasSum = 0;
      rectangle_t frame = {};
      double* frameXY = new double[shapesCounter * 4];
      double* scaledFrameXY = new double[shapesCounter * 4];
      for (int i = 0; i < shapesCounter; i++)
      {
        areasSum += shapes[i]->getArea();
        frame = shapes[i]->getFrameRect();
        frameXY[4 * i] = frame.pos_.x_ - frame.width_ / 2;
        frameXY[4 * i + 1] = frame.pos_.y_ - frame.height_ / 2;
        frameXY[4 * i + 2] = frame.pos_.x_ + frame.width_ / 2;
        frameXY[4 * i + 3] = frame.pos_.y_ + frame.height_ / 2;

        shapes[i]->scale({ x, y }, coefficient);

        scaledAreasSum += shapes[i]->getArea();
        frame = shapes[i]->getFrameRect();
        scaledFrameXY[4 * i] = frame.pos_.x_ - frame.width_ / 2;
        scaledFrameXY[4 * i + 1] = frame.pos_.y_ - frame.height_ / 2;
        scaledFrameXY[4 * i + 2] = frame.pos_.x_ + frame.width_ / 2;
        scaledFrameXY[4 * i + 3] = frame.pos_.y_ + frame.height_ / 2;
      }
      std::cout << std::fixed << std::setprecision(1) << areasSum;
      for (int i = 0; i < shapesCounter * 4; i++)
      {
        std::cout << ' ' << frameXY[i];
      }
      std::cout << '\n' << scaledAreasSum;
      for (int i = 0; i < shapesCounter * 4; i++)
      {
        std::cout << ' ' << scaledFrameXY[i];
      }
      std::cout << '\n';
      if (some_descr_is_wrong)
      {
        std::cerr << "errors in the description of supported shapes\n";
      }
      delete[] shapes;
      delete[] frameXY;
      delete[] scaledFrameXY;
      return 0;
    }
    points = new point_t[4];
    int i = 0;
    bool descr_is_wrong = false;

    if (type == "RECTANGLE")
    {
      while (shapeStream >> x)
      {
        if (i > 1 || !(shapeStream >> y))
        {
          some_descr_is_wrong = true;
          descr_is_wrong = true;
          break;
        }
        points[i++] = { x, y };
      }
      if (!descr_is_wrong && i == 2)
      {
        shapes[shapesCounter++] = new redko::Rectangle(points[0], points[1]);
      }
    }
    else if (type == "PARALLELOGRAM")
    {
      while (shapeStream >> x)
      {
        if (i > 2 || !(shapeStream >> y))
        {
          some_descr_is_wrong = true;
          descr_is_wrong = true;
          break;
        }
        points[i++] = { x, y };
      }
      if (points[0].y_ != points[1].y_ && points[2].y_ != points[0].y_)
      {
        some_descr_is_wrong = true;
      }
      else if (!descr_is_wrong && i == 3)
      {
        shapes[shapesCounter++] = new redko::Parallelogram(points[0], points[1], points[2]);
      }
    }
    else if (type == "CONCAVE")
    {
      while (shapeStream >> x)
      {
        if (i > 3 || !(shapeStream >> y))
        {
          some_descr_is_wrong = true;
          descr_is_wrong = true;
          break;
        }
        points[i++] = { x, y };
      }
      double firstTriangle = abs((points[0].x_ * (points[1].y_ - points[3].y_) + \
        points[1].x_ * (points[3].y_ - points[0].y_) + points[3].x_ * (points[0].y_ - points[1].y_)) / 2);
      double secondTriangle = abs((points[0].x_ * (points[3].y_ - points[2].y_) + \
        points[3].x_ * (points[2].y_ - points[0].y_) + points[2].x_ * (points[0].y_ - points[3].y_)) / 2);
      double thirdTriangle = abs((points[3].x_ * (points[1].y_ - points[2].y_) + \
        points[1].x_ * (points[2].y_ - points[3].y_) + points[2].x_ * (points[3].y_ - points[1].y_)) / 2);
      double fourthTriangle = abs((points[0].x_ * (points[1].y_ - points[2].y_) + \
        points[1].x_ * (points[2].y_ - points[0].y_) + points[2].x_ * (points[0].y_ - points[1].y_)) / 2);
      if (firstTriangle == 0 || secondTriangle == 0 || thirdTriangle == 0 || fourthTriangle == 0 || \
        firstTriangle + secondTriangle + thirdTriangle != fourthTriangle)
      {
        some_descr_is_wrong = true;
      }
      else if (!descr_is_wrong && i == 4)
      {
        shapes[shapesCounter++] = new redko::Concave(points[0], points[1], points[2], points[3]);
      }
    }
    delete[] points;
    shapeStream.str(std::string());
    shapeStream.clear();
  }
  if (!shapes_are_scaled)
  {
    std::cerr << "shapes was not scaled\n";
    return 2;
  }
}
