#ifndef CIR2_VAL_METROLINE_H
#define CIR2_VAL_METROLINE_H

#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"
#include "TrainGraphics.h"


class MetroLine {
private:
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Termini;
public:
    MetroLine(const std::vector<std::tuple<std::string, int, double, bool>> &terminusData,
              const std::vector<std::tuple<std::string, int,
                      std::tuple<int, int>, bool, std::tuple<double, double>, double>>

              &stationData,
              int trainNumber
    );

    void manageLine(SharedData &sharedData, std::mutex &mtx, bool &stopWorking, Heure &temps);

};

#endif //CIR2_VAL_METROLINE_H
