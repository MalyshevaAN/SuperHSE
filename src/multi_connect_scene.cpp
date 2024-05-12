#include "multi_connect_scene.hpp"
#include "input_box.hpp"

namespace super_hse {

MultiConnectScene::MultiConnectScene() {
    if (!font.loadFromFile("../assets/fonts/8bit.ttf")) {
        std::cerr << "Error loading font\n";
    }

    get_texture_from_file("menu.png", bigRectanglePicture);
    bigRectangle.setTexture(bigRectanglePicture);

    ipInput.init(font, InputBoxType::IP);
    portInput.init(font, InputBoxType::Port);

    ipInput.box.setFillColor(activeInputBoxColor);
    ipInput.cursorVisible = true;

    const int errorBoxheightOffset = 150;
    errorBox.init(font, errorBoxheightOffset);

    get_texture_from_file("connect_button.png", connectButtonPicture);
    connectButton.setTexture(connectButtonPicture);

    updateSceneSize();
}

}
