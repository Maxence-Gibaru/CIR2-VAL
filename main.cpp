#include <thread>
#include <vector>
#include "data.h"
#include "MetroLine.h"
#include "TrainGraphics.h"

#define DISPLAY true

int TRAIN_NUMBER_LINE_1 = 10;
int TRAIN_NUMBER_LINE_2 = 10;

double DISTANCE_SECURITY = 1000;

// Main function
int main(void) {
    try {
        // Shared data among threads
        SharedData sharedData;
        bool stop_working = false;

        // Vector definition
        std::mutex mtx_;
        std::vector<std::thread> threads;

        // Metroline definition
        // Wrap potentially problematic code in try-catch blocks
        try {
            MetroLine line1(0, dataTerminusLine1, dataStationsLine1, TRAIN_NUMBER_LINE_1);
            MetroLine line2(1, dataTerminusLine2, dataStationsLine2, TRAIN_NUMBER_LINE_2);

            // ... [Other potentially problematic code]
        } catch (const std::exception &e) {
            std::cerr << "Exception in MetroLine setup: " << e.what() << std::endl;
            // Handle or log the exception as needed
            return EXIT_FAILURE; // Return failure code
        }

        std::thread renderThread;
        // Thread for rendering visuals
        if (DISPLAY) {
            renderThread = std::thread([&sharedData]() {
                sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Train Simulator");
                renderVisuals(window, sharedData);
            });
        }

        Heure temps;
        // launch a thread for each train line
        // Wrap potentially problematic code in try-catch blocks
        try {
            threads.emplace_back(&MetroLine::manageLine, &line1, std::ref(sharedData), std::ref(mtx_), std::ref(stop_working),
                                 std::ref(temps));
            threads.emplace_back(&MetroLine::manageLine, &line2, std::ref(sharedData), std::ref(mtx_), std::ref(stop_working),std::ref(temps));

            // ... [Other potentially problematic code]
        } catch (const std::exception &e) {
            std::cerr << "Exception in launching threads: " << e.what() << std::endl;
            // Handle or log the exception as needed
            return EXIT_FAILURE; // Return failure code
        }

        // Wait for all threads to finish
        for (auto &thread: threads) {
            if (thread.joinable())
                thread.join();
        }

        // Wait for rendering thread to finish if applicable
        if (DISPLAY and renderThread.joinable()) {
            renderThread.join();
        }
    } catch (const std::exception &e) {
        std::cerr << "Unhandled exception in main: " << e.what() << std::endl;
        return EXIT_FAILURE; // Return failure code
    }

    return EXIT_SUCCESS; // Return success code if no exception occurred
}
