#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <SFML/Graphics.hpp>

class Display {
public:
    Display(const sf::Image& image) : _image(image) {
        _texture.loadFromImage(image);
        _sprite.setTexture(_texture, true);
    };
    virtual ~Display(){};

    void update() {
        _texture.update(_image);
    }
    const sf::Sprite& sprite() { return _sprite; };
private:
    const sf::Image& _image;
    sf::Texture _texture;
    sf::Sprite _sprite;
};


#endif /* end of include guard: __DISPLAY_H__ */
