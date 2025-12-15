#include <gtest/gtest.h>

#include "resource_loader.h"
#include "observer.h"

#include <fstream>
#include <filesystem>

// Observer finto per i test
class TestObserver : public IObserver {
public:
    float lastProgress = 0.f;
    int notifyCount = 0;

    void onProgressUpdate(float progress,
                          const std::string&) override {
        lastProgress = progress;
        notifyCount++;
    }
};

TEST(ResourceLoaderTest, ObserverIsNotifiedAndProgressCompletes) {
    ResourceLoader loader;
    TestObserver observer;

    loader.addObserver(&observer);

    // Creiamo un file temporaneo di test
    const std::string filename = "test_file.txt";
    {
        std::ofstream out(filename);
        out << "test content";
    }

    loader.loadFiles({filename});

    EXPECT_GT(observer.notifyCount, 0);
    EXPECT_NEAR(observer.lastProgress, 1.0f, 0.001f);

    // Cleanup
    std::filesystem::remove(filename);
}
