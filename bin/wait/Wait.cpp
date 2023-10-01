#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include <ProcessClient.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for the process to change its state");
    parser().registerPositional("PROCESS_ID", "Wait for the given pid process until the state changes");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid;
    if ((pid = atoi(arguments().get("PROCESS_ID"))) <= 0)
    {
        ERROR("Invalid pid '" << arguments().get("PROCESS_ID") << "'");
        return InvalidArgument;
    }
    
    ProcessClient process;
    ProcessClient::Info info;
    ProcessClient::Result result = process.processInfo(pid, info);
    
    if (result == ProcessClient::Success)
    {
    	waitpid(pid, 0, 0);
        printf("Process %d has exited.\n", pid);
    }
    else 
    {
    	ERROR("Invalid pid " << arguments().get("PROCESS_ID"));
    	return InvalidArgument;
    }
    return Success;
  
}
