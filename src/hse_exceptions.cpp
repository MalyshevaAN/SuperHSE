#ifndef HSE_EXCEPTIONS_CPP
#define HSE_EXCEPTIONS_CPP

#include "hse_exceptions.hpp"

namespace super_hse{
ldtkException::ldtkException(const std::string &message)
    : runtime_error(message){};
noSuchLdtkProject::noSuchLdtkProject(const std::string &projectName)
    : ldtkException("Cannot find \'" + projectName + "\'' project\n"){};
noSuchLevel::noSuchLevel(const std::string &levelName)
    : ldtkException("Cannot find \'" + levelName + "\'' level\n"){};
noSuchLayer::noSuchLayer(const std::string &layerName)
    : ldtkException(
          "Cannot find \'" + layerName + "\'' layer in ldtk project\n"
      ){};
noSuchDescriptionFile::noSuchDescriptionFile(const std::string &fileName)
    : ldtkException("Cannot find \'" + fileName + "\' description file\n"){};

textureException::textureException(const std::string &texture_name)
    : runtime_error("Cannot find texture named: " + texture_name){};

serverException::serverException(const std::string &message)
    : runtime_error(message){};
connectionException::connectionException(const std::string &socket_address)
    : serverException(
          "Failed to connect to server on address: " + socket_address + '\n'
      ){};
sendingException::sendingException()
    : serverException("Failed to send data to server\n"){};
}

#endif
