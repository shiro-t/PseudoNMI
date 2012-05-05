/* add your code here */
#ifndef __PseudoNMISwitch__PseudoNMISwitch__
#define __PseudoNMISwitch__PseudoNMISwitch__
#include <IOKit/IOService.h>

class jp_nest_driver_PseudoNMI : public IOService
{
    OSDeclareDefaultStructors(jp_nest_driver_PseudoNMI)
private:
    
public:
    virtual bool start(IOService *provider);
    virtual void stop(IOService *provider);
};





#endif /* __PseudoNMISwitch__PseudoNMISwitch__ */
