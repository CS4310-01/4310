#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <Process.h>
#include <ProcessClient.h>
#include "Renice.h"


Renice::Renice(int argc, char** argv) : POSIXApplication(argc, argv)
{
	parser().setDescription("Change the priority of a process");
   	parser().registerFlag('n', "priority", "Change priority level");
	parser().registerPositional("PRIORITY", "Change the priority level to this level");
	parser().registerPositional("PID", "Changes the priority of this PID");
}

Renice::~Renice() 
{
	
}

Renice::~Renice(){
}

Renice::Result Renice::exec()
{	
    if(arguments().get("priority"))
    {
        ProcessClient client;
        ProcessID pid = atoi(arguments().get("PID"));
        int priority = atoi(arguments().get("PRIORITY"));
        ProcessClient::Info info;
        const ProcessClient::Result result = client.processInfo(pid, info);
        
        if (priority < 1 || priority > 5)
        {
            ERROR("ERROR: Invalid priority level")
            return InvalidArgument;
        }
        
	if(result != ProcessClient::Success) {
            ERROR("ERROR: Process '" << pid << "' is not found")
            return InvalidArgument;
        }        
        
        client.setPriority(pid, priority);
        printf("Process with ID %d has been changed from priority level %d to priority level %d\n", pid, info.kernelState.priority, priority);
        
        //Done
        return Success;
    }
    return InvalidArgument;
}
