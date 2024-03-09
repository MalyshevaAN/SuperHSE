#ifndef TILEMAP_
#define TILEMAP_

#include <LDtkLoader/Level.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class TileMap {
public:
    static std::string path;  // путь к папке проекта

    class Textures {
        Textures() = default;
        std::map<std::string, sf::Texture> data;
        static auto instance() -> Textures &;
        ~Textures() = default;

    public:
        Textures(const Textures &) = delete;
        Textures(Textures &&other) = delete;
        Textures operator=(const Textures &) = delete;
        Textures operator=(Textures &&other) = delete;
        static auto get(const std::string &name) -> sf::Texture &;
    };

    class Layer : public sf::Drawable {  // класс слоя в карте
        friend TileMap;
        Layer(const ldtk::Layer &layer, sf::RenderTexture &render_texture);
        sf::Texture
            *m_tileset_texture;  // что используется как текстура в уровне
        sf::RenderTexture &m_render_texture;
        sf::VertexArray m_vertex_array;  // по сути точки, которые отрисовываем
        void draw(sf::RenderTarget &target, sf::RenderStates states)
            const override;  // сама отрисовка - куда и на основе чего
    };

    TileMap() = default;
    void load(const ldtk::Level &level);
    // загрузка уровня, запись слоёв уровня в мапу со слоями
    auto getLayer(const std::string &name) const
        -> const Layer &;  // выбор конкретного слоя из всех слоёв уровня
private:
    mutable sf::RenderTexture m_render_texture;  //
    std::map<std::string, Layer> m_layers;       // мапа слоёв
};

#endif
