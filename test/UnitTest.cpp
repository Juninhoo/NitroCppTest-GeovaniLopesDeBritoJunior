#include <gtest/gtest.h>
#include "../rectangle.hpp"
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

// Test Rectangle Constructor and Getters
TEST(RectangleTest, ConstructorAndGetters) {
    Rectangle rect(10, 20, 30, 40);
    EXPECT_EQ(rect.getX(), 10);
    EXPECT_EQ(rect.getY(), 20);
    EXPECT_EQ(rect.getWidth(), 30);
    EXPECT_EQ(rect.getHeight(), 40);
}

// Test Rectangle Intersection (Valid Case)
TEST(RectangleTest, ValidIntersection) {
    Rectangle rect1(0, 0, 4, 4);
    Rectangle rect2(2, 2, 4, 4);
    Rectangle result = rect1.intersect(rect2);

    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.getX(), 2);
    EXPECT_EQ(result.getY(), 2);
    EXPECT_EQ(result.getWidth(), 2);
    EXPECT_EQ(result.getHeight(), 2);
    EXPECT_EQ(result.area(), 4);
}

// Test Rectangle Intersection (No Intersection)
TEST(RectangleTest, NoIntersection) {
    Rectangle rect1(0, 0, 4, 4);
    Rectangle rect2(5, 5, 2, 2);
    Rectangle result = rect1.intersect(rect2);

    EXPECT_FALSE(result.isValid());
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 0);
    EXPECT_EQ(result.getHeight(), 0);
    EXPECT_EQ(result.area(), 0);
}

// Test Rectangle Area Calculation
TEST(RectangleTest, AreaCalculation) {
    Rectangle rect(5, 5, 10, 15);
    EXPECT_EQ(rect.area(), 150);

    Rectangle emptyRect(5, 5, 0, 0);
    EXPECT_EQ(emptyRect.area(), 0);
}

// Test Rectangle isValid Method
TEST(RectangleTest, IsValidMethod) {
    Rectangle validRect(0, 0, 10, 10);
    EXPECT_TRUE(validRect.isValid());

    Rectangle invalidRect(0, 0, 0, 0);
    EXPECT_FALSE(invalidRect.isValid());
}

// Test Rectangle Print Method
TEST(RectangleTest, PrintMethod) {
    Rectangle rect(10, 20, 30, 40);

    // Redirect std::cout to capture output
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    rect.print("TestRectangle");

    // Restore std::cout and check output
    std::cout.rdbuf(oldCout);
    EXPECT_EQ(output.str(), "TestRectangle: Rectangle at (10,20), w=30, h=40.");
}

// Test for parsing JSON file
TEST(JsonTest, ParseRectangles) {
    // Create a temporary JSON file for testing
    std::string testJsonPath = "test_rectangles.json";
    std::ofstream jsonFile(testJsonPath);
    jsonFile << R"({
        "rects": [
            { "x": 0, "y": 0, "w": 4, "h": 4 },
            { "x": 2, "y": 2, "w": 3, "h": 3 },
            { "x": 5, "y": 5, "w": 2, "h": 2 }
        ]
    })";
    jsonFile.close();

    // Parse rectangles from JSON
    std::vector<Rectangle> rectangles = parseRectangles(testJsonPath);

    // Check the parsed rectangles
    ASSERT_EQ(rectangles.size(), 3);

    // Validate individual rectangles
    EXPECT_EQ(rectangles[0].getX(), 0);
    EXPECT_EQ(rectangles[0].getY(), 0);
    EXPECT_EQ(rectangles[0].getWidth(), 4);
    EXPECT_EQ(rectangles[0].getHeight(), 4);

    EXPECT_EQ(rectangles[1].getX(), 2);
    EXPECT_EQ(rectangles[1].getY(), 2);
    EXPECT_EQ(rectangles[1].getWidth(), 3);
    EXPECT_EQ(rectangles[1].getHeight(), 3);

    EXPECT_EQ(rectangles[2].getX(), 5);
    EXPECT_EQ(rectangles[2].getY(), 5);
    EXPECT_EQ(rectangles[2].getWidth(), 2);
    EXPECT_EQ(rectangles[2].getHeight(), 2);

    // Cleanup: Remove the temporary JSON file
    fs::remove(testJsonPath);
}

// Test for missing or malformed JSON file
TEST(JsonTest, MissingOrMalformedJsonFile) {
    std::string invalidPath = "non_existent.json";

    // Check that parsing a non-existent file throws an exception
    EXPECT_THROW(parseRectangles(invalidPath), std::runtime_error);

    // Create a malformed JSON file
    std::string malformedJsonPath = "malformed.json";
    std::ofstream jsonFile(malformedJsonPath);
    jsonFile << R"({ "rects": [ { "x": 0, "y": 0, "w": 4 } ])"; // Missing "h"
    jsonFile.close();

    // Check that parsing the malformed JSON file throws an exception
    EXPECT_THROW(parseRectangles(malformedJsonPath), std::runtime_error);

    // Cleanup: Remove the malformed JSON file
    fs::remove(malformedJsonPath);
}


// Test detectPairwiseIntersections Function
TEST(IntersectionTest, DetectPairwiseIntersections) {
    std::vector<Rectangle> rectangles = {
        Rectangle(0, 0, 10, 10),
        Rectangle(5, 5, 10, 10),
        Rectangle(15, 15, 5, 5),
        Rectangle(3, 3, 2, 2)
    };

    std::vector<Intersection> pairwiseIntersections;

    // Call detectPairwiseIntersections
    detectPairwiseIntersections(rectangles, &pairwiseIntersections);

    // Check that the pairwise intersections are detected correctly
    ASSERT_EQ(pairwiseIntersections.size(), 2); // Expect 2 unique pairwise intersections

    // Validate each intersection
    EXPECT_EQ(pairwiseIntersections[0].indices, (std::vector<int>{1, 2}));
    EXPECT_EQ(pairwiseIntersections[0].rect, Rectangle(5, 5, 5, 5));

    EXPECT_EQ(pairwiseIntersections[1].indices, (std::vector<int>{1, 4}));
    EXPECT_EQ(pairwiseIntersections[1].rect, Rectangle(3, 3, 2, 2));
}

// Test for edge case: No intersections
TEST(IntersectionTest, NoIntersections) {
    std::vector<Rectangle> rectangles = {
        Rectangle(0, 0, 10, 10),
        Rectangle(20, 20, 5, 5),
        Rectangle(30, 30, 5, 5)
    };

    std::vector<Intersection> pairwiseIntersections;
    std::vector<Intersection> higherOrderIntersections;

    detectPairwiseIntersections(rectangles, &pairwiseIntersections);
    detectHigherOrderIntersections(pairwiseIntersections, &higherOrderIntersections);

    EXPECT_TRUE(pairwiseIntersections.empty());
    EXPECT_TRUE(higherOrderIntersections.empty());
}
// Test detectHigherOrderIntersections Function
TEST(IntersectionTest, DetectHigherOrderIntersections) {
    // Prepare pairwise intersections as input
    std::vector<Intersection> pairwiseIntersections = {
        {{1, 2}, Rectangle(5, 5, 5, 5)},
        {{1, 3}, Rectangle(7, 7, 3, 3)},
        {{2, 3}, Rectangle(7, 7, 3, 3)}
    };

    std::vector<Intersection> higherOrderIntersections;
    higherOrderIntersections.reserve(1);  // Reserve space for 1 higher order intersection

    // Call detectHigherOrderIntersections
    detectHigherOrderIntersections(pairwiseIntersections, &higherOrderIntersections);

    // Check that the higher-order intersections are detected correctly
    ASSERT_EQ(higherOrderIntersections.size(), 1); // Expect 1 higher-order intersection

    // Validate the higher-order intersection
    EXPECT_EQ(higherOrderIntersections[0].indices, (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(higherOrderIntersections[0].rect, Rectangle(7, 7, 3, 3));
}
