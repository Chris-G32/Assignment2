#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "json.hpp"
using json = nlohmann::json;

class Resource
{
public:
    int instances;
    int available;

    Resource() {}
    Resource(int instances, int available) : instances(instances), available(available) {}
};

class Process
{
public:
    std::unordered_map<std::string, int> allocated;
    std::unordered_map<std::string, int> max;
    std::unordered_map<std::string, int> need()
    {
        std::unordered_map<std::string, int> need;
        need["a"] = max["a"] - allocated["a"];
        need["b"] = max["b"] - allocated["b"];
        need["c"] = max["c"] - allocated["c"];
        return need;
    }
    Process() {}
    Process(std::unordered_map<std::string, int> allocated, std::unordered_map<std::string, int> max) : allocated(allocated), max(max) {}
};

class SystemState
{
public:
    std::unordered_map<std::string, Resource> resources;
    std::vector<Process> processes;

    SystemState() {}
    SystemState(std::unordered_map<std::string, Resource> resources, std::vector<Process> processes) : resources(resources), processes(processes) {}
};
bool runBankers()
{
}
bool lessThanOrEqualToAll(std::unordered_map<std::string, int> lhs, std::unordered_map<std::string, Resource> rhs)
{
    return lhs["a"] <= rhs["a"].available || lhs["b"] <= rhs["b"].available || lhs["c"] <= rhs["c"].available;
}
int main()
{
    std::ifstream file("input.json");
    json j;
    file >> j;

    // Load resources
    std::unordered_map<std::string, Resource> resources;
    for (json::iterator it = j["resources"].begin(); it != j["resources"].end(); ++it)
    {
        std::string name = it.key();
        int instances = it.value()["instances"];
        int available = it.value()["available"];
        resources[name] = Resource(instances, available);
    }

    // Load processes
    std::vector<Process> processes;
    for (json::iterator it = j["processes"].begin(); it != j["processes"].end(); ++it)
    {
        std::unordered_map<std::string, int> allocated;
        std::unordered_map<std::string, int> max;
        for (json::iterator res_it = it.value()["allocated"].begin(); res_it != it.value()["allocated"].end(); ++res_it)
        {
            std::string name = res_it.key();
            int value = res_it.value();
            allocated[name] = value;
        }
        for (json::iterator res_it = it.value()["max"].begin(); res_it != it.value()["max"].end(); ++res_it)
        {
            std::string name = res_it.key();
            int value = res_it.value();
            max[name] = value;
        }
        processes.push_back(Process(allocated, max));
    }

    /*BEGIN BANKERS*/
    // get count of resources in this case 3 len(available)
    const int RESCOUNT = 3;

    std::vector<std::unordered_map<std::string, int>> need;
    // calculate the needed array
    for (int i = 0; i < RESCOUNT; i++)
    {
        need.push_back(processes[i].need());
    }
    std::vector<int> safeSequence={};
    // copy available to work
    auto work = std::unordered_map<std::string, Resource>(resources);
    // Finish should be boolean array of len 3, false initially
    bool finish[3] = {false, false, false};
    // if any not finish
    bool anyNotFinish = true;
    bool outerSafe=false;
    while (!finish[0] || !finish[1] || !finish[2])
    {
        bool safe = false;
        for (int i = 0; i < 3; i++)
        {
            // if not finish[i] and need[i] <= work[0->2][a-c]
            if (!finish[i] && lessThanOrEqualToAll(need[i], work))
            {
                work["a"].available += need[i]["a"];
                work["b"].available += need[i]["b"];
                work["c"].available += need[i]["c"];
                finish[i] = true;
                safeSequence.push_back(i);
                safe = true;
                outerSafe=true;
                break;
            }
        }
        if (!safe)
        {
            outerSafe=false;
            std::cout<<"NOT SAFE";
            break;
        }
    }
    if(outerSafe){
        std::cout<<"SAFE"<<std::endl<<"SAFE SEQUENCE IS"<<std::endl;
        for(auto& num : safeSequence){
            std::cout<<"P"<<num<<std::endl;
        }
    }
    
    /*END BANKERS*/
    // Create system state
    SystemState system_state(resources, processes);

    // Print system state for testing
    std::cout << "Resources:\n";
    for (auto &res : system_state.resources)
    {
        std::cout << "  " << res.first << ": " << res.second.instances << " instances, " << res.second.available << " available\n";
    }
    std::cout << "Processes:\n";
    for (auto &proc : system_state.processes)
    {
        std::cout << "  Allocated: ";
        for (auto &res : proc.allocated)
        {
            std::cout << res.first << "=" << res.second << " ";
        }
        std::cout << ", Max: ";
        for (auto &res : proc.max)
        {
            std::cout << res.first << "=" << res.second << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
