#pragma once
#include <stdexcept>
#include <optional>
#include <SFML/Graphics.hpp>
class Assets {
    std::optional<sf::Font>    m_Font;
    std::optional<sf::Texture> m_Background;
    std::optional<sf::Texture> m_Gems;
public:
    static Assets& Instance() {
        static Assets assets;
        return assets;
    }
    
    sf::Font& GetFont() {
        if (!m_Font)
            LoadResource(m_Font, "images//calibri.ttf");
        return *m_Font; 
    }
    
    sf::Texture& GetBackGround() {
        if (!m_Background)
            LoadResource(m_Background, "images//background.png");
        return *m_Background;
    }
    
    sf::Texture& GetGems() {
        if (!m_Gems)
            LoadResource(m_Gems, "images//gems.png");
        return *m_Gems;
    }

private:
    Assets() {};
    ~Assets() {};
    Assets(Assets const&) = delete;
    Assets& operator= (Assets const&) = delete;

    template<class TRes>
    void LoadResource(std::optional<TRes>& aRes, std::string aResPath) {
        aRes = std::make_optional(TRes());
        if (!aRes->loadFromFile(aResPath))
            throw std::runtime_error("cant open resource file " + aResPath);
    }
};
