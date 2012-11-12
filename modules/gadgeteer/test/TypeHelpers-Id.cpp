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

#undef NDEBUG

#include <gadget/Type/TypeHelpers.h>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/for_each.hpp>
#include <cassert>
#include <iostream>



template<typename T>
inline int getID() {
   return typename gadget::type::compute_id<typename boost::mpl::inherit<T>::type>::type();
}

template<typename T>
struct Wrap {};

struct SingleTypeTransformChecker {
   template<typename T>
   void operator()(Wrap<T> const&) {
      using namespace boost::mpl;
      typedef vector1<T> JustT;

      typedef typename gadget::type::transform_to_ids<JustT>::type IDs;
   }
};

template<typename T, int N>
inline void checkExpectedId() {
   using namespace boost::mpl;
   typedef typename inherit<T>::type Inherited;
   BOOST_MPL_ASSERT((equal_to<typename gadget::type::compute_id<Inherited>::type, int_<N> >));
   BOOST_MPL_ASSERT((equal_to<typename gadget::type::compute_id<T>::type, int_<N> >));

   typedef typename gadget::type::compute_id<Inherited>::type ComputeIdResult;
   std::cout << "Computed ID: " << ComputeIdResult() << " aka " << ComputeIdResult::value << ", expected " << N << std::endl;
   assert(ComputeIdResult() == N);
   assert(ComputeIdResult::value == N);
}

int main(int /*argc*/, char * /*argv*/[])
{
   using namespace gadget;
   checkExpectedId<Digital,   1>();
   checkExpectedId<Analog,    2>();
   checkExpectedId<Position,  4>();
   checkExpectedId<String,    8>();
   checkExpectedId<Command,   16>();
   checkExpectedId<Glove,     32>();
   checkExpectedId<Rumble,    64>();
   checkExpectedId<Hat,       128>();
   checkExpectedId<KeyboardMouse, 256>();
   boost::mpl::for_each<gadget::all_base_types, Wrap<boost::mpl::_1> >(SingleTypeTransformChecker());
   return 0;
}
