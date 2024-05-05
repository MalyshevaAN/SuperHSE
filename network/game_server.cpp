#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include "server.hpp"


int main(){
    super_hse::server game_server{};
    game_server.run();
    return 0;
}

