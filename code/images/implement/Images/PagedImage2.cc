//# PagedImage.cc: defines the PagedImage class (non-template code)
//# Copyright (C) 1994,1995,1996,1999,2000
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
//# $Id$

#include <trial/Images/PagedImage.h>
#include <aips/Tables/TableDesc.h>
#include <aips/Tables/Table.h>
#include <aips/Tables/ColumnDesc.h>
#include <aips/Exceptions/Error.h>

DataType imagePixelType(const String &fileName)
{
    DataType retval = TpOther;
    if (Table::isReadable(fileName)) {
	try {
	    TableDesc desc;
	    uInt nrow = Table::getLayout(desc, fileName);
	    ColumnDesc cdesc = desc["map"];
	    retval = cdesc.dataType();
            nrow = 0;                   // Shut compiler up
	} catch (AipsError x) {
	    // Nothing
	} 
    }
    return retval;
}
