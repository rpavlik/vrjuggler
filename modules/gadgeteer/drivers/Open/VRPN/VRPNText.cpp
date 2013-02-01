/** @file
	@brief Implementation

	@date 2012

	@author
	Patrick Carlson <carlsonp@iastate.edu>
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
	
*/

//           Copyright Iowa State University 2012.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

// Internal Includes
#include "VRPNText.h"

// Library/third-party includes
#include <boost/bind.hpp>
#include <jccl/Config/ConfigElement.h>
#include <gadget/Type/DeviceConstructor.h>
#include <gadget/Util/Debug.h>
#include <gadget/Devices/DriverConfig.h>


// Standard includes
// - none


namespace gadget
{
	void VRPN_CALLBACK VRPNText::handle_text (void *userdata, const vrpn_TEXTCB t)
	{
		if (t.type == vrpn_TEXT_NORMAL) {
			//Cast void pointer to the appropriate type
			VRPNText *self = static_cast<VRPNText*>(userdata);
			self->setStoredText(t.message);
		}
	}

	VRPNText::VRPNText()
	   : mIsActive(false)
	{
		//constructor
	}

	VRPNText::~VRPNText()
	{
		//Destructor
	   this->stopSampling();
	}

	bool VRPNText::config(jccl::ConfigElementPtr c)
	{
	   if(! (Input::config(c) && String::config(c)))
	   {
		  return false;
	   }

	   //Pull in tracker name and IP address from JCCL
	   //e.g. mytracker@127.0.0.1
	   name = c->getProperty<std::string>("device");

	   return true;
	}

	// Main thread of control for this active object
	void VRPNText::controlLoop()
	{
	   //Wait for initialization to finish
	   while( mIsInitializing )
	   {
		  vpr::Thread::yield();
	   }

	   // Loop through and keep sampling
	   while ( this->isActive() )
	   {
		  this->sample();
	   }
	}

	bool VRPNText::startSampling()
	{
	   mIsInitializing = true;

	   if ( this->isActive() )
	   {
		  vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
			 << "gadget::VRPNText was already started.\n" << std::endl
			 << vprDEBUG_FLUSH;

		  mIsInitializing = false;
		  return false;
	   }

	   // Has the thread actually started already
	   if (mThread != NULL)
	   {
		  vprDEBUG(vprDBG_ERROR,vprDBG_CONFIG_LVL)
			 << clrOutNORM(clrRED,"ERROR:")
			 << " gadget::VRPNText: startSampling called, when already sampling.\n"
			 << vprDEBUG_FLUSH;
		  vprASSERT(false);
	   }
	   else
	   {
		  // Create a new thread to handle the sampling control
		  try
		  {
			 mThread = new vpr::Thread(boost::bind(&VRPNText::controlLoop, this));
			 mIsActive = true;
			 vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
				<< "gadget::VRPNText sampling control thread created.\n"
				<< std::endl << vprDEBUG_FLUSH;

			//Setup VRPN connection
			 std::cout << "Starting up VRPN Text connection: " << name << std::endl;
			text = new vrpn_Text_Receiver(name.c_str());
			if (text == NULL) {
				vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
				<< clrOutNORM(clrRED,"ERROR:")
				<< "gadget::VRPNText unable to open VRPN connection.\n"
				<< std::endl << vprDEBUG_FLUSH;
			} else {
				//setup VRPN callback
				//http://www.cs.unc.edu/Research/vrpn/Connection_interest.html
				text->register_message_handler(this, handle_text);

				 mIsInitializing = false;
				 return true;   // success
			}
		  }
		  catch (vpr::Exception& ex)
		  {
			 vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
				<< clrOutBOLD(clrRED, "ERROR")
				<< ": Failed to spawn thread for VRPNText driver!\n"
				<< vprDEBUG_FLUSH;
			 vprDEBUG_NEXT(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
				<< ex.what() << std::endl << vprDEBUG_FLUSH;

			 mIsInitializing = false;
			 return false;  // Fail
		  }
	   }
	   mIsInitializing = false;

	   return false;
	}

	bool VRPNText::sample()
	{
	   if (this->isActive() == false)
	   {
		  return false;
	   }

	   vpr::Thread::yield();

	   //run VRPN mainloop
	   text->mainloop();

	   std::vector<StringData> temp;
	   temp.push_back(storedText);

	   addStringSample(temp);

	   storedText.clear();

	   return true;
	}

	bool VRPNText::stopSampling()
	{
	   if (this->isActive() == false)
	   {
		  return false;
	   }

	   if (mThread != NULL)
	   {
		  vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
			 << "gadget::VRPNText::stopSampling(): Stopping the sampling thread...\n"
			 << vprDEBUG_FLUSH;

		  mIsActive = false;
		  mThread->join();
		  //mThread->kill();
		  delete mThread;
		  mThread = NULL;
	   }

	   return true;
	}

	void VRPNText::updateData()
	{
	   if (!isActive())
	   {
		  return;
	   }

	   swapStringBuffers();
	}
}
