#include "game.hpp"
#include "sql.hpp"
#include <SFML/Network.hpp>
#include "hse_utils.hpp"

int main() {
    super_hse::executeQuery();
    auto game = super_hse::Game();
    try{
        game.run();
    }catch(super_hse::ldtkException &e){
        std::cerr << e.what();
        return -1;
    }catch (super_hse::textureException &e){
        std::cerr << e.what();
        return -1;
    }
    super_hse::closeDB();
    return 0;
}
