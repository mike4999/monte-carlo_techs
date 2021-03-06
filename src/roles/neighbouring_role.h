#ifndef NEIGHBOURING_ROLE_H
#define NEIGHBOURING_ROLE_H

#include <functional>
#include "../datas/area_data.h"
#include "../datas/cell_data.h"
#include "../datas/dimer_data.h"

template <class SData>
class NeighbouringRole : public SData
{
public:
    template <typename Lambda>
    void eachNeighbour(const AreaData *area, bool isTorus, const Lambda &lambda) const;

    template <typename Lambda>
    void uniqPairs(const AreaData *area, bool isTorus, const Lambda &lambda) const;

private:
    void neighboursIter(CoordType (*neighboursCoords)[2], CoordType neighboursNum, const AreaData *area, bool isTorus, std::function<void (int)> lambda) const;

    void checkAndUpdateIfNeed(CoordType coords[], const AreaData *area) const;
    int torus(CoordType curr, CoordType maxSize) const;
};

template <>
template <typename Lambda>
void NeighbouringRole<CellData>::uniqPairs(const AreaData *area, bool isTorus, const Lambda &lambda) const {
    CoordType neighboursCoords[][2] = {
        { (CoordType)(this->x() + 1), (CoordType)(this->y()) },
        { (CoordType)(this->x()), (CoordType)(this->y() + 1) }
    };

    neighboursIter(neighboursCoords, 2, area, isTorus, lambda);
}

template <>
template <typename Lambda>
void NeighbouringRole<CellData>::eachNeighbour(const AreaData *area, bool isTorus, const Lambda &lambda) const {
    // the middle pair of coordinates is the same as in uniqPairs method
    CoordType neighboursCoords[][2] = {
        { (CoordType)(this->x()), (CoordType)(this->y() - 1) },
        { (CoordType)(this->x() + 1), (CoordType)(this->y()) },
        { (CoordType)(this->x()), (CoordType)(this->y() + 1) },
        { (CoordType)(this->x() - 1), (CoordType)(this->y()) }
    };

    neighboursIter(neighboursCoords, 4, area, isTorus, lambda);
}

template <>
template <typename Lambda>
void NeighbouringRole<DimerData>::eachNeighbour(const AreaData *area, bool isTorus, const Lambda &lambda) const {
    CoordType ncs[6][2];
    if (this->first->x() == this->second->x()) {
        ncs[0][0] = (CoordType)(this->first->x() - 1);
        ncs[0][1] = (CoordType)(this->first->y());

        ncs[1][0] = (CoordType)(this->first->x() + 1);
        ncs[1][1] = (CoordType)(this->first->y());

        ncs[2][0] = (CoordType)(this->second->x() - 1);
        ncs[2][1] = (CoordType)(this->second->y());

        ncs[3][0] = (CoordType)(this->second->x() + 1);
        ncs[3][1] = (CoordType)(this->second->y());

        ncs[4][0] = (CoordType)(this->first->x());
        ncs[5][0] = (CoordType)(this->first->x());
        if (this->first->y() > this->second->y()) {
            ncs[4][1] = (CoordType)(this->first->y() + 1);
            ncs[5][1] = (CoordType)(this->second->y() - 1);
        } else {
            ncs[4][1] = (CoordType)(this->first->y() - 1);
            ncs[5][1] = (CoordType)(this->second->y() + 1);
        }
    } else {
        ncs[0][0] = (CoordType)(this->first->x());
        ncs[0][1] = (CoordType)(this->first->y() - 1);

        ncs[1][0] = (CoordType)(this->first->x());
        ncs[1][1] = (CoordType)(this->first->y() + 1);

        ncs[2][0] = (CoordType)(this->second->x());
        ncs[2][1] = (CoordType)(this->second->y() - 1);

        ncs[3][0] = (CoordType)(this->second->x());
        ncs[3][1] = (CoordType)(this->second->y() + 1);

        ncs[4][1] = (CoordType)(this->first->y());
        ncs[5][1] = (CoordType)(this->first->y());
        if (this->first->x() > this->second->x()) {
            ncs[4][0] = (CoordType)(this->first->x() + 1);
            ncs[5][0] = (CoordType)(this->second->x() - 1);
        } else {
            ncs[4][0] = (CoordType)(this->first->x() - 1);
            ncs[5][0] = (CoordType)(this->second->x() + 1);
        }
    }

    neighboursIter(ncs, 6, area, isTorus, lambda);
}

template <class SData>
void NeighbouringRole<SData>::neighboursIter(CoordType (*neighboursCoords)[2], CoordType neighboursNum,
                                             const AreaData *area, bool isTorus, std::function<void (int)> lambda) const
{
    for (int i = 0; i < neighboursNum; ++i) {
        CoordType *nc = neighboursCoords[i];
        if (!isTorus && (nc[0] < 0 || nc[1] < 0 || nc[0] >= area->sizeX() || nc[1] >= area->sizeY())) continue;
        checkAndUpdateIfNeed(nc, area);
        lambda(area->index(nc[0], nc[1]));
    }
}

template <class SData>
void NeighbouringRole<SData>::checkAndUpdateIfNeed(CoordType coords[2], const AreaData *area) const {
    coords[0] = torus(coords[0], area->sizeX());
    coords[1] = torus(coords[1], area->sizeY());
}

template <class SData>
int NeighbouringRole<SData>::torus(CoordType curr, CoordType maxSize) const {
    if (curr < 0) return curr + maxSize;
    else if (curr >= maxSize) return curr - maxSize;
    else return curr;
}


#endif // NEIGHBOURING_ROLE_H
