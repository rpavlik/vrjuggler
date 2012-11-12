/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2011 by Iowa State University
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

#ifndef _GADGET_TYPE_HELPERS_H_
#define _GADGET_TYPE_HELPERS_H_

#include <gadget/gadgetConfig.h>

// Used by pow
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/times.hpp>

// Used by compute_id
#include <boost/mpl/index_of.hpp>

// Used by transform_to_ids
#include <boost/mpl/transform.hpp>
#include <boost/mpl/quote.hpp>

// Used by compose_id
#include <boost/mpl/bitor.hpp>

// Used by get_ordered_bases
#include <boost/mpl/copy_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector/vector10.hpp>

#include <gadget/Type/AllBaseTypes.h>


namespace gadget
{

namespace detail
{

/** @name Compile-Time Power-of Computation */
//@{

template<typename Value, typename Exponent>
struct pow {
  typedef boost::mpl::range_c<int, 0, Exponent::value> range;
  typedef typename
      boost::mpl::fold<
           range
         , boost::mpl::int_<1>
         , boost::mpl::times<boost::mpl::_1, Value >
      >::type
   type;
};

} // end of namespace detail

namespace type
{

/** @name Metafunctions */
//@{

template<typename Type>
struct compute_id : detail::pow<boost::mpl::int_<2>, typename boost::mpl::index_of<all_base_types, Type>::type > {};

template<typename TypeList>
struct transform_to_ids : boost::mpl::transform<TypeList, boost::mpl::quote1<compute_id> >::type {};

template<typename TypeList>
struct compose_id
{
   typedef typename transform_to_ids<TypeList>::type ids;
   typedef typename
      boost::mpl::fold<
           ids
         , boost::mpl::int_<0>
         , boost::mpl::bitor_<boost::mpl::_1, boost::mpl::_2>
      >::type
   type;
};

/**
* Computes the ordered subset of all_base_types that is the list of base
* types for this instantiation.
*
* @see writeObject()
* @see readObject()
*/
template<typename T>
struct get_ordered_bases {
   typedef typename
      boost::mpl::copy_if<
           all_base_types
         , boost::is_base_of<boost::mpl::_1, T>
         , boost::mpl::back_inserter<boost::mpl::vector0<> >
      >::type
   type;
};

template<typename T>
struct get_id : compose_id< typename get_ordered_bases<T>::type > {};

//@}

} // end of namespace type

} // end of namespace gadget


#endif /* _GADGET_TYPE_HELPERS_H_ */
