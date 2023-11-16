#include "sys/renice.h"
#include <stdio.h>
#include <unistd.h>
#include "Renice.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ProcessClient.h>

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Alters the scheduling priority of a running process.");
    parser().registerPositional("PRIORITY", "change the scheduling priority to this level");
    parser().registerPositional("PROCESS_ID", "change the sceduling priority of this process");
    parser().registerFlag('n', "priority", "change priority level");
}

Renice::Result Renice::exec()
{
    if(arguments().get("priority")) {
        const ProcessClient process;
        ProcessID pid = (atoi(arguments().get("PROCESS_ID")));
        int priority = (atoi(arguments().get("PRIORITY")));

        ProcessClient::Info info;
        const ProcessClient::Result result = process.processInfo(pid, info);

        //check if process exists
        if(result != ProcessClient::Success) {
            ERROR("ERROR: There is no current process with ID '" << pid << "!")
            return InvalidArgument;
        }

        //check if new priority is valid
        if(priority < 1 || priority > 5) {
            ERROR("ERROR: Requested priority level is not valid! Priority must be a level from 1-5!" << pid)
            return InvalidArgument;
        }
        
        // final error checking
        if (renicepid(pid, priority, 0 , 0) == ProcessCtl::Success){
            printf("Process with ID %d has been changed from priority level %d to priority level %d\n", pid, info.kernelState.priority, priority);
        }

    }
    return Success;
}