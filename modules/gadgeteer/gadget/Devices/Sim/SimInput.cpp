/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2003 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile$
 * Date modified: $Date$
 * Version:       $Revision$
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <gadget/gadgetConfig.h>

#include <jccl/Config/ConfigElement.h>
#include <gadget/Devices/Sim/SimInput.h>

namespace gadget
{

/** Constructs the mod pair from a mod pair element. */
std::vector<SimInput::KeyModPair> SimInput::readKeyList(std::vector<jccl::ConfigElementPtr>& keyList)
{
   std::vector<KeyModPair> key_vec;

   if ( ! keyList.empty() )
   {
#ifdef GADGET_DEBUG
      jccl::ConfigElementPtr first_element = keyList[0];
      std::string element_type(first_element->getID());
      vprASSERT(element_type == std::string("key_modifier_pair"));
#endif

      for ( std::vector<jccl::ConfigElementPtr>::iterator i = keyList.begin();
            i != keyList.end();
            ++i )
      {
         key_vec.push_back(KeyModPair((gadget::Keys) (*i)->getProperty<int>("key"),
                                      (gadget::Keys) (*i)->getProperty<int>("modifier_key")));
      }
   }

   return key_vec;
}


/**
 * Configures the keyboard interface.  Grabs it out of the given config element.
 */
bool SimInput::config(jccl::ConfigElementPtr element)
{
   // Get the event source.
   mEventWin.init(element->getProperty<std::string>("event_window_proxy"));

   return true;
}

int SimInput::checkKeyPair(KeyModPair& pair)
{
   if (pair.mModifier == -1)      // ANY modifier
   {
      return mEventWin->keyPressed(pair.mKey);
   }
   if (mEventWin->modifierOnly(pair.mModifier))
   {
      return mEventWin->keyPressed(pair.mKey);
   }
   else                 // Mod not pressed
   {
      return 0;
   }
}

int SimInput::checkKey(gadget::Keys keyId)
{
   return mEventWin->keyPressed(keyId);
}

} // End of gadget namespace
