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

                // Simula tempo di caricamento (solo per effetti visivi)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }
};
