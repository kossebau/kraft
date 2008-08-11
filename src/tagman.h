/***************************************************************************
             tag manager - create, edit and remove tags.
                             -------------------
    begin                : June 2008
    copyright            : (C) 2008 by Klaas Freitag
    email                : freitag@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _TAGMAN_H
#define _TAGMAN_H

/*
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files
#include <qvaluevector.h>

#include "geld.h"
#include "dbids.h"


class QString;
class QColor;

/**
 * das Stundensatzobjekt: definiert durch id und namen
 */
class TagTemplate
{
public:
  TagTemplate();
  TagTemplate( const dbID&, const QString&, const QString&, const QString& );

  QString name()  const { return mName;  }
  QColor  color() const { return mColor; }
  dbID    dbId()  const { return mId;    }
  QString description() const { return mDesc; }
private:
  dbID      mId;
  QString   mName;
  QString   mDesc;
  QColor    mColor;
  
};

typedef QValueVector<TagTemplate> TagTemplateValueVector;

/**
 * Tag Template Manager
 */

class TagTemplateMan
{
public:
  ~TagTemplateMan();
  static TagTemplateMan *self();

  QStringList allTagTemplates();
  TagTemplate getTagTemplate( const QString& );

private:
  TagTemplateMan();
  void load();

  TagTemplateValueVector mTagTmpl;
  static TagTemplateMan *mSelf;
};

#endif

/* END */

