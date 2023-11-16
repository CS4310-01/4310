#include "sys/renice.h"
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include "Renice.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ProcessClient.h>
#include <Process.h>

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Alters the scheduling priority of a running process.");
    parser().registerPositional("PRIORITY", "change the scheduling priority to this level");
    parser().registerPositional("PROCESS_ID", "change the sceduling priority of this process");
    parser().registerFlag('n', "priority", "change priority level");
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    if(arguments().get("priority")) {
        ProcessClient process;
        ProcessID pid = (atoi(arguments().get("PROCESS_ID")));
        int priority = (atoi(arguments().get("PRIORITY")));

        ProcessClient::Info info;
        const ProcessClient::Result result = process.processInfo(pid, info);

        if(result != ProcessClient::Success) {
            ERROR("No process of ID '" << pid << "' is found")
            return InvalidArgument;
        }

        if(priority > 5 || priority < 1) {
            ERROR("Failed to set priority for process " << pid)
            return InvalidArgument;
        }

        process.setPriority(pid, priority);

        printf("process %d set to priority %d, from priority %d\n", pid, priority, info.kernelState.priority);

    }

    return Success;
}