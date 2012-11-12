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
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/size.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iostream>

template<typename T>
struct Wrap {};

template<int N, typename Vec>
inline void checkExpectedSize() {
   using namespace boost::mpl;
   BOOST_MPL_ASSERT((equal_to<typename size<Vec>::type, int_<N> >));
}

struct SingleTypeChecker {
   template<typename T>
   void operator()(Wrap<T> const&) {
      using namespace boost::mpl;

      checkExpectedSize<1, typename gadget::type::get_ordered_bases<T>::type>();
      BOOST_MPL_ASSERT((equal<typename gadget::type::get_ordered_bases<T>::type, vector<T> >));

      typedef typename inherit<T>::type Inherited;
      checkExpectedSize<1, typename gadget::type::get_ordered_bases<Inherited>::type>();
      BOOST_MPL_ASSERT((equal<typename gadget::type::get_ordered_bases<Inherited>::type, vector<T> >));
   }
};

struct DoubleTypeChecker {
   template<typename T1>
   struct Internal {

      template<typename T2>
      void operator()(Wrap<T2> const&, typename boost::disable_if<boost::is_same<T1, T2> >::type * = NULL) {
      using namespace boost::mpl;
         typedef typename inherit<T1, T2>::type Inherited1;
         typedef typename inherit<T2, T1>::type Inherited2;

         checkExpectedSize<2, typename gadget::type::get_ordered_bases<Inherited1>::type>();
         checkExpectedSize<2, typename gadget::type::get_ordered_bases<Inherited2>::type>();
         BOOST_MPL_ASSERT((equal<typename gadget::type::get_ordered_bases<Inherited1>::type, typename gadget::type::get_ordered_bases<Inherited2>::type >));
      }

      template<typename T2>
      void operator()(Wrap<T2> const&, typename boost::enable_if<boost::is_same<T1, T2> >::type * = NULL) {
         // Can't inherit twice from the same class, so nothing to test here.
      }
   };

   template<typename T>
   void operator()(Wrap<T> const&) {
      boost::mpl::for_each<gadget::all_base_types, Wrap<boost::mpl::_1> >(Internal<T>());
   }
};

int main(int /*argc*/, char * /*argv*/[])
{
   boost::mpl::for_each<gadget::all_base_types, Wrap<boost::mpl::_1> >(SingleTypeChecker());
   boost::mpl::for_each<gadget::all_base_types, Wrap<boost::mpl::_1> >(DoubleTypeChecker());
   return 0;
}
