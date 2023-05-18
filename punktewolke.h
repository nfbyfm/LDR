#ifndef PUNKTEWOLKE_H
#define PUNKTEWOLKE_H
#include "vector"
#include "QString"
#include <QtDataVisualization/q3dscatter.h>
using namespace std;
using namespace QtDataVisualization;

class Punktewolke
{
public:
    Punktewolke();
    ~Punktewolke();
    Punktewolke(QString fileName);
    QScatterDataArray* getdataArray();

private:
    vector<QVector3D> pc;
    QVector3D parseLine(const QString &line);
    double getdoubleValue(const QString& fhStr);
};

#endif // PUNKTEWOLKE_H
