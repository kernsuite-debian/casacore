//# AxesMapping.h: Info about mapping array axes to another order
//# Copyright (C) 2000
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//#
//# $Id$

#if !defined(AIPS_AXESMAPPING_H)
#define AIPS_AXESMAPPING_H


//# Includes
#include <aips/aips.h>
#include <aips/Arrays/IPosition.h>

//# Forward Declarations
class Slicer;


// <summary>
// Info about mapping array axes to another order.
// </summary>

// <use visibility=local>

// <reviewed reviewer="" date="yyyy/mm/dd" tests="tAxesSpecifier.cc" demos="">
// </reviewed>

// <prerequisite>
//   <li> <linkto class="IPosition">IPosition</linkto>
//   <li> <linkto class="AxesSpecifier">AxesSpecifier</linkto>
// </prerequisite>

// <synopsis>
// AxesMapping holds the information about mapping axes to another order.
// It can be constructed by <linkto class=AxesSpecifier>AxesSpecifier</linkto>
// by applying a shape to the axes specification.
// <br>AxesMapping is thereafter used to map positions, shapes, and
// slices to the new axes or backwards.
// <note role=caution>
// Shapes and positions are both represented by class IPosition.
// However, they have to be treated differently in this class,
// because removed axes for a position have value 0, while for a
// shape they have value 1. Hence there are different functions for them
// and the user has to take care that the correct function is called.
// </note>
// </synopsis>

// <example>
// <srcblock>
//
// </srcblock>
// </example>

// <motivation>
// The class encapsulates the mapping functionality.
// It is meant as a helper class for
// <linkto class=SubLattice>SubLattice</linkto>.
// </motivation>

//# <todo asof="yyyy/mm/dd">
//# </todo>

class AxesMapping
{
public:
  // The default constructor creates empty maps.
  AxesMapping();

  // Construct it with the mapping from old to new axes order.
  // A value of -1 means that the old axes is ignored in the new one.
  explicit AxesMapping (const IPosition& oldToNew);

  // Copy constructor (copy semantics).
  AxesMapping(const AxesMapping& other);
  
  ~AxesMapping();

  // Assignment (copy semantics).
  // This and that do not have to have the same length.
  AxesMapping& operator= (const AxesMapping& other);

  // Is the axes order reordered?
  Bool isReordered() const
    { return itsReordered; }

  // Get the mapping of old->new.
  const IPosition& getToNew() const
    { return itsToNew; }

  // Get the mapping of new->old.
  const IPosition& getToOld() const
    { return itsToOld; }

  // Map an old position to the new one.
  // In debug-mode it checks if the removed axes have position 0.
  IPosition posToNew (const IPosition& pos) const;

  // Map an new position or shape to the old one.
  IPosition posToOld (const IPosition& pos) const;

  // Map an old shape to the new one.
  // In debug-mode it checks if the removed axes have length 1.
  IPosition shapeToNew (const IPosition& shape) const;

  // Map an new position or shape to the old one.
  IPosition shapeToOld (const IPosition& shape) const;

  // Map an old shape to the new one.
  // In debug-mode it checks if the removed axes have length 1.
  Slicer slicerToNew (const Slicer& slicer) const;

  // Map an new position or shape to the old one.
  Slicer slicerToOld (const Slicer& slicer) const;

private:
  IPosition itsToNew;
  IPosition itsToOld;
  Bool      itsReordered;
};


#endif
