/* QtRangeExample, Implementation of range iterator in Qt, and usage example
 * with QtConcurrent.
 * Copyright (C) 2015  Gonzalo Exequiel Pedone
 *
 * QtRangeExample is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtRangeExample is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtRangeExample. If not, see <http://www.gnu.org/licenses/>.
 *
 * Email   : hipersayan DOT x AT gmail DOT com
 * Web-Site: http://github.com/hipersayanX/QtRangeExample
 */

#include <QCoreApplication>
#include <QtConcurrent>

#include "range.h"

#define BUFFERSIZE (3 * 7 * 11 * 13 * 17 * 19 * 23)

QVector<float> bufferA(BUFFERSIZE);
QVector<float> bufferB(BUFFERSIZE);
QVector<float> bufferC(BUFFERSIZE);

QVector<quint32> bufferI(BUFFERSIZE);
QVector<quint32> bufferO(BUFFERSIZE);
quint32 *bufferP[2] = {bufferI.data(), bufferO.data()};
int inBufferSize;
int outBufferSize;
int buffN = 0;

void sum(int i)
{
    int next = 2 * i + 1;

    if (next < inBufferSize)
        bufferP[1 - buffN][i] = bufferP[buffN][2 * i] + bufferP[buffN][next];
    else
        bufferP[1 - buffN][i] = bufferP[buffN][2 * i];
}

inline int outSize(int inSize)
{
    return (inSize + (inSize & 0x1)) / 2;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Inicialize buffer
    for (int i = 0; i < BUFFERSIZE; i++)
        bufferI[i] = qrand() % 128;

    QElapsedTimer timer;
    timer.start();

    // Serial sum.
    quint32 sumT = 0;

    for (int i = 0; i < BUFFERSIZE; i++)
        sumT += bufferI[i];

    qDebug() << sumT << timer.elapsed();

    timer.restart();

    // Concurrent prefix sum.
    for (inBufferSize = BUFFERSIZE,
         outBufferSize = outSize(inBufferSize);
         inBufferSize > 1;
         inBufferSize = outBufferSize,
         outBufferSize = outSize(inBufferSize)) {
        Range range(outBufferSize);
        QtConcurrent::blockingMap(range, sum);
        buffN = 1 - buffN;
    }

    qDebug() << bufferP[buffN][0] << timer.elapsed();

    return 0;
}
