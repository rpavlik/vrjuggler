
#include <gadget/Devices/DriverConfig.h>

#include <jccl/Config/ConfigElement.h>
#include <gadget/Type/DeviceConstructor.h>
#include <gadget/Util/Debug.h>
#include <gadget/gadgetParam.h>

#include "Vrpn.h"
#include "VRPNText.h"


extern "C"
{
	GADGET_DRIVER_EXPORT(vpr::Uint32) getGadgeteerVersion()
	{
		return __GADGET_version;
	}

	GADGET_DRIVER_EXPORT(void) initDevice(gadget::InputManager* inputMgr)
	{
		vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
			<< "Starting Gadget Driver Export" << std::endl
            << vprDEBUG_FLUSH;
		new gadget::DeviceConstructor<gadget::Vrpn>(inputMgr);
		vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
			<< "Middle." << std::endl
            << vprDEBUG_FLUSH;
		new gadget::DeviceConstructor<gadget::VRPNText>(inputMgr);
		vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
			<<  "Done." << std::endl
            << vprDEBUG_FLUSH;
	}
}
