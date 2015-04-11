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

#ifndef QBRANGE_H
#define QBRANGE_H

#include <QtDebug>

typedef int RangeType;
class RangePrivate;

// This class works as it were a list of monotonically increasing numbers.
// It doesn't stores real data, but only values of start, stop and stepping.
class Range
{
    public:
        class iterator
        {
            public:
                typedef std::random_access_iterator_tag iterator_category;
                typedef int difference_type;
                typedef RangeType value_type;
                typedef RangeType *pointer;
                typedef RangeType &reference;

                iterator();
                iterator(const Range &range, int pos);
                iterator(const iterator &other);
                iterator(const iterator &other, int pos);
                ~iterator();
                RangeType start() const;
                RangeType stop() const;
                RangeType step() const;
                int pos() const;
                RangeType operator *() const;
                RangeType operator [](difference_type i) const;
                bool operator ==(const iterator &other) const;
                bool operator !=(const iterator &other) const;
                iterator &operator ++();
                iterator operator ++(int);
                iterator &operator --();
                iterator operator --(int);
                iterator &operator +=(difference_type i);
                iterator &operator -=(difference_type i);
                iterator operator +(difference_type i) const;
                iterator operator -(difference_type i) const;
                int operator -(const iterator &other) const;

            private:
                RangePrivate *d;

            friend QDebug operator <<(QDebug debug, const Range::iterator &rangeIterator);
        };

        class const_iterator
        {
            public:
                typedef std::random_access_iterator_tag  iterator_category;
                typedef int difference_type;
                typedef RangeType value_type;
                typedef const RangeType *pointer;
                typedef const RangeType &reference;

                const_iterator();
                const_iterator(const Range &range, int pos);
                const_iterator(const const_iterator &other);
                const_iterator(const const_iterator &other, int pos);
                const_iterator(const iterator &other);
                ~const_iterator();
                RangeType operator *() const;
                RangeType operator [](difference_type i) const;
                bool operator ==(const const_iterator &other) const;
                bool operator !=(const const_iterator &other) const;
                const_iterator &operator ++();
                const_iterator operator ++(int);
                const_iterator &operator --();
                const_iterator operator --(int);
                const_iterator &operator +=(difference_type i);
                const_iterator &operator -=(difference_type i);
                const_iterator operator +(difference_type i) const;
                const_iterator operator -(difference_type i) const;
                int operator -(const const_iterator &other) const;

            private:
                RangePrivate *d;

            friend QDebug operator <<(QDebug debug, const Range::const_iterator &rangeIterator);
        };

        Range();
        Range(RangeType stop);
        Range(RangeType start, RangeType stop, RangeType step=1);
        ~Range();
        void append(RangeType value);
        RangeType at(int i) const;
        RangeType back() const;
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        void clear();
        bool contains(RangeType value) const;
        int count(RangeType value) const;
        int count();
        bool empty();
        iterator end();
        const_iterator end() const;
        RangeType first() const;
        bool isEmpty();
        RangeType last() const;
        int length() const;
        void prepend(RangeType value);
        void push_back(RangeType value);
        void push_front(RangeType value);
        void setStart(RangeType start);
        void setStop(RangeType stop);
        void setStep(RangeType step);
        int size() const;
        RangeType start() const;
        RangeType &start();
        RangeType stop() const;
        RangeType &stop();
        RangeType step() const;
        RangeType &step();
        QList<RangeType> toList() const;
        QVector<RangeType> toVector() const;
        RangeType value(int i) const;
        RangeType value(int i, RangeType defaultValue) const;
        bool operator !=(const Range &other) const;
        Range &operator <<(RangeType value);
        Range &operator =(const Range &other);
        bool operator ==(const Range &other) const;
        RangeType operator [](int i) const;

    private:
        RangePrivate *d;

    friend QDebug operator <<(QDebug debug, const Range &range);
    friend QDataStream &operator >>(QDataStream &istream, Range &range); \
    friend QDataStream &operator <<(QDataStream &ostream, const Range &range);
};

QDebug operator <<(QDebug debug, const Range &range);
QDebug operator <<(QDebug debug, const Range::iterator &rangeIterator);
QDebug operator <<(QDebug debug, const Range::const_iterator &rangeIterator);
QDataStream &operator >>(QDataStream &istream, Range &range);
QDataStream &operator <<(QDataStream &ostream, const Range &range);

#endif // QBRANGE_H
