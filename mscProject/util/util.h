#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <qxmlstream.h>
#include <QDebug>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QTextStream>

class Util
{
public:
    Util();
    static QFile* openFile(const char* path);
    static QXmlStreamReader *openXmlFileStream(const char* path);
    static QDomDocument *openXmlFileDom(const char* path);
    static void xmlDomParser(QDomDocument* xml);
    static void saveFile(const QString path, const QString text);
};

#endif // UTIL_H
