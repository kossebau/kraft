/***************************************************************************
        katalogselection  - widget to select catalog entries from
                             -------------------
    begin                : 2006-08-30
    copyright            : (C) 2006 by Klaas Freitag
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

#ifndef CATALOGSELECTION_H
#define CATALOGSELECTION_H

#include <qvbox.h>

class KatalogListView;
class QComboBox;
class QWidgetStack;

class CatalogSelection : public QVBox
{
  Q_OBJECT
public:
  CatalogSelection( QWidget* );

  ~CatalogSelection() { };
protected:
  void setupCatalogList();

protected slots:
  void slotSelectCatalog( const QString& );

private:
  QComboBox *mCatalogSelector;
  QWidgetStack *mWidgets;

};

#endif
