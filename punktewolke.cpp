#include "punktewolke.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QDebug"

//Pointcloud-class
Punktewolke::Punktewolke()
{
    this->pc.reserve(1);
    this->pc.push_back(QVector3D(0,0,0));
}

Punktewolke::~Punktewolke()
{
    this->pc.clear();
    vector<QVector3D>().swap(this->pc);
}

Punktewolke::Punktewolke(QString fileName){


    //Open File and read data
    QFile inputFile(fileName);

    //file with 200'000 points (xyzRGB) is approx. 10MB big
    int fsize = abs((int)(inputFile.size()));

    fsize /= 1024; //KB
    fsize /= 1024; //MB

    if(fsize>10)
    {
        //don't read the whole file

        int factor = static_cast<int>(fsize/10 + 0.5)+1; //load only every "factor"-th value

        if (inputFile.open(QIODevice::ReadOnly))
        {
            //delete old points if they exist
            this->pc.clear();

            QTextStream in(&inputFile);
            int counter =0;

            while (!in.atEnd())
            {
                QString line = in.readLine();
                if(counter%factor==0)
                {
                    this->pc.push_back(parseLine(line));
                }
                counter ++;
            }
            inputFile.close();
        }
    }
    else
    {
        //read the whole file
        if (inputFile.open(QIODevice::ReadOnly))
        {
            //delete old points if they exist
            this->pc.clear();

            QTextStream in(&inputFile);
            int counter =0;
            int max_points = 200000;
            while (!in.atEnd() && counter <max_points)
            {
                QString line = in.readLine();
                this->pc.push_back(parseLine(line));
                counter++;
            }
            inputFile.close();

            if(counter==max_points)
            {
                QMessageBox::information(0,QObject::tr("Messpunkte laden"), fileName + QObject::tr(" besitzt mehr als 200'000 Punkte. Es wurden nur die ersten 200'000 Punkte eingelesen.") );
            }

        }
    }


}

QVector3D Punktewolke::parseLine(const QString &line)
{

    double x_value = 0;
    double y_value = 0;
    double z_value = 0;

    QString conv = line;
    conv=conv.replace(",", ".");
    QStringList list = conv.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if(list.count() >=3)
    {
        //z,x,y
        x_value = getdoubleValue(list.at(0));
        y_value = getdoubleValue(list.at(1));
        z_value = getdoubleValue(list.at(2));
    }

    return QVector3D(x_value, y_value, z_value);
}

double Punktewolke::getdoubleValue(const QString& fhStr)
{
    bool ok(false);
    double d = fhStr.toDouble(&ok);
    if (ok) {
        return d;
    }
    else
    {
        qDebug() << fhStr << ok << d;
        return 0;
    }
}

QScatterDataArray* Punktewolke::getdataArray()
{
    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize((int)(this->pc.size()));
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    for (float i = 0; i < this->pc.size(); i++)
    {
        ptrToDataArray->setPosition(this->pc.at(i));
        ptrToDataArray++;
    }
    return dataArray;
}
