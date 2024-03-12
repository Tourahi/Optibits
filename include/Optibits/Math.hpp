#pragma once

#include <numbers>

namespace Optibits
{

  /// @brief 
  /// @param min (inclusive) 
  /// @param max (exclusive) 
  /// @return 
  double random(double min, double max);

  inline double degreesToRadians(double angle)
  {
    return angle * std::numbers::pi / 180;
  }

  inline double radiansToDegrees(double angle)
  {
    return angle * 180 / std::numbers::pi;
  }

  inline double radiansToAngle(double angle)
  {
    return radiansToAngle(angle) + 90;
  }

  inline double angleToRadians(double angle)
  {
    return degreesToRadians(angle - 90);
  }

  double offsetX(double angle, double radius);
  
  double offsetY(double angle, double radius);

  double angle(double fromX, double fromY, double toX, double toY, double fallback = 0);

  double angleDiff(double angle1, double angle2);

  double normalizeAngle(double angle);

  int wrap(int value, int min, int max);
  double wrap(double value, double min, double max);

  double distance(double x1, double y1, double x2, double y2);
}