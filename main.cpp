#include <SFML/Graphics.hpp>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>

// observer
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onProgressUpdate(float progress, const std::string& currentFile) = 0;
};

class ISubject {
protected:
    std::vector<IObserver*> observers;

public:
    void addObserver(IObserver* obs) {
        observers.push_back(obs);
    }

    void notify(float progress, const std::string& fileName) {
        for (auto* obs : observers)
            obs->onProgressUpdate(progress, fileName);
    }
};

// subject
class ResourceLoader : public ISubject {
public:
    void loadFiles(const std::vector<std::string>& filePaths) {
        using namespace std::filesystem;
        //calcola la dimensione
        uintmax_t totalSize = 0;
        for (const auto& path : filePaths) {
            if (exists(path))
                totalSize += file_size(path);
        }

        uintmax_t loadedSize = 0;

        for (const auto& path : filePaths) {
            if (!exists(path)) continue;

            uintmax_t size = file_size(path);
            std::ifstream file(path, std::ios::binary);
            std::vector<char> buffer(4096);
            uintmax_t readBytes = 0;

            while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
                readBytes += file.gcount();
                loadedSize += file.gcount();

                // Calcola il progresso
                float progress = static_cast<float>(loadedSize) / static_cast<float>(totalSize);
                notify(progress, path);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }
};

class ProgressBar : public IObserver {
    sf::RectangleShape background;
    sf::RectangleShape bar;
    sf::Font font;
    sf::Text percentText;
    sf::Text fileText;

    float progress = 0.f;
    std::string currentFile;

public:
    ProgressBar(float width, float height)
        : percentText(font, "", 20),
          fileText(font, "", 18)
    {
        background.setSize({width, height});
        background.setFillColor(sf::Color(50, 50, 50));
        background.setOutlineThickness(2.f);
        background.setOutlineColor(sf::Color::White);

        bar.setSize({0.f, height});
        bar.setFillColor(sf::Color::Green);


        font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");

        percentText.setFillColor(sf::Color::White);
        fileText.setFillColor(sf::Color(180, 180, 180));
    }

    // Callback dell'observer: aggiorna barra e testi
    void onProgressUpdate(float value, const std::string& file) override {
        progress = value;
        currentFile = file;

        bar.setSize({
            background.getSize().x * progress,
            background.getSize().y
        });

        int percent = static_cast<int>(progress * 100);
        percentText.setString(std::to_string(percent) + "%");

        std::filesystem::path p(file);
        fileText.setString("Loading: " + p.filename().string());
    }

    // Disegno della barra (sarà usato nel main il giorno 3)
    void draw(sf::RenderWindow& window, sf::Vector2f pos) {
        background.setPosition(pos);
        bar.setPosition(pos);

        percentText.setPosition({
            pos.x + background.getSize().x / 2.f - 25.f,
            pos.y - 30.f
        });

        fileText.setPosition({
            pos.x,
            pos.y + background.getSize().y + 10.f
        });

        window.draw(background);
        window.draw(bar);
        window.draw(percentText);
        window.draw(fileText);
    }
};

