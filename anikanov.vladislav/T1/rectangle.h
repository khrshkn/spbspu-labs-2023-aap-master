#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iosfwd>
#include "shape.h"

class Rectangle : Shape {
private:
  double width;
  double height;
  PointT cPoint;
public:
  explicit Rectangle();

  void setWidth(double);

  double getWidth() const;

  void setHeight(double);

  double getHeight() const;

  PointT getCPoint() const;

  long long getArea() override;

  RectangleT getFrameRect() override;

  void move(PointT) override;

  void move(double x, double y) override;

  void scale(double) override;

  friend std::istream &operator>>(std::istream &, Rectangle &);
};

#endif
