//# NewMSAntenna.h: The NewMeasurementSet ANTENNA Table
//# Copyright (C) 1996,2000
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

#if !defined(AIPS_NewMSANTENNA_H)
#define AIPS_NewMSANTENNA_H

#include <aips/aips.h>
#include <aips/MeasurementSets/NewMSTable.h>
#include <aips/MeasurementSets/NewMSAntennaEnums.h>

// <summary> 
// A Table intended to hold a NewMeasurementSet ANTENNA table.
// </summary>

// <use visibility=export>

// <reviewed reviewer="Bob Garwood" date="1997/02/01" tests="" demos="">

// <prerequisite>
// <ul>
//   <li> <linkto class="NewMeasurementSet:description">NewMeasurementSet</linkto> 
//   <li> <linkto class="NewMSTable">NewMSTable</linkto> 
// </ul>
// </prerequisite>
//
// <etymology>
// NewMSAntenna stands for the NewMeasurementSet Antenna table.
// </etymology>
//
// <synopsis> 
// An NewMSAntenna is a table intended to hold the ANTENNA table for
// the NewMeasurementSet. It has an identical set of member functions as
// the main NewMeasurementSet class, except (currently) for the default
// calibration members. For further info and examples see the 
// NewMeasurementSet class.
// </synopsis> 
//
// <example>
// See the NewMeasurementSet for an example of how to access and use this class.
// </example>
//
// <motivation>
// It was found that subtables and the main table of the NewMeasurementSet have
// a lot in common, therefore they derive their interface from the same
// base class. Each subtable has its own class to keep the enum definitions
// and conversion functions in separate scopes.
// </motivation>
//
// <todo asof="1996/2/22">
// see NewMeasurementSet.
// </todo>


class NewMSAntenna:public NewMSAntennaEnums,
                public NewMSTable<NewMSAntennaEnums::PredefinedColumns,
		               NewMSAntennaEnums::PredefinedKeywords>
{
public:
    // This constructs an empty NewMSAntenna
    NewMSAntenna ();
    //
    // These constructors mirror the Table ones with additional checking
    // on validity (verifying that the NewMSAntenna will have the required columns
    // and keywords).
    // An exception is thrown if the constructed Table is not a valid NewMSAntenna
    // <thrown>
    //   <li> AipsError
    // </thrown>
    // <group name=tableLikeConstructors>
    NewMSAntenna (const String &tableName, TableOption = Table::Old);
    NewMSAntenna (const String &tableName, const String &tableDescName,
		    TableOption = Table::Old);
    NewMSAntenna (SetupNewTable &newTab, uInt nrrow = 0,
		    Bool initialize = False);
    NewMSAntenna (const Table &table);
    NewMSAntenna (const NewMSAntenna &other);
    // </group>

    // As with tables, the destructor writes the table if necessary.
    // Additional checking is done here to verify that all required
    // columns are still present.
    // If it is NOT valid, it will write the table and then throw an exception.
    // <thrown>
    //   <li> AipsError
    // </thrown>
    ~NewMSAntenna();

    //  Assignment operator, reference semantics
    NewMSAntenna& operator=(const NewMSAntenna&);

    // Make a special copy of this Table which references all columns from
    // this Table except those mentioned; those are empty and writable.
    // Each forwarded column has the same writable status as the underlying
    // column. The mentioned columns all use the AipsIO storage manager.
    // This function is inherited from NewMSTable and unlikely to be of use,
    // except in the class NewMeasurementSet (see comment there)..
    NewMSAntenna referenceCopy(const String& newTableName,
			    const Block<String>& writableColumns) const;

    // Initialize the statics appropriately. This does not need to be
    // called by users, it is called by the implementation class
    // NewMSTableImpl.
    static void init();

private:

    // required by the need to throw an exception in the destructor
    Bool hasBeenDestroyed_p;

};

#endif
