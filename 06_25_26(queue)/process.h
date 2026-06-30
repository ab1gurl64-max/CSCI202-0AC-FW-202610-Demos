#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <map>
#include <iostream>

enum statusType
{
    WAITING,
    READY,
    FINISHED
};

const std::map<std::string, statusType> strToStatus = {{"waiting", WAITING}, {"ready", READY}, {"finished", FINISHED}};
const std::map<statusType, std::string> statusToStr = {{WAITING, "Waiting"}, {READY, "Ready"}, {FINISHED, "Finished"}};

class Process
{
public:
    Process(std::string, int, int, int, statusType);
    Process(const Process &);
    void run();
    statusType getStatus();
    void changePriority(int);
    void changeStatus(statusType);
    const Process &operator=(const Process &);
    bool operator>(const Process &) const;
    bool operator<(const Process &) const;
    bool operator>=(const Process &) const;
    bool operator<=(const Process &) const;
    bool operator==(const Process &) const;
    bool operator!=(const Process &) const;
    friend std::ostream &operator<<(std::ostream &, const Process &);

private:
    std::string name;
    int priority;
    int slicesNeeded;
    int IOSlice;
    int slicesUsed;
    statusType status;
};

#endif