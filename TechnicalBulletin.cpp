/*
 * TBI - Technical Bulletin Indexer - Save and index Technical Bulletins,
 * allowing to use keywords to find them easily
 * Copyright (C) 2020 Martial Demolins AKA Folco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * mail: martial <dot> demolins <at> gmail <dot> com
 */

#include "TechnicalBulletin.hpp"
#include "Global.hpp"

//  TechnicalBulletin
//
// Create a TB using dropped data
// This constructor is designed to handle standard mails sent via the subscription list
//
TechnicalBulletin::TechnicalBulletin(QByteArray data)
{
    int start, end;

    // Parse most of the strings
    QList<QString> Strings;
    QList<QString> StringLabels;
    StringLabels << "Bulletin No:"
                 << "Title:"
                 << "TB Category:"
                 << "Rebuilding Kit:"
                 << "Technical Publication:"
                 << "Registered by:"
                 << "Replaces:"
                 << "Replaced by:";

    for (int i = 0; i < StringLabels.count(); i++) {
        start = data.indexOf(StringLabels.at(i));                          // Look for a label
        start = data.indexOf('\t', start) + 1;                             // Skip the label, and find the fist byte of the data string
        end   = min(data.indexOf('\t', start), data.indexOf('\n', start)); // End of data string. May terminate with a Tab or a New Line
        Strings << data.mid(start, end - start);                           // Grab and save data
    }

    // Comment box
    start = data.indexOf("Comments:");
    start = data.indexOf('\t', start) + 1;
    end   = data.indexOf('\t', start);
    QString Comment(data.mid(start, end - start));

    // Release date
    start = data.indexOf("Release date:");
    start = data.indexOf('\t', start) + 1;
    end   = data.indexOf('\n', start);
    QDate Date(QDate::fromString(data.mid(start, end - start), "yyyy-MM-dd"));

    // Keywords
    QList<QString> Keywords;
    Keywords << "";

    // Save data into members
    setData(Strings.at(0), Strings.at(1), Strings.at(2), Strings.at(3), Strings.at(4), Comment, Date, Strings.at(5), Strings.at(6), Strings.at(7), Keywords);
}

//  TechnicalBulletin
//
// Create a TB using data provided UI
//
TechnicalBulletin::TechnicalBulletin(QString number,
                                     QString title,
                                     QString category,
                                     QString rk,
                                     QString techpub,
                                     QString comment,
                                     QDate releasedate,
                                     QString registeredby,
                                     QString replaces,
                                     QString replacedby,
                                     QList<QString> keywords)
    : Number(number)
    , Title(title)
    , Category(category)
    , RK(rk)
    , TechPub(techpub)
    , Comment(comment)
    , ReleaseDate(releasedate)
    , RegisteredBy(registeredby)
    , Replaces(replaces)
    , ReplacedBy(replacedby)
    , Keywords(keywords)
{
}

//  setData
//
// Update an existing TB
//
void TechnicalBulletin::setData(QString number,
                                QString title,
                                QString category,
                                QString rk,
                                QString techpub,
                                QString comment,
                                QDate releasedate,
                                QString registeredby,
                                QString replaces,
                                QString replacedby,
                                QList<QString> keywords)
{
    this->Number       = number;
    this->Title        = title;
    this->Category     = category;
    this->RK           = rk;
    this->TechPub      = techpub;
    this->Comment      = comment;
    this->ReleaseDate  = releasedate;
    this->RegisteredBy = registeredby;
    this->Replaces     = replaces;
    this->ReplacedBy   = replacedby;
    this->Keywords     = keywords;
}

//  keywordString
//
// Create a string, using the keyword list. Intended to display keywords in UI
//
QString TechnicalBulletin::keywordsString() const
{
    if (this->Keywords.isEmpty()) {
        return QString("");
    }

    QString keywords = this->Keywords.at(0);
    for (int i = 1; i < this->Keywords.count(); i++) {
        keywords.append(KEYWORD_SEPARATOR).append(this->Keywords.at(i));
    }
    return keywords;
}

//  >>
//
// Unserialize a TB
QDataStream& operator>>(QDataStream& stream, TechnicalBulletin* tb)
{
    QByteArray Number;
    QByteArray Title;
    QByteArray Category;
    QByteArray RK;
    QByteArray TechPub;
    QByteArray Comment;
    QDate ReleaseDate;
    QByteArray RegisteredBy;
    QByteArray Replaces;
    QByteArray ReplacedBy;
    QList<QString> Keywords;

    stream >> Number >> Title >> Category >> RK >> TechPub >> Comment >> ReleaseDate >> RegisteredBy >> Replaces >> ReplacedBy >> Keywords;
    tb->setData(QString::fromUtf8(Number),
                QString::fromUtf8(Title),
                QString::fromUtf8(Category),
                QString::fromUtf8(RK),
                QString::fromUtf8(TechPub),
                QString::fromUtf8(Comment),
                ReleaseDate,
                QString::fromUtf8(RegisteredBy),
                QString::fromUtf8(Replaces),
                QString::fromUtf8(ReplacedBy),
                Keywords);
    return stream;
}

//  <<
//
// Serialize a TB
//
QDataStream& operator<<(QDataStream& stream, const TechnicalBulletin& tb)
{
    stream << tb.number().toUtf8() << tb.title().toUtf8() << tb.category().toUtf8() << tb.rk().toUtf8() << tb.techpub().toUtf8() << tb.comment().toUtf8()
           << tb.releaseDate() << tb.registeredBy().toUtf8() << tb.replaces().toUtf8() << tb.replacedBy().toUtf8() << tb.keywords();
    return stream;
}
