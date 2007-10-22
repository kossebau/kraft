/***************************************************************************
           texttemplate.cpp - fill a template with text tags
                             -------------------
    begin                : Sep 2007
    copyright            : (C) 2007 by Klaas Freitag
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

#include "texttemplate.h"
#include "google/template.h"
#include <kstandarddirs.h>
#include <klocale.h>
#include <kdebug.h>

#include <string.h>

TextTemplate::TextTemplate()
  :mStandardDict( 0 )
{

}

TextTemplate::TextTemplate( const QString& name )
  : mFileName( name ),
    mStandardDict( 0 )
{
  openTemplate();
}

TextTemplate::~TextTemplate()
{
  // delete mTemplate;
  delete mStandardDict;
}

void TextTemplate::createDictionary( const QString& dictName )
{
  if ( mStandardDict ) {
    mDictionaries[dictName] = mStandardDict->AddSectionDictionary( dictName.ascii() );
    mStandardDict->ShowSection( dictName.ascii() );
  }
}


void TextTemplate::setValue( const QString& dictName, const QString& key, const QString& val )
{
  TemplateDictionary *dict = mDictionaries[dictName];
  if ( ! dict ) {
    if ( mStandardDict ) {
      dict = mStandardDict->AddSectionDictionary( dictName.ascii() );
      mStandardDict->ShowSection( dictName.ascii() );
    }
  }
  if ( dict )
    dict->SetValue( key.ascii(), std::string( val.utf8() ) );
}

void TextTemplate::setValue( const QString& key, const QString& val )
{
  if ( mStandardDict ) {
    mStandardDict->SetValue( key.ascii(), std::string( val.utf8() ) );
  }
}

bool TextTemplate::setTemplateFileName( const QString& name )
{
  mErrorString = QString();

  mFileName = name;
  return openTemplate( );
}

bool TextTemplate::openTemplate()
{
  KStandardDirs stdDirs;
  if ( mFileName.isEmpty() ) {
    mErrorString = i18n( "No file name given for template" );
    return false;
  }

  QString findFile = stdDirs.findResource( "data", mFileName );

  if ( findFile.isEmpty() ) {
    mErrorString = i18n( "Could not find template file" );
    return false;
  }

  kdDebug() << "Loading this template source file: " << findFile << endl;
  mTemplate = Template::GetTemplate( findFile, google::DO_NOT_STRIP );

  if ( !mTemplate ) {
    mErrorString = i18n( "Failed to open template source" );
    return false;
  }

  mStandardDict = new TemplateDictionary( "TopLevel" );

  return true;
}


QString TextTemplate::errorString() const
{
  return mErrorString;
}

QString TextTemplate::expand() const
{
  std::string output;

  if ( mStandardDict ) {
    mStandardDict->Dump();
  }
  if ( mTemplate ) {
    bool errorFree = mTemplate->Expand(&output, mStandardDict );

    if ( errorFree )
      return QString::fromUtf8( output.c_str() );
  }
  return QString();
}