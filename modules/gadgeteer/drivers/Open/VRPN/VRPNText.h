/** @file
	@brief Header

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

#pragma once
#ifndef INCLUDED_VRPNText_h_GUID_9D0D67FD_44E7_4D9F_B0C6_5C4E3963BB79
#define INCLUDED_VRPNText_h_GUID_9D0D67FD_44E7_4D9F_B0C6_5C4E3963BB79


// Internal Includes
#include <vpr/Thread/Thread.h>
#include <gadget/Type/InputBaseTypes.h>
#include <gadget/Type/Input.h>
#include <gadget/Type/String.h>

// Library/third-party includes
#include <vrpn_Text.h>
#include <vrpn_Tracker.h>
#include <vrpn_Shared.h>
#include <vrpn_FileConnection.h>

// Standard includes
#include <string>

namespace gadget
{
   class InputManager;
}

namespace gadget
{
	class VRPNText : public input_string_t
	{
		public:
			VRPNText();
			virtual ~VRPNText();

			/** Configures the device with a config chunk. */
			virtual bool config(jccl::ConfigElementPtr c);

			/** Begins sampling. */
			bool startSampling();

			/** Main thread of control for this active object. */
			void controlLoop();

			/** Stops sampling. */
			bool stopSampling();

			/** Samples data. */
			bool sample();

			/** Updates to the sampled data. */
			void updateData();

			/** Returns what chunk type is associated with this class. */
			static std::string getElementType()
			{
			  return std::string("VRPNText");
			}

			const StringData getStringData(int devNum = 0)
			{
			  return storedText;
			}

			/** Checks if the device is active. */
			bool isActive()
			{
			  return mIsActive;
			}

			void setStoredText(std::string text)
			{
				storedText = text;
			}

		private:
			static void VRPN_CALLBACK handle_text(void *userdata, const vrpn_TEXTCB t);

			std::string storedText;

			bool mIsActive;
			bool mIsInitializing;

			//VRPN name and IP address to connect to
			//e.g. mytracker@127.0.0.1
			const char *name;

			vrpn_Tracker_Remote *tkr;
			vrpn_Text_Receiver *text;
	};

} // End of gadget namespace

#endif // INCLUDED_VRPNText_h_GUID_9D0D67FD_44E7_4D9F_B0C6_5C4E3963BB79

