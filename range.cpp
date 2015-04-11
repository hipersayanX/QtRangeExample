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

#include "range.h"

class RangePrivate
{
    public:
        RangeType m_start;
        RangeType m_stop;
        RangeType m_step;
        int m_pos;
};

Range::Range()
{
    this->d = new RangePrivate();
    this->d->m_start = 0;
    this->d->m_stop = 0;
    this->d->m_step = 1;
    this->d->m_pos = 0;
}

Range::Range(RangeType stop)
{
    this->d = new RangePrivate();
    this->d->m_start = 0;
    this->d->m_stop = stop;
    this->d->m_step = 1;
    this->d->m_pos = 0;
}

Range::Range(RangeType start, RangeType stop, RangeType step)
{
    this->d = new RangePrivate();
    this->d->m_start = start;
    this->d->m_stop = stop;
    this->d->m_step = step;
    this->d->m_pos = 0;
}

Range::~Range()
{
    delete d;
}

void Range::append(RangeType value)
{
    if (this->d->m_stop == this->d->m_start) {
        this->d->m_step = value;

        this->d->m_stop = 2 * value;

        return;
    }

    this->d->m_step = this->d->m_step * (value - this->d->m_start)
                      / (this->d->m_stop - this->d->m_start);

    this->d->m_stop = value + this->d->m_step;
}

RangeType Range::at(int i) const
{
    return i * this->d->m_step + this->d->m_start;
}

RangeType Range::back() const
{
    return this->last();
}

Range::iterator Range::begin()
{
    return iterator(*this, 0);
}

Range::const_iterator Range::begin() const
{
    return const_iterator(*this, 0);
}

Range::const_iterator Range::cbegin() const
{
    return const_iterator(*this, 0);
}

Range::const_iterator Range::cend() const
{
    return const_iterator(*this, this->size());
}

void Range::clear()
{
    this->d->m_start = 0;
    this->d->m_stop = 0;
    this->d->m_step = 1;
    this->d->m_pos = 0;
}

bool Range::contains(RangeType value) const
{
    if (value < this->d->m_start
        || value >= this->d->m_stop)
        return false;

    int i = (value - this->d->m_start) / this->d->m_step;
    RangeType v = i * this->d->m_step + this->d->m_start;

    return v == value;
}

int Range::count(RangeType value) const
{
    if (this->contains(value))
        return 1;

    return 0;
}

int Range::count()
{
    return this->size();
}

bool Range::empty()
{
    return this->size() < 1;
}

Range::iterator Range::end()
{
    return iterator(*this, this->size());
}

Range::const_iterator Range::end() const
{
    return const_iterator(*this, this->size());
}

RangeType Range::first() const
{
    return this->d->m_start;
}

bool Range::isEmpty()
{
    return this->size() < 1;
}

RangeType Range::last() const
{
    return this->d->m_stop - this->d->m_step;
}

int Range::length() const
{
    return this->size();
}

void Range::prepend(RangeType value)
{
    this->d->m_step = this->d->m_step * (this->d->m_stop - value)
                      / (this->d->m_stop - this->d->m_start + this->d->m_step);

    this->d->m_start = value;
}

void Range::push_back(RangeType value)
{
    this->append(value);
}

void Range::push_front(RangeType value)
{
    this->prepend(value);
}

void Range::setStart(RangeType start)
{
    this->d->m_start = start;
}

void Range::setStop(RangeType stop)
{
    this->d->m_stop = stop;
}

void Range::setStep(RangeType step)
{
    this->d->m_step = step;
}

int Range::size() const
{
    return (this->d->m_stop - this->d->m_start) / this->d->m_step;
}

RangeType Range::start() const
{
    return this->d->m_start;
}

RangeType &Range::start()
{
    return this->d->m_start;
}

RangeType Range::stop() const
{
    return this->d->m_stop;
}

RangeType &Range::stop()
{
    return this->d->m_stop;
}

RangeType Range::step() const
{
    return this->d->m_step;
}

RangeType &Range::step()
{
    return this->d->m_step;
}

QList<RangeType> Range::toList() const
{
    QList<RangeType> list;

    for (int i = 0; i < this->size(); i++)
        list << i * this->d->m_step + this->d->m_start;

    return list;
}

QVector<RangeType> Range::toVector() const
{
    QVector<RangeType> vector(this->size());

    for (int i = 0; i < this->size(); i++)
        vector[i] = i * this->d->m_step + this->d->m_start;

    return vector;
}

RangeType Range::value(int i) const
{
    i = qBound(0, i, this->size() - 1);

    return i * this->d->m_step + this->d->m_start;
}

RangeType Range::value(int i, RangeType defaultValue) const
{
    if (i < 0
        || i >= this->size())
        return defaultValue;

    return i * this->d->m_step + this->d->m_start;
}

bool Range::operator !=(const Range &other) const
{
    if (this->d->m_start != other.d->m_start
        || this->d->m_stop != other.d->m_stop
        || this->d->m_step != other.d->m_step
        || this->d->m_pos != other.d->m_pos)
        return true;

    return false;
}

Range &Range::operator <<(RangeType value)
{
    this->append(value);

    return *this;
}

Range &Range::operator =(const Range &other)
{
    if (this != &other) {
        this->d->m_start = other.d->m_start;
        this->d->m_stop = other.d->m_stop;
        this->d->m_step = other.d->m_step;
        this->d->m_pos = other.d->m_pos;
    }

    return *this;
}

bool Range::operator ==(const Range &other) const
{
    if (this->d->m_start == other.d->m_start
        && this->d->m_stop == other.d->m_stop
        && this->d->m_step == other.d->m_step
        && this->d->m_pos == other.d->m_pos)
        return true;

    return false;
}

RangeType Range::operator [](int i) const
{
    return i * this->d->m_step + this->d->m_start;
}

Range::iterator::iterator()
{
    this->d = new RangePrivate();
    this->d->m_start = 0;
    this->d->m_stop = 0;
    this->d->m_step = 1;
    this->d->m_pos = 0;
}

Range::iterator::iterator(const Range &range, int pos)
{
    this->d = new RangePrivate();
    this->d->m_start = range.d->m_start;
    this->d->m_stop = range.d->m_stop;
    this->d->m_step = range.d->m_step;
    this->d->m_pos = pos;
}

Range::iterator::iterator(const Range::iterator &other)
{
    this->d = new RangePrivate();
    this->d->m_start = other.d->m_start;
    this->d->m_stop = other.d->m_stop;
    this->d->m_step = other.d->m_step;
    this->d->m_pos = other.d->m_pos;
}

Range::iterator::iterator(const Range::iterator &other, int pos)
{
    this->d = new RangePrivate();
    this->d->m_start = other.d->m_start;
    this->d->m_stop = other.d->m_stop;
    this->d->m_step = other.d->m_step;
    this->d->m_pos = pos;
}

Range::iterator::~iterator()
{
    delete d;
}

RangeType Range::iterator::start() const
{
    return this->d->m_start;
}

RangeType Range::iterator::stop() const
{
    return this->d->m_stop;
}

RangeType Range::iterator::step() const
{
    return this->d->m_step;
}

int Range::iterator::pos() const
{
    return this->d->m_pos;
}

RangeType Range::iterator::operator *() const
{
    return this->d->m_pos * this->d->m_step + this->d->m_start;
}

RangeType Range::iterator::operator [](Range::iterator::difference_type i) const
{
    return i * this->d->m_step + this->d->m_start;
}

bool Range::iterator::operator ==(const Range::iterator &other) const
{
    return this->d->m_start == other.d->m_start
            && this->d->m_stop == other.d->m_stop
            && this->d->m_step == other.d->m_step
            && this->d->m_pos == other.d->m_pos;
}

bool Range::iterator::operator !=(const Range::iterator &other) const
{
    return this->d->m_start != other.d->m_start
           || this->d->m_stop != other.d->m_stop
           || this->d->m_step != other.d->m_step
           || this->d->m_pos != other.d->m_pos;
}

Range::iterator Range::iterator::operator ++(int)
{
    this->d->m_pos++;

    return *this;
}

Range::iterator Range::iterator::operator --(int)
{
    this->d->m_pos--;

    return *this;
}

Range::iterator &Range::iterator::operator +=(Range::iterator::difference_type i)
{
    this->d->m_pos += i;

    return *this;
}

Range::iterator &Range::iterator::operator -=(Range::iterator::difference_type i)
{
    this->d->m_pos -= i;

    return *this;
}

Range::iterator Range::iterator::operator +(Range::iterator::difference_type i) const
{
    return iterator(*this, this->d->m_pos + i);
}

int Range::iterator::operator -(const Range::iterator &other) const
{
    return this->d->m_pos - other.d->m_pos;
}

Range::iterator Range::iterator::operator -(Range::iterator::difference_type i) const
{
    return iterator(*this, this->d->m_pos - i);
}

Range::iterator &Range::iterator::operator --()
{
    this->d->m_pos--;

    return *this;
}

Range::iterator &Range::iterator::operator ++()
{
    this->d->m_pos++;

    return *this;
}

Range::const_iterator::const_iterator()
{
    this->d = new RangePrivate();
    this->d->m_start = 0;
    this->d->m_stop = 0;
    this->d->m_step = 1;
    this->d->m_pos = 0;
}

Range::const_iterator::const_iterator(const Range &range, int pos)
{
    this->d = new RangePrivate();
    this->d->m_start = range.d->m_start;
    this->d->m_stop = range.d->m_stop;
    this->d->m_step = range.d->m_step;
    this->d->m_pos = pos;
}

Range::const_iterator::const_iterator(const Range::const_iterator &other)
{
    this->d = new RangePrivate();
    this->d->m_start = other.d->m_start;
    this->d->m_stop = other.d->m_stop;
    this->d->m_step = other.d->m_step;
    this->d->m_pos = other.d->m_pos;
}

Range::const_iterator::const_iterator(const Range::const_iterator &other, int pos)
{
    this->d = new RangePrivate();
    this->d->m_start = other.d->m_start;
    this->d->m_stop = other.d->m_stop;
    this->d->m_step = other.d->m_step;
    this->d->m_pos = pos;
}

Range::const_iterator::const_iterator(const Range::iterator &other)
{
    this->d = new RangePrivate();
    this->d->m_start = other.start();
    this->d->m_stop = other.stop();
    this->d->m_step = other.step();
    this->d->m_pos = other.pos();
}

Range::const_iterator::~const_iterator()
{
    delete d;
}

RangeType Range::const_iterator::operator *() const
{
    return this->d->m_pos * this->d->m_step + this->d->m_start;
}

RangeType Range::const_iterator::operator [](Range::const_iterator::difference_type i) const
{
    return i * this->d->m_step + this->d->m_start;
}

bool Range::const_iterator::operator ==(const Range::const_iterator &other) const
{
    return this->d->m_start == other.d->m_start
            && this->d->m_stop == other.d->m_stop
            && this->d->m_step == other.d->m_step
            && this->d->m_pos == other.d->m_pos;
}

bool Range::const_iterator::operator !=(const Range::const_iterator &other) const
{
    return this->d->m_start != other.d->m_start
           || this->d->m_stop != other.d->m_stop
           || this->d->m_step != other.d->m_step
           || this->d->m_pos != other.d->m_pos;
}

Range::const_iterator Range::const_iterator::operator ++(int)
{
    this->d->m_pos++;

    return *this;
}

Range::const_iterator Range::const_iterator::operator --(int)
{
    this->d->m_pos--;

    return *this;
}

Range::const_iterator &Range::const_iterator::operator +=(Range::const_iterator::difference_type i)
{
    this->d->m_pos += i;

    return *this;
}

Range::const_iterator &Range::const_iterator::operator -=(Range::const_iterator::difference_type i)
{
    this->d->m_pos -= i;

    return *this;
}

Range::const_iterator Range::const_iterator::operator +(Range::const_iterator::difference_type i) const
{
    return const_iterator(*this, this->d->m_pos + i);
}

int Range::const_iterator::operator -(const Range::const_iterator &other) const
{
    return this->d->m_pos - other.d->m_pos;
}

Range::const_iterator Range::const_iterator::operator -(Range::const_iterator::difference_type i) const
{
    return const_iterator(*this, this->d->m_pos - i);
}

Range::const_iterator &Range::const_iterator::operator --()
{
    this->d->m_pos--;

    return *this;
}

Range::const_iterator &Range::const_iterator::operator ++()
{
    this->d->m_pos++;

    return *this;
}

QDebug operator <<(QDebug debug, const Range &range)
{
    debug.nospace() << "Range("
                    << range.d->m_start
                    << ", "
                    << range.d->m_stop
                    << ", "
                    << range.d->m_step
                    << ")";

    return debug.space();
}

QDebug operator <<(QDebug debug, const Range::iterator &rangeIterator)
{
    debug.nospace() << "Range::iterator("
                    << rangeIterator.d->m_start
                    << ", "
                    << rangeIterator.d->m_stop
                    << ", "
                    << rangeIterator.d->m_step
                    << ")";

    return debug.space();
}

QDebug operator <<(QDebug debug, const Range::const_iterator &rangeIterator)
{
    debug.nospace() << "Range::const_iterator("
                    << rangeIterator.d->m_start
                    << ", "
                    << rangeIterator.d->m_stop
                    << ", "
                    << rangeIterator.d->m_step
                    << ")";

    return debug.space();
}

QDataStream &operator >>(QDataStream &istream, Range &range)
{
    istream >> range.d->m_start;
    istream >> range.d->m_stop;
    istream >> range.d->m_step;

    return istream;
}

QDataStream &operator <<(QDataStream &ostream, const Range &range)
{
    ostream << range.d->m_start;
    ostream << range.d->m_stop;
    ostream << range.d->m_step;

    return ostream;
}
