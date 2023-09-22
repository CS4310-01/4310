
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "HelloWorld.h"

HelloWorld::HelloWorld(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    /*	
    parser().setDescription("Stop executing for some time");
    parser().registerPositional("SECONDS", "Stop executing for the given number of seconds");*/
}

HelloWorld::~HelloWorld()
{
}

HelloWorld::Result HelloWorld::exec()
{
    printf("Hello world!\n");
    return Success;
}
