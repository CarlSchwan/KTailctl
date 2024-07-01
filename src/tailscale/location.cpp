#include "location.h"

Location::Location(QObject *parent)
    : QObject(parent)
    , mData()
{
}

const QString &Location::country() const
{
    return mData.country;
}
const QString &Location::countryCode() const
{
    return mData.countryCode;
}
const QString &Location::city() const
{
    return mData.city;
}
const QString &Location::cityCode() const
{
    return mData.cityCode;
}
int Location::priority() const
{
    return mData.priority;
}
const LocationData &Location::locationData() const
{
    return mData;
}

bool Location::update(const LocationData &newData)
{
    bool changed = false;
    if (newData.country != mData.country) {
        changed = true;
        mData.country = newData.country;
        emit countryChanged(mData.country);
    }
    if (newData.countryCode != mData.countryCode) {
        changed = true;
        mData.countryCode = newData.countryCode;
        emit countryCodeChanged(mData.countryCode);
    }
    if (newData.city != mData.city) {
        changed = true;
        mData.city = newData.city;
        emit cityChanged(mData.city);
    }
    if (newData.cityCode != mData.cityCode) {
        changed = true;
        mData.cityCode = newData.cityCode;
        emit cityCodeChanged(mData.cityCode);
    }
    return changed;
}
