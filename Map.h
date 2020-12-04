/**
 * \class Map
 *
 * \brief Map class
 *
 * This is a Map class. This is stores the datas from a map file. 
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.11.30. 14:00
 *
 * Created on: 2020.11.30. 14:00
*/
#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <exception>

class Map{
protected:
    std::vector<std::string> mapvector;
public: 
    /// This is a type named enum, and it returns Free or Wall
    enum type{
        Free,
        Wall
    };

    /// This is a constructor for the Map Class
    Map();
    /// This is a constructor for the Map Class, this constructor reads the file in
    explicit Map(std::string filename);

    /// This method returns the map type from the given coordinates x and y
    /**
    * \return The coordinate given Map type enum, it can be Free or Wall
    */
    Map::type get(long unsigned int x, long unsigned int y) const;

    /// This method is an exception if the given coordinates are wrong
    class WrongIndexException : public std::runtime_error {
        public:
            explicit WrongIndexException(const std::string& msg) : std::runtime_error(msg){};

    };
    ~Map(){};
};