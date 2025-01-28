<<<<<<< HEAD
#include "rectangle.hpp"
#include <fstream>
#include <stdexcept>

// I use this macro to only get a given number of rectangles. Anything beyond that will be discarded.
#define NUMBER_OF_RECTANGLES 11

using json = nlohmann::json;

std::vector<Rectangle> parseRectangles(const std::string& filepath) {

    //open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file!");
    }
    //parse the file
    try {
        json j;
        file >> j;

        std::vector<Rectangle> rectangles;
        //if theres rectangles
        if (j.contains("rects") && j["rects"].is_array()) {
            //for each rectangle
            for (const auto& rect : j["rects"]) {
                //save rectangles until expected NUMBER_OF_RECTANGLES and erase the rest
                if(rectangles.size() > NUMBER_OF_RECTANGLES ) {
                    rectangles.erase(rectangles.begin() + NUMBER_OF_RECTANGLES, rectangles.end());
                    break;
                }
                rectangles.emplace_back(
                    rect["x"].get<int>(),
                    rect["y"].get<int>(),
                    rect["w"].get<int>(),
                    rect["h"].get<int>()
                );

                
            }
        } else {
            //if not, throw exception
            throw std::runtime_error("Error: JSON does not contain a valid 'rects' array!");
        }

        return rectangles;
    } catch (const nlohmann::json::exception& e) {
        throw std::runtime_error(std::string("JSON parsing error: ") + e.what());
    }
}

// Function to print the parsed rectangles
void printInput(const std::vector<Rectangle>& rectangles) {
    std::cout << "Input:\n";
    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << i + 1 << ": Rectangle at (" << rectangles[i].getX() << "," 
                  << rectangles[i].getY() << "), w=" << rectangles[i].getWidth() 
                  << ", h=" << rectangles[i].getHeight() << ".\n";
    }
}

// Function to detect pairwise intersections
void detectPairwiseIntersections(
    const std::vector<Rectangle>& rectangles, 
    std::vector<Intersection>* intersections) 
{
    //for each rectangle
    for (size_t i = 0; i < rectangles.size(); ++i) {
        //go through all the other exept itself and already checked
        for (size_t j = i + 1; j < rectangles.size(); ++j) {
            //check for intersection
            Rectangle intersect = rectangles[i].intersect(rectangles[j]);
            //if there´s an intersection
            if (intersect.isValid()) {
                //store the indices of the given rectangles sorted to simplify comparisson of them
                std::vector<int> indices = {static_cast<int>(i + 1), static_cast<int>(j + 1)};
                std::sort(indices.begin(), indices.end());

                bool exists = false;
                //check if the intersection already exists between the same rectangles
                for (const auto& entry : *intersections) {
                    if (entry.indices == indices && entry.rect == intersect) {
                        exists = true;
                        break;
                    }
                }
                //if it does't exists, you can add it to the list of intersections. 
                if (!exists) {
                    intersections->push_back({indices, intersect});
                }
            }
        }
    }
}

// Function to detect higher-order intersections
void detectHigherOrderIntersections(
    const std::vector<Intersection>& pairwiseIntersections, 
    std::vector<Intersection>* higherOrderIntersections) 
{
    // compare each of the intersections with the others
    for (size_t i = 0; i < pairwiseIntersections.size(); ++i) {
        for (size_t j = i + 1; j < pairwiseIntersections.size(); ++j) {
            //get the intersection of the intersections
            Rectangle intersect = pairwiseIntersections[i].rect.intersect(pairwiseIntersections[j].rect);
            //if the intersections intersect each other
            if (intersect.isValid()) {
                // save the index of it
                std::vector<int> mergedIndices = pairwiseIntersections[i].indices;
                //for each index
                for (int idx : pairwiseIntersections[j].indices) {
                    //if it is NOT already in mergedIndices, add it
                    if (std::find(mergedIndices.begin(), mergedIndices.end(), idx) == mergedIndices.end()) { 
                        mergedIndices.push_back(idx);
                    }
                }
                //sort the indexes
                std::sort(mergedIndices.begin(), mergedIndices.end());

                bool exists = false;
                //go through higherOrderIntersections 
                for (const auto& entry : *higherOrderIntersections) {
                    //if you can find it, it means it's already accounted for, so ignore it
                    if (entry.indices == mergedIndices && entry.rect == intersect) {
                        exists = true;
                        break;
                    }
                }
                //if it does't exists, you can add it to the list of higher order intersections.
                if (!exists) {
                    higherOrderIntersections->push_back({mergedIndices, intersect});
                }
            }
        }
    }
}

// Function to print all unique intersections
void printIntersections(const std::vector<Intersection>& intersections) {
    for (const auto& entry : intersections) {
        std::cout << "Between rectangle ";
        for (size_t k = 0; k < entry.indices.size(); ++k) {
            std::cout << entry.indices[k] << (k + 1 < entry.indices.size() ? ", " : "");
        }
        std::cout << " at (" << entry.rect.getX() << "," << entry.rect.getY() 
                  << "), w=" << entry.rect.getWidth() 
                  << ", h=" << entry.rect.getHeight() << ".\n";
    }
}

// check all intersections of the rectangles
void checkIntersections(const std::vector<Rectangle>& rectangles) {
    std::vector<Intersection> pairwiseIntersections;
    std::vector<Intersection> higherOrderIntersections;

    // Print the input
    printInput(rectangles);

    // Detect pairwise intersections
    detectPairwiseIntersections(rectangles, &pairwiseIntersections);

    // Detect higher-order intersections
    detectHigherOrderIntersections(pairwiseIntersections, &higherOrderIntersections);

    // Print all unique intersections
    std::cout << "Intersections:\n";
    printIntersections(pairwiseIntersections);
    printIntersections(higherOrderIntersections);
}
=======
#include "rectangle.hpp"
#include <fstream>
#include <stdexcept>

// I use this macro to only get a given number of rectangles. Anything beyond that will be discarded.
#define NUMBER_OF_RECTANGLES 11

using json = nlohmann::json;

std::vector<Rectangle> parseRectangles(const std::string& filepath) {

    //open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file!");
    }
    //parse the file
    try {
        json j;
        file >> j;

        std::vector<Rectangle> rectangles;
        //if theres rectangles
        if (j.contains("rects") && j["rects"].is_array()) {
            //for each rectangle
            for (const auto& rect : j["rects"]) {
                //save rectangles until expected NUMBER_OF_RECTANGLES and erase the rest
                if(rectangles.size() > NUMBER_OF_RECTANGLES ) {
                    rectangles.erase(rectangles.begin() + NUMBER_OF_RECTANGLES, rectangles.end());
                    break;
                }
                rectangles.emplace_back(
                    rect["x"].get<int>(),
                    rect["y"].get<int>(),
                    rect["w"].get<int>(),
                    rect["h"].get<int>()
                );

                
            }
        } else {
            //if not, throw exception
            throw std::runtime_error("Error: JSON does not contain a valid 'rects' array!");
        }

        return rectangles;
    } catch (const nlohmann::json::exception& e) {
        throw std::runtime_error(std::string("JSON parsing error: ") + e.what());
    }
}

// Function to print the parsed rectangles
void printInput(const std::vector<Rectangle>& rectangles) {
    std::cout << "Input:\n";
    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << i + 1 << ": Rectangle at (" << rectangles[i].getX() << "," 
                  << rectangles[i].getY() << "), w=" << rectangles[i].getWidth() 
                  << ", h=" << rectangles[i].getHeight() << ".\n";
    }
}

// Function to detect pairwise intersections
void detectPairwiseIntersections(
    const std::vector<Rectangle>& rectangles, 
    std::vector<Intersection>* intersections) 
{
    //for each rectangle
    for (size_t i = 0; i < rectangles.size(); ++i) {
        //go through all the other exept itself and already checked
        for (size_t j = i + 1; j < rectangles.size(); ++j) {
            //check for intersection
            Rectangle intersect = rectangles[i].intersect(rectangles[j]);
            //if there´s an intersection
            if (intersect.isValid()) {
                //store the indices of the given rectangles sorted to simplify comparisson of them
                std::vector<int> indices = {static_cast<int>(i + 1), static_cast<int>(j + 1)};
                std::sort(indices.begin(), indices.end());

                bool exists = false;
                //check if the intersection already exists between the same rectangles
                for (const auto& entry : *intersections) {
                    if (entry.indices == indices && entry.rect == intersect) {
                        exists = true;
                        break;
                    }
                }
                //if it does't exists, you can add it to the list of intersections. 
                if (!exists) {
                    intersections->push_back({indices, intersect});
                }
            }
        }
    }
}

// Function to detect higher-order intersections
void detectHigherOrderIntersections(
    const std::vector<Intersection>& pairwiseIntersections, 
    std::vector<Intersection>* higherOrderIntersections) 
{
    // compare each of the intersections with the others
    for (size_t i = 0; i < pairwiseIntersections.size(); ++i) {
        for (size_t j = i + 1; j < pairwiseIntersections.size(); ++j) {
            //get the intersection of the intersections
            Rectangle intersect = pairwiseIntersections[i].rect.intersect(pairwiseIntersections[j].rect);
            //if the intersections intersect each other
            if (intersect.isValid()) {
                // save the index of it
                std::vector<int> mergedIndices = pairwiseIntersections[i].indices;
                //for each index
                for (int idx : pairwiseIntersections[j].indices) {
                    //if it is NOT already in mergedIndices, add it
                    if (std::find(mergedIndices.begin(), mergedIndices.end(), idx) == mergedIndices.end()) { 
                        mergedIndices.push_back(idx);
                    }
                }
                //sort the indexes
                std::sort(mergedIndices.begin(), mergedIndices.end());

                bool exists = false;
                //go through higherOrderIntersections 
                for (const auto& entry : *higherOrderIntersections) {
                    //if you can find it, it means it's already accounted for, so ignore it
                    if (entry.indices == mergedIndices && entry.rect == intersect) {
                        exists = true;
                        break;
                    }
                }
                //if it does't exists, you can add it to the list of higher order intersections.
                if (!exists) {
                    higherOrderIntersections->push_back({mergedIndices, intersect});
                }
            }
        }
    }
}

// Function to print all unique intersections
void printIntersections(const std::vector<Intersection>& intersections) {
    for (const auto& entry : intersections) {
        std::cout << "Between rectangle ";
        for (size_t k = 0; k < entry.indices.size(); ++k) {
            std::cout << entry.indices[k] << (k + 1 < entry.indices.size() ? ", " : "");
        }
        std::cout << " at (" << entry.rect.getX() << "," << entry.rect.getY() 
                  << "), w=" << entry.rect.getWidth() 
                  << ", h=" << entry.rect.getHeight() << ".\n";
    }
}

// check all intersections of the rectangles
void checkIntersections(const std::vector<Rectangle>& rectangles) {
    std::vector<Intersection> pairwiseIntersections;
    std::vector<Intersection> higherOrderIntersections;

    // Print the input
    printInput(rectangles);

    // Detect pairwise intersections
    detectPairwiseIntersections(rectangles, &pairwiseIntersections);

    // Detect higher-order intersections
    detectHigherOrderIntersections(pairwiseIntersections, &higherOrderIntersections);

    // Print all unique intersections
    std::cout << "Intersections:\n";
    printIntersections(pairwiseIntersections);
    printIntersections(higherOrderIntersections);
}
>>>>>>> 049e196 (Added directory and its files)
