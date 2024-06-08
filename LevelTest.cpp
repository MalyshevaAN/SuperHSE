#ifndef LEVEL_TEST
#define LEVEL_TEST

#include "level_info.hpp"
#include "Level.hpp"
#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

namespace super_hse{

void checkLevelInfoConstructor(){
    LevelInfo levelInfoEmpty;
    assert(levelInfoEmpty.colliderName.size() == 0);
    assert(levelInfoEmpty.entityLayerName.size() == 0);
    assert(levelInfoEmpty.tileLayerName.size() == 0);

    LevelInfo levelInfoTestFile("assets/files/level1_test.txt");
    assert(levelInfoTestFile.filename == "../assets/tilemaps/first_level2.ldtk");
    assert(levelInfoTestFile.tileLayerName.size() == 5);
    assert(levelInfoTestFile.entityLayerName.size() == 1);
    assert(levelInfoTestFile.colliderName.size() == 2);

    std::string descriptionFile = "wtf52";
    std::string excpectedErrorMessage = "Cannot find \'" + descriptionFile + "\' description file\n";
    try {
        LevelInfo levelInfoWrongFile(descriptionFile);
    }catch (std::runtime_error  &e){
        assert(e.what() == excpectedErrorMessage);
    }

}

void checkLevelConstructor(){
    Level levelFromRightFileName("first_level2.ldtk");
    assert(levelFromRightFileName.ldtk_filename == "first_level2.ldtk");

    std::string projectName = "wtf52";
    std::string expectedErrorMessage = "Cannot find \'" + projectName + "\'' project\n";
    try{
        Level levelWithWrongFileName(projectName);
    }catch(ldtkException &e){
        assert(e.what() == expectedErrorMessage);
    }
}

}
int main(){
    super_hse::checkLevelInfoConstructor();
    super_hse::checkLevelConstructor();
    return 0;
}
#endif
