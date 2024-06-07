#ifndef HSE_EXCEPIONS_HPP
#define HSE_EXCEPTIONS_HPP

#include <exception>
#include <stdexcept>

namespace super_hse{

class ldtkException : public std::runtime_error {
public:
    explicit ldtkException(const std::string &message);
};

class noSuchLdtkProject : public ldtkException {
public:
    explicit noSuchLdtkProject(const std::string &projectName);
};

class noSuchLevel : public ldtkException {
public:
    explicit noSuchLevel(const std::string &levelName);
};

class noSuchLayer : public ldtkException {
public:
    explicit noSuchLayer(const std::string &layerName);
};

class noSuchDescriptionFile : public ldtkException {
public:
    explicit noSuchDescriptionFile(const std::string &fileName);
};

class textureException : public std::runtime_error {
public:
    explicit textureException(const std::string &texture_name);
};

class serverException : public std::runtime_error {
public:
    explicit serverException(const std::string &message);
};

class connectionException : public serverException {
public:
    explicit connectionException(const std::string &socket_address);
};

class sendingException : public serverException {
public:
    explicit sendingException();
};
}

#endif
