/* add your code here */
#include "PseudoNMI.h"
#include <IOKit/IOLib.h>


// PE_enter_debugger
extern "C" {
#include <pexpert/pexpert.h>
}

/* ************** */
/* SYSCTL Support */
/* ************** */
#include <mach/mach_types.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/sysctl.h>

static int handle_pseudo_nmi SYSCTL_HANDLER_ARGS
{
    int err = 0;
    if (req->newptr) {
        // write cause NMI
        PE_enter_debugger("PseudoNMI");
//        Debugger("PseudoNMI");
    } else {
        int zero = 0;
        err = SYSCTL_OUT(req, &zero, sizeof(int));
    }
    return err;
}

SYSCTL_PROC(_debug, OID_AUTO, pseudo_nmi,  CTLTYPE_INT | CTLFLAG_RW, 0, 0, &handle_pseudo_nmi, "I", "Pseudo NMI");


/* ************** */
/*   Driver main  */
/* ************** */

#define super IOService
OSDefineMetaClassAndStructors(jp_nest_driver_PseudoNMI, IOService)

bool jp_nest_driver_PseudoNMI::start(IOService *provider)
{
    bool res = super::start(provider);
    //IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);
    IOLog("PseudoNMI is Enabled, if you want to push NMI, run \'sysctl -w debug.pseudo_nmi=1\'.");
    if(res) {
        sysctl_register_oid(&sysctl__debug_pseudo_nmi);
    }
    return res;
}

void jp_nest_driver_PseudoNMI::stop(IOService *provider)
{
    //IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);
    sysctl_register_oid(&sysctl__debug_pseudo_nmi);
    IOLog("PseudoNMI is Disabled.");
    super::stop(provider);
}


