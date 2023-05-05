//BorisovNikita DSAI-03
#include <iostream>
#include <vector>
#include <valarray>
#include <iomanip>


using namespace std;

#define GNUPLOT_NAME "D:\\gnuplot\\bin\\gnuplot -persist"

int main() {


    std::cout << std::setprecision(2) << std::fixed;
    double alpha1, beta1, alpha2, beta2, vic, kill, InitVics, InitKills, timeLimit;
    int numOfPoints;
    cin >> vic >> kill >> alpha1 >> beta1 >> alpha2 >> beta2 >> timeLimit >> numOfPoints;
    InitKills = kill;
    InitVics= vic;
    double step = timeLimit / double(numOfPoints);
    double time = 0;
    vector<double> victims, killers;
    cout << "t:" << '\n';
    for(int i = 0; i <= numOfPoints; i++) {
        cout << time << " ";
        victims.push_back((InitVics - alpha2 / beta2) * cos(sqrt(alpha1 * alpha2) * time) - ((InitKills - alpha1 / beta1) * sqrt(alpha2) * beta1 * sin(sqrt(alpha1 * alpha2) * time)) / (beta2 * sqrt(alpha1)) + alpha2 / beta2);
        killers.push_back(((InitVics - alpha2 / beta2) * sqrt(alpha1) * beta2 * sin(sqrt(alpha1 *alpha2) * time)) / (beta1 * sqrt(alpha2)) + ((InitKills - alpha1 / beta1) * cos(sqrt(alpha1 * alpha2) * time)) + alpha1 / beta1);
        time += step;
    }
    cout << '\n';
    cout << "v:" << '\n';
    cout << InitVics << " ";
    for(int i = 1; i <= numOfPoints; i++) {
        cout << victims[i] << " ";
    }
    cout << '\n';
    cout << "k:" << '\n';
    cout << InitKills << " ";
    for(int i = 1; i <= numOfPoints; i++) {
        cout << killers[i] << " ";
    }


    FILE* pipe = popen(GNUPLOT_NAME, "w");
    fprintf(pipe, "set grid xtics ytics\n");
    fprintf(pipe, "set terminal pngcairo\n");
    fprintf(pipe, "set output \"output.png\"\n");

    fprintf(pipe, "plot '-' with lines title \"victims\", '-' with lines title \"killers\"\n");
    time = 0;
    fprintf(pipe, "%f %f\n", time, InitVics);
    time += step;
    for(int i = 1; i <= numOfPoints; i++) {
        fprintf(pipe, "%f %f\n", time, victims[i]);
        time += step;
    }
    fprintf(pipe, "e\n");

    time = 0;
    fprintf(pipe, "%f %f\n", time, InitKills);
    time += step;
    for(int i = 1; i <= numOfPoints; i++) {
        fprintf(pipe, "%f %f\n", time, killers[i]);
        time += step;
    }
    fprintf(pipe, "e\n");

    fflush(pipe);
    pclose(pipe);
}