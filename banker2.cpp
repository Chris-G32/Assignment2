#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

enum Resources
{
    A,
    B,
    C
};

const int PROCESS_COUNT = 5;
const int RESOURCE_COUNT = 3;
const int ATTRIBUTE_COUNT = 2;

std::vector<int> safeOrder = {};

bool bankers(int[], int[][RESOURCE_COUNT], int[][RESOURCE_COUNT]);
using std::string;
int main()
{
    // Resource info
    int available[RESOURCE_COUNT];
    int instances[RESOURCE_COUNT];

    // Allocated here to avoid a copy later
    int work[RESOURCE_COUNT];

    // Process info
    int maximumResources[PROCESS_COUNT][RESOURCE_COUNT];
    int allocatedResource[PROCESS_COUNT][RESOURCE_COUNT];

    // Open file to read
    std::ifstream input("input.txt");

    // Reusable str buffer
    string buffer;

    // Load available resource counts
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        input >> buffer;
        int val = std::stoi(buffer);
        available[i] = val;
        work[i] = val; // Loading here avoids a copy of available later
    }

    // Load resource instances
    for (int i = 0; i < RESOURCE_COUNT; i++)
    {
        input >> buffer;
        instances[i] = std::stoi(buffer);
    }

    // Load resource allocation
    for (int i = 0; i < PROCESS_COUNT; i++)
    {
        for (int j = 0; j < RESOURCE_COUNT; j++)
        {
            input >> buffer;
            allocatedResource[i][j] = std::stoi(buffer);
        }
    }

    // Load max resource requirements
    for (int i = 0; i < PROCESS_COUNT; i++)
    {
        for (int j = 0; j < RESOURCE_COUNT; j++)
        {
            input >> buffer;
            maximumResources[i][j] = std::stoi(buffer);
        }
    }

    // Close file
    input.close();

    if (bankers(work, maximumResources, allocatedResource))
    {
        std::cout << "SAFE" << std::endl
                  << "SAFE SEQUENCE IS" << std::endl;
        for (auto &num : safeOrder)
        {
            std::cout << "P" << num << std::endl;
        }
    }
}

bool bankers(int work[], int maxRes[][RESOURCE_COUNT], int allocation[][RESOURCE_COUNT])
{
    bool finish[PROCESS_COUNT] = {false, false, false, false, false};

    int need[PROCESS_COUNT][RESOURCE_COUNT];

    // calculate needed resources
    for (int i = 0; i < PROCESS_COUNT; i++)
        for (int j = 0; j < RESOURCE_COUNT; j++)
            need[i][j] = maxRes[i][j] - allocation[i][j];

    int safeProcesses = 0;
    while (safeProcesses < PROCESS_COUNT)
    {
        bool safe = false;
        for (int i = 0; i < PROCESS_COUNT; i++)
        {
            // if not finish[i] and need[i] <= work[0->2][a-c]
            if (!finish[i])
            {

                int j;
                for (j = 0; j < RESOURCE_COUNT; j++)
                    if (need[i][j] > work[j])
                        break;

                // If all needs of p were satisfied.
                if (j == RESOURCE_COUNT)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0; k < RESOURCE_COUNT; k++)
                        work[k] += allocation[i][k];

                    // Add this process to safe sequence.
                    safeProcesses++;
                    safeOrder.push_back(i);

                    // Mark this p as finished
                    finish[i] = true;

                    safe = true;
                }
            }
        }
        if (!safe)
        {
            return false;
        }
    }
    return true;
}