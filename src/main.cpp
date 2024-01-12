#include <thread>
#include <vector>
#include "data.h"
#include "MetroLine.h"
#include "TrainGraphics.h"
#include "config.h"


std::mutex mtx_;

// Main function
int main() {
    try {
        // Shared data among threads
        SharedData sharedData;
        Heure temps;
        bool stop_working = false;

        // Vector definition
        std::vector<std::thread> threads;
        std::vector<MetroLine *> metroLines;
        std::thread hourThread(ManageTime, std::ref(temps), std::ref(stop_working), std::ref(mtx_));;

        // Metroline definition
        MetroLine line1, line2;

        // Wrap potentially problematic code in try-catch blocks
        try {

            line1 = MetroLine(0, dataTerminusLine1, dataStationsLine1, TRAIN_NUMBER_LINE_1);
            metroLines.push_back(&line1);

            line2 = MetroLine(1, dataTerminusLine2, dataStationsLine2, TRAIN_NUMBER_LINE_2);
            metroLines.push_back(&line2);

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


        // launch a thread for each train line
        // Wrap potentially problematic code in try-catch blocks
        try {


            for (auto &line: metroLines) {
                for (auto &actualTrain: line->getTrains()) {
                    threads.emplace_back(&MetroLine::manageLine, line,
                                         std::ref(actualTrain),
                                         std::ref(sharedData),
                                         std::ref(mtx_),
                                         std::ref(stop_working),
                                         std::ref(temps));
                }
            }

        } catch (const std::exception &e) {
            std::cerr << "Exception in launching threads: " << e.what() << std::endl;
            // Handle or log the exception as needed
            return EXIT_FAILURE; // Return failure code
        }

        if (hourThread.joinable()) {
            hourThread.join();
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
