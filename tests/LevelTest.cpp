#ifndef LEVEL_TEST_CPP
#define LEVEL_TEST_CPP

#include <cassert>
#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Level.hpp"
#include "level_info.hpp"

namespace super_hse {

static std::filesystem::path p(std::filesystem::current_path());

void checkLevelInfoConstructor() {
    LevelInfo levelInfoEmpty;
    assert(levelInfoEmpty.colliderName.size() == 0);
    assert(levelInfoEmpty.entityLayerName.size() == 0);
    assert(levelInfoEmpty.tileLayerName.size() == 0);
    LevelInfo levelInfoTestFile(
        p.parent_path().parent_path().string() + "/assets/files/level1_test.txt"
    );
    assert(
        levelInfoTestFile.filename == "../assets/tilemaps/first_level2.ldtk"
    );
    assert(levelInfoTestFile.tileLayerName.size() == 5);
    assert(levelInfoTestFile.entityLayerName.size() == 1);
    assert(levelInfoTestFile.colliderName.size() == 2);

    std::string descriptionFile = "wtf52";
    std::string excpectedErrorMessage =
        "Cannot find \'" + descriptionFile + "\' description file\n";
    try {
        LevelInfo levelInfoWrongFile(descriptionFile);
    } catch (std::runtime_error &e) {
        assert(e.what() == excpectedErrorMessage);
    }
}

void checkLevelConstructor() {
    Level levelFromRightFileName(
        p.parent_path().parent_path().string() +
        "/assets/tilemaps/first_level2.ldtk"
    );
    assert(
        levelFromRightFileName.ldtk_filename ==
        p.parent_path().parent_path().string() +
            "/assets/tilemaps/first_level2.ldtk"
    );

    std::string projectName = "wtf52";
    std::string expectedErrorMessage =
        "Cannot find \'" + projectName + "\'' project\n";
    try {
        Level levelWithWrongFileName(projectName);
    } catch (ldtkException &e) {
        assert(e.what() == expectedErrorMessage);
    }
}

void level_test() {
    super_hse::checkLevelInfoConstructor();
    super_hse::checkLevelConstructor();
}

}  // namespace super_hse
#endif
