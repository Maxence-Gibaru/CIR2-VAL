#ifndef CIR2_VAL_METROLINE_H
#define CIR2_VAL_METROLINE_H

#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"
#include "TrainGraphics.h"

class MetroLine {
private:
    int lineId;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Termini;
public:

    /**
     * @brief Constructor of MetroLine class
    */
    MetroLine();

    /**
     * @brief Constructor of MetroLine class
     * @param lineId : id of the line
     * @param terminusData : data of the terminus
     * @param stationData : data of the stations
     * @param trainNumber : number of trains
     */
    MetroLine(int lineId, const std::vector<std::tuple<std::string, int, double, bool>> &terminusData,
              const std::vector<std::tuple<std::string, int,
                      std::tuple<int, int>, bool, std::tuple<double, double>, double>>

              &stationData,
              int trainNumber
    );

    /**
     * @breif Manage the line (trains, stations, terminus)
     * @param sharedData : data shared between threads
     * @param mtx : mutex
     * @param stopWorking : boolean to stop the thread
     * @param temps : time
     */
    void manageLine(SharedData &sharedData, std::mutex &mtx, bool &stopWorking, Heure &temps);

    /**
     * @brief Get the id of the line
     * @return int : id of the line
     */
    int getLineId();

    std::vector<Train> getTrains();

    /**
     * @brief Set the trains of the line
     * @param newTrains : new trains
     */
    void setTrains(std::vector<Train> &newTrains);

    std::vector<Station> getStations();

    /**
     * @brief Set the stations of the line
     * @param newStations : new stations
     */
    void setStations(std::vector<Station> &newStations);

};

#endif //CIR2_VAL_METROLINE_H
