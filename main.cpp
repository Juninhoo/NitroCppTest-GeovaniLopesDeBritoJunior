/*-------------------------------------------------------------------------------------*/
//Name: Geovani Lopes de Brito Junior
//Program: retangles intersactions and areas from json file
//Company: Nitro
//Unit Test: googleTest
/*-------------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "rectangle.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file_path>" << std::endl;
        return 1;
    }
    try {
        // Path to the JSON file
        const std::string filepath = argv[1];

        // Parse rectangles from the JSON file
        std::vector<Rectangle> rectangles = parseRectangles(filepath);

        // Check and print intersections
        checkIntersections(rectangles);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
	return 0;
}