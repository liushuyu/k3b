/***************************************************************************
                          k3bfileitem.h  -  description
                             -------------------
    begin                : Sat Apr 21 2001
    copyright            : (C) 2001 by Sebastian Trueg
    email                : trueg@informatik.uni-freiburg.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef K3BFILEITEM_H
#define K3BFILEITEM_H


#include "k3bdataitem.h"

#include <kfileitem.h>
#include <qstring.h>

class K3bDataDoc;
class K3bDirItem;

/**
  *@author Sebastian Trueg
  */


class K3bFileItem : public KFileItem, public K3bDataItem
{
public:
	/**
	* Creates a new K3bFileItem
	* @param fileName if fileName end with a slash the item will become a directory.
	*/
	K3bFileItem( const QString& fileName, K3bDataDoc* doc, K3bDirItem* dir );
	~K3bFileItem();
	
	bool exists() const;
	
	const QString& isoName() const { return m_isoName; }
	const QString& joiletName() const { return m_joiletName; }
	const QString& rockRidgeName() const { return m_rockRidgeName; }
	
	QString absIsoPath();
	
private:
	QString m_isoName;
	QString m_joiletName;
	QString m_rockRidgeName;
};

#endif
