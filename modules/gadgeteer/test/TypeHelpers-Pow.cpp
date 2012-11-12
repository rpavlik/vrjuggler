/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2012 by Iowa State University
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
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/


#include <gadget/Type/TypeHelpers.h>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <iostream>

int main(int /*argc*/, char * /*argv*/[])
{
   using namespace boost::mpl;
   using gadget::detail::pow;
   BOOST_MPL_ASSERT((equal_to<pow<int_<0>,  int_<0> >::type, int_<1> >));

   BOOST_MPL_ASSERT((equal_to<pow<int_<2>,  int_<0> >::type, int_<1> >));
   BOOST_MPL_ASSERT((equal_to<pow<int_<2>,  int_<1> >::type, int_<2> >));
   BOOST_MPL_ASSERT((equal_to<pow<int_<2>,  int_<2> >::type, int_<4> >));
   BOOST_MPL_ASSERT((equal_to<pow<int_<2>,  int_<3> >::type, int_<8> >));
   BOOST_MPL_ASSERT((equal_to<pow<int_<2>,  int_<4> >::type, int_<16> >));
   return 0;
}
