#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "json.hpp"
using json = nlohmann::json;

class Resource {
public:
    int instances;
    int available;

    Resource() {}
    Resource(int instances, int available): instances(instances), available(available) {}
};

class Process {
public:
    std::unordered_map<std::string, int> allocated;
    std::unordered_map<std::string, int> max;
    std::unordered_map<std::string, int> need(){
        std::unordered_map<std::string, int> need;
        need["a"]=max["a"]-allocated["a"];
        need["b"]=max["b"]-allocated["b"];
        need["c"]=max["c"]-allocated["c"];
    }
    Process() {}
    Process(std::unordered_map<std::string, int> allocated, std::unordered_map<std::string, int> max): allocated(allocated), max(max) {}

};

class SystemState {
public:
    std::unordered_map<std::string, Resource> resources;
    std::vector<Process> processes;

    SystemState() {}
    SystemState(std::unordered_map<std::string, Resource> resources, std::vector<Process> processes): resources(resources), processes(processes) {}
};
bool runBankers(){

}
int main() {
    std::ifstream file("input.json");
    json j;
    file >> j;

    // Load resources
    std::unordered_map<std::string, Resource> resources;
    for (json::iterator it = j["resources"].begin(); it != j["resources"].end(); ++it) {
        std::string name = it.key();
        int instances = it.value()["instances"];
        int available = it.value()["available"];
        resources[name] = Resource(instances, available);
    }

    // Load processes
    std::vector<Process> processes;
    for (json::iterator it = j["processes"].begin(); it != j["processes"].end(); ++it) {
        std::unordered_map<std::string, int> allocated;
        std::unordered_map<std::string, int> max;
        for (json::iterator res_it = it.value()["allocated"].begin(); res_it != it.value()["allocated"].end(); ++res_it) {
            std::string name = res_it.key();
            int value = res_it.value();
            allocated[name] = value;
        }
        for (json::iterator res_it = it.value()["max"].begin(); res_it != it.value()["max"].end(); ++res_it) {
            std::string name = res_it.key();
            int value = res_it.value();
            max[name] = value;
        }
        processes.push_back(Process(allocated, max));
    }

    /*BEGIN BANKERS*/
    //get count of resources in this case 3 len(available)
    //calculate the needed array

    //copy available to work
    //Finish should be boolean array of len 3, false initially

    //if any not finish 
    //safe false
    //iterate over resource length, 3
    for (int i=0;i<3;i++){
        if(!)
    }

    /*END BANKERS*/
    // Create system state
    SystemState system_state(resources, processes);

    // Print system state for testing
    std::cout << "Resources:\n";
    for (auto& res : system_state.resources) {
        std::cout << "  " << res.first << ": " << res.second.instances << " instances, " << res.second.available << " available\n";
    }
    std::cout << "Processes:\n";
    for (auto& proc : system_state.processes) {
        std::cout << "  Allocated: ";
        for (auto& res : proc.allocated) {
            std::cout << res.first << "=" << res.second << " ";
        }
        std::cout << ", Max: ";
        for (auto& res : proc.max) {
            std::cout << res.first << "=" << res.second << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
