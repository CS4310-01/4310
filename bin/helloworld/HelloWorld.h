#ifndef __BIN_HELLOWORLD_HELLOWORLD_H
#define __BIN_HELLOWORLD_HELLOWORLD_H

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

/**
 * Stop executing for some time.
 */
class HelloWorld : public POSIXApplication
{
  public:

    /**
     * Constructor
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    HelloWorld(int argc, char **argv);

    /**
     * Destructor
     */
    virtual ~HelloWorld();

    /**
     * Execute the application.
     *
     * @return Result code
     */
    virtual Result exec();
};

/**
 * @}
 */

#endif /* __BIN_HELLOWORLD_HELLOWORLD_H */
