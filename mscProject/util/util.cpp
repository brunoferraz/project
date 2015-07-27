#include "util.h"

Util::Util()
{

}

QFile* Util::openFile(const char* path)
{
    //REMEMBER ALWAYS CLOSE THE FILE IN SPECIALIZATION METHOD OF TYPE;
    QFile* file = new QFile(path);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << path << "| File could NOT be opened";
        return 0;
    }else{
        qDebug() << path << "| OK";
        return file;
    }
}

QXmlStreamReader *Util::openXmlFileStream(const char *path)
{
    //CLOSE FILE BEFORE RETURN
    QFile &file  = *Util::openFile(path);
    QXmlStreamReader* xmlReader = new QXmlStreamReader(&file);
    file.close();
    return xmlReader;
}

QDomDocument *Util::openXmlFileDom(const char *path)
{
    //CLOSE FILE BEFORE RETURN
    QFile &file  = *Util::openFile(path);
    QDomDocument doc("ModelBase");
    doc.setContent(&file);
    file.close();
    return &doc;
}

void Util::xmlDomParser(QDomDocument *xml)
{
   // qDebug() << xml->toElement();
}

