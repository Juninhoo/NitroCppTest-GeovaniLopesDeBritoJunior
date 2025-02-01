#pragma once
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"

// Forward declarations
struct Intersection;
class Rectangle;

class Rectangle {
private:
    int x, y, width, height;

public:
    // Constructor
    Rectangle(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Calculate intersection with another rectangle
    Rectangle intersect(const Rectangle& other) const {
        int ix = std::max(x, other.x);
        int iy = std::max(y, other.y);
        int iw = std::min(x + width, other.x + other.width) - ix;
        int ih = std::min(y + height, other.y + other.height) - iy;

        if (iw > 0 && ih > 0) {
            return Rectangle(ix, iy, iw, ih);
        }

        return Rectangle(0, 0, 0, 0); // No intersection
    }

    // Check if the rectangle has a valid area
    bool isValid() const {
        return width > 0 && height > 0;
    }

    // Calculate the area of the rectangle
    int area() const {
        return width * height;
    }

    // Print rectangle details
    void print(const std::string& label = "") const {
        if (!label.empty()) {
            std::cout << label << ": ";
        }
        std::cout << "Rectangle at (" << x << "," << y << "), w=" << width << ", h=" << height << ".";
    }

    bool operator==(const Rectangle& other) const {
    return x == other.x && y == other.y &&
           width == other.width && height == other.height;
}
};

// Function declarations
std::vector<Rectangle> parseRectangles(const std::string& filepath);
void detectPairwiseIntersections(
    const std::vector<Rectangle>& rectangles, 
    std::vector<Intersection>* intersections
);

void detectHigherOrderIntersections(
    const std::vector<Intersection>& pairwiseIntersections, 
    std::vector<Intersection>* higherOrderIntersections
);

void printInput(const std::vector<Rectangle>& rectangles);

void printIntersections(const std::vector<Intersection>& intersections);
void checkIntersections(const std::vector<Rectangle>& rectangles);

// intersection struct
struct Intersection {
    std::vector<int> indices; // Indices of rectangles involved
    Rectangle rect;           // Overlapping rectangle
};

#endif /*RECTANGLE_HPP*/