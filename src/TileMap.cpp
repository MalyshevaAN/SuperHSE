#include "TileMap.hpp"
#include <iostream>
#include "hse_utils.hpp"

namespace super_hse {

auto TileMap::Textures::instance() -> Textures & {
    static Textures instance;
    return instance;
}

auto TileMap::Textures::get(const std::string &name) -> sf::Texture & {
    auto &data = instance().data;
    if (data.count(name) == 0) {
        data[name].loadFromFile(
            TileMap::path + name
        );  // подгрузили файл откуда берем инфу для текстур
    }
    return instance().data.at(name);
}

TileMap::Layer::Layer(
    const ldtk::Layer &layer,
    sf::RenderTexture &render_texture
)
    : m_render_texture(render_texture) {
    m_tileset_texture = &Textures::get(layer.getTileset().path
    );  // текстура для конкретного слоя
    m_vertex_array.resize(
        layer.allTiles().size() * 4
    );  // точки слоя которые отрисовываем
    m_vertex_array.setPrimitiveType(sf::PrimitiveType::Quads
    );  // говорим что точки это квадратики
    int i = 0;
    for (const auto &tile : layer.allTiles(
         )) {  // каждому квадратику ставим в соответсвтие тайл с картинки
        for (int j = 0; j < 4; ++j) {
            auto vertices = tile.getVertices();
            m_vertex_array[i * 4 + j].position.x = vertices[j].pos.x;
            m_vertex_array[i * 4 + j].position.y = vertices[j].pos.y;
            m_vertex_array[i * 4 + j].texCoords.x =
                static_cast<float>(vertices[j].tex.x
                );  // где-то тут беда с текстурой
            m_vertex_array[i * 4 + j].texCoords.y =
                static_cast<float>(vertices[j].tex.y);
        }
        i++;
    }
}

void TileMap::Layer::draw(sf::RenderTarget &target, sf::RenderStates states)
    const {  // отрисовывем слой
    states.texture = m_tileset_texture;
    m_render_texture.clear(sf::Color::Transparent);
    m_render_texture.draw(m_vertex_array, states);
    m_render_texture.display();
    target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}

std::string TileMap::path;  // путь к папке

void TileMap::load(const ldtk::Level &level) {  // подгрузка уровня
    m_render_texture.create(level.size.x, level.size.y);
    m_layers.clear();
    for (const auto &layer : level.allLayers()) {
        if (layer.getType() == ldtk::LayerType::Tiles) {
            cell_size = layer.getCellSize();
            width = layer.getGridSize().x * cell_size;
            height = layer.getGridSize().y * cell_size;
            m_layers.insert({layer.getName(), {layer, m_render_texture}});
        }
    }
}

auto TileMap::getLayer(const std::string &name) const
    -> const Layer & {  // выбор конкретного слоя
    try {
        return m_layers.at(name);
    } catch (std::out_of_range &e) {
        std::cerr << name;
        throw noSuchLayer(name);
    }
}
}  // namespace super_hse
