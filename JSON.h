/**
 * \class JSON
 *
 * \brief JSON parser class
 *
 * This is a JSON parser class. This class accepts 3 formats: filename, string, istream, and gets the data from there and converts it to a map. 
 *
 * \author b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.10.18. 16:45
 *
 * Created on: 2020.10.18. 16:45
*/
#pragma once
#ifndef JSON_H
#define JSON_H
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <istream>
#include <exception>

class JSON
{
private:
        std::map<std::string,std::string> adatok;
        void internalParser(std::string data);
        static void keyTester(std::string data, std::string key);
        void internalStringParse(std::string data, std::string key);
        void internalNumParse(std::string data, std::string key);
public:
        /// This is a constructor for JSON
        JSON();

        /// This is a constructor with a map
        JSON(std::map<std::string,std::string> adatok_ /**< [in] A map with the datas */);

        ///This is a destructot for JSON
        ~JSON();


        ///This is the file parser.
        /**
        * \return A map with the parsed datas. It has name, hp, dmg, attackspeed keys.
        * \exception std::invalid_argument file cannot opened, or the data has duplicated keys.
        */
        std::map<std::string,std::string> parseFile(std::string fname/**< [in] Name of the file */);


        ///This is the String parser.
        /**
        * \return A map with the parsed datas. It has name, hp, dmg, attackspeed keys.
        * \exception std::invalid_argument The data has duplicated keys.
        */
        std::map<std::string,std::string> parseString(std::string data/**< [in] The input string */);


        ///This is a getter for the Adatok map.
        /**
        * \return Returns the setted map with the parsed datas. It has name, hp, dmg, attackspeed keys.
        */
        std::map<std::string,std::string> getAdatok();


        ///This is the istream manager. It gets an input stream and make the adatok map, which is accessible through getAdatok.
        /**
        * \exception std::invalid_argument The data has duplicated keys.
        */
        friend std::istream& operator>>(std::istream&, JSON& j);

        template<typename T>
        T get(std::string data){
                T ret = adatok.at("data");
                return ret; 
        }

        static JSON parseFromFile(std::string fname);
        
        class ParseException : public std::logic_error {
                public:
                        ParseException(const std::string& msg) : std::logic_error(msg){};
        };
        unsigned int count(const std::string& data);
};

#endif //JSON_H
