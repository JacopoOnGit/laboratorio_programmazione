#include "resource_loader.h"

#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

void ResourceLoader::addObserver(IObserver* obs) {
    observers.push_back(obs);
}

void ResourceLoader::notify(float progress, const std::string& fileName) {
    for (auto* obs : observers)
        obs->onProgressUpdate(progress, fileName);
}

void ResourceLoader::loadFiles(const std::vector<std::string>& filePaths) {
    using namespace std::filesystem;

    uintmax_t totalSize = 0;
    for (const auto& path : filePaths) {
        if (exists(path))
            totalSize += file_size(path);
    }

    uintmax_t loadedSize = 0;

    for (const auto& path : filePaths) {
        if (!exists(path)) continue;

        std::ifstream file(path, std::ios::binary);
        std::vector<char> buffer(4096);

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
            loadedSize += file.gcount();

            float progress =
                static_cast<float>(loadedSize) /
                static_cast<float>(totalSize);

            notify(progress, path);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
