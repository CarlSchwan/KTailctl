// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2023 Fabian Köhler <me@fkoehler.org>

#include "peer.h"
#include "status.h"

#include <QJsonArray>

#include <algorithm>
#include <cmath>

void Peer::updateFromStatus(const Status &status)
{
    if (status.self() != nullptr) {
        if (status.self()->id() == mId) {
            this->setTo(status.self());
            return;
        }
    }

    const auto *pos = std::find_if(status.peers().begin(), status.peers().end(), [this](const Peer *peer) {
        return peer->id() == mId;
    });
    if (pos != status.peers().end()) {
        this->setTo(*pos);
    }
}

Peer::Peer(QObject *parent)
    : QObject(parent)
{
}

Peer *Peer::fromJSON(const QJsonObject &json)
{
    Peer *peer = new Peer();
    peer->setIdFromJSON(json);
    peer->setPublicKeyFromJSON(json);
    peer->setHostNameFromJSON(json);
    peer->setDNSNameFromJSON(json);
    peer->setOsFromJSON(json);
    peer->setTailscaleIpsFromJSON(json);
    peer->setRelayFromJSON(json);
    peer->setRxBytesFromJSON(json);
    peer->setTxBytesFromJSON(json);
    peer->setCreatedFromJSON(json);
    peer->setLastSeenFromJSON(json);
    peer->setIsOnlineFromJSON(json);
    peer->setIsActiveFromJSON(json);
    peer->setIsCurrentExitNodeFromJson(json);
    peer->setIsExitNodeFromJSON(json);
    peer->setSSHHostKeysFromJSON(json);

    return peer;
}

bool Peer::setId(const QString &value)
{
    if (mId != value) {
        mId = value;
        emit idChanged(mId);
        return true;
    }
    return false;
}
bool Peer::setPublicKey(const QString &value)
{
    if (mPublicKey != value) {
        mPublicKey = value;
        emit publicKeyChanged(mPublicKey);
        return true;
    }
    return false;
}
bool Peer::setHostName(const QString &value)
{
    if (mHostName != value) {
        mHostName = value;
        emit hostNameChanged(mHostName);
        return true;
    }
    return false;
}
bool Peer::setDNSName(const QString &value)
{
    if (mDNSName != value) {
        mDNSName = value;
        emit dnsNameChanged(mDNSName);
        return true;
    }
    return false;
}
bool Peer::setOs(const QString &value)
{
    if (mOs != value) {
        mOs = value;
        emit osChanged(mOs);
        return true;
    }
    return false;
}
bool Peer::setTailscaleIps(const QStringList &value)
{
    if (mTailscaleIps != value) {
        mTailscaleIps = value;
        emit tailscaleIpsChanged(mTailscaleIps);
        return true;
    }
    return false;
}
bool Peer::setRelay(const QString &value)
{
    if (mRelay != value) {
        mRelay = value;
        emit relayChanged(mRelay);
        return true;
    }
    return false;
}
bool Peer::setRxBytes(long value)
{
    if (mRxBytes != value) {
        mRxBytes = value;
        emit rxBytesChanged(mRxBytes);
        return true;
    }
    return false;
}
bool Peer::setTxBytes(long value)
{
    if (mTxBytes != value) {
        mTxBytes = value;
        emit txBytesChanged(mTxBytes);
        return true;
    }
    return false;
}
bool Peer::setCreated(const QDateTime &value)
{
    if (mCreated != value) {
        mCreated = value;
        emit createdChanged(mCreated);
        return true;
    }
    return false;
}
bool Peer::setLastSeen(const QDateTime &value)
{
    if (mLastSeen != value) {
        mLastSeen = value;
        emit lastSeenChanged(mLastSeen);
        return true;
    }
    return false;
}
bool Peer::setIsOnline(bool value)
{
    if (mIsOnline != value) {
        mIsOnline = value;
        emit isOnlineChanged(mIsOnline);
        return true;
    }
    return false;
}
bool Peer::setIsActive(bool value)
{
    if (mIsActive != value) {
        mIsActive = value;
        emit isActiveChanged(mIsActive);
        return true;
    }
    return false;
}
bool Peer::setIsCurrentExitNode(bool value)
{
    if (mIsCurrentExitNode != value) {
        mIsCurrentExitNode = value;
        emit isCurrentExitNodeChanged(mIsCurrentExitNode);
        return true;
    }
    return false;
}
bool Peer::setIsExitNode(bool value)
{
    if (mIsExitNode != value) {
        mIsExitNode = value;
        emit isExitNodeChanged(mIsExitNode);
        return true;
    }
    return false;
}

bool Peer::setSSHHostKeys(const QStringList &value)
{
    if (mSSHHostKeys != value) {
        mSSHHostKeys = value;
        emit sshHostKeysChanged(mSSHHostKeys);
        if (mSSHHostKeys.size() > 0) {
            setIsRunningSSH(true);
        } else {
            setIsRunningSSH(false);
        }
        return true;
    }
    return false;
}

bool Peer::setIsRunningSSH(bool value)
{
    if (mIsRunningSSH != value) {
        mIsRunningSSH = value;
        emit isRunningSSHChanged(mIsRunningSSH);
        return true;
    }
    return false;
}

void Peer::setIdFromJSON(const QJsonObject &json)
{
    if (json.contains("ID") && json["ID"].isString()) {
        setId(json["ID"].toString());
    } else {
        qWarning() << "Cannot find string \"ID\"";
    }
}
void Peer::setPublicKeyFromJSON(const QJsonObject &json)
{
    if (json.contains("PublicKey") && json["PublicKey"].isString()) {
        setPublicKey(json["PublicKey"].toString());
    } else {
        qWarning() << "Cannot find string \"PublicKey\"";
    }
}
void Peer::setHostNameFromJSON(const QJsonObject &json)
{
    if (json.contains("HostName") && json["HostName"].isString()) {
        setHostName(json["HostName"].toString());
    } else {
        qWarning() << "Cannot find string \"HostName\"";
    }
}
void Peer::setDNSNameFromJSON(const QJsonObject &json)
{
    if (json.contains("DNSName") && json["DNSName"].isString()) {
        setDNSName(json["DNSName"].toString());
    } else {
        qWarning() << "Cannot find string \"DNSName\"";
    }
}
void Peer::setOsFromJSON(const QJsonObject &json)
{
    if (json.contains("OS") && json["OS"].isString()) {
        setOs(json["OS"].toString());
    } else {
        qWarning() << "Cannot find string \"OS\"";
    }
}
void Peer::setTailscaleIpsFromJSON(const QJsonObject &json)
{
    QStringList ips;
    if (json.contains("TailscaleIPs") && json["TailscaleIPs"].isArray()) {
        // TODO: FIXME
        for (const auto &ip_address : json["TailscaleIPs"].toArray()) {
            if (ip_address.isString()) {
                ips.append(ip_address.toString());
            } else {
                qWarning() << "TailscaleIPs contains non-string";
            }
        }
    } else {
        qWarning() << "Cannot find array \"TailscaleIPs\"";
    }
    setTailscaleIps(ips);
}
void Peer::setRelayFromJSON(const QJsonObject &json)
{
    if (json.contains("Relay") && json["Relay"].isString()) {
        setRelay(json["Relay"].toString());
    } else {
        qWarning() << "Cannot find string \"Relay\"";
    }
}
void Peer::setRxBytesFromJSON(const QJsonObject &json)
{
    if (json.contains("RxBytes") && json["RxBytes"].isDouble()) {
        setRxBytes((long)std::round(json["RxBytes"].toDouble()));
    } else {
        qWarning() << "Cannot find int \"RxBytes\"";
    }
}
void Peer::setTxBytesFromJSON(const QJsonObject &json)
{
    if (json.contains("TxBytes") && json["TxBytes"].isDouble()) {
        setTxBytes((long)std::round(json["TxBytes"].toDouble()));
    } else {
        qWarning() << "Cannot find int \"TxBytes\"";
    }
}
void Peer::setCreatedFromJSON(const QJsonObject &json)
{
    static constexpr const char *nowdate = "0001-01-01T00:00:00Z";
    if (json.contains("Created") && json["Created"].isString()) {
        const auto string = json["Created"].toString();
        if (string == nowdate) {
            setCreated(QDateTime::currentDateTime());
        } else {
            setCreated(QDateTime::fromString(string, Qt::ISODateWithMs));
        }
    } else {
        qWarning() << "Cannot find string \"Created\"";
    }
}
void Peer::setLastSeenFromJSON(const QJsonObject &json)
{
    static constexpr const char *nowdate = "0001-01-01T00:00:00Z";
    if (json.contains("LastSeen") && json["LastSeen"].isString()) {
        const auto string = json["LastSeen"].toString();
        if (string == nowdate) {
            setLastSeen(QDateTime::currentDateTime());
        } else {
            setLastSeen(QDateTime::fromString(string, Qt::ISODateWithMs));
        }
    } else {
        qWarning() << "Cannot find string \"LastSeen\"";
    }
}
void Peer::setIsOnlineFromJSON(const QJsonObject &json)
{
    if (json.contains("Online") && json["Online"].isBool()) {
        setIsOnline(json["Online"].toBool());
    } else {
        qWarning() << "Cannot find bool \"Online\"";
    }
}
void Peer::setIsActiveFromJSON(const QJsonObject &json)
{
    if (json.contains("Active") && json["Active"].isBool()) {
        setIsActive(json["Active"].toBool());
    } else {
        qWarning() << "Cannot find bool \"Active\"";
    }
}
void Peer::setIsCurrentExitNodeFromJson(const QJsonObject &json)
{
    if (json.contains("ExitNode") && json["ExitNode"].isBool()) {
        setIsCurrentExitNode(json["ExitNode"].toBool());
    } else {
        qWarning() << "Cannot find bool \"ExitNode\"";
    }
}
void Peer::setIsExitNodeFromJSON(const QJsonObject &json)
{
    if (json.contains("ExitNodeOption") && json["ExitNodeOption"].isBool()) {
        setIsExitNode(json["ExitNodeOption"].toBool());
    } else {
        qWarning() << "Cannot find bool \"ExitNode\"";
    }
}
void Peer::setSSHHostKeysFromJSON(const QJsonObject &json)
{
    QStringList keys{};
    if (json.contains("sshHostKeys")) {
        if (json["sshHostKeys"].isArray()) {
            const auto arr = json["sshHostKeys"].toArray();
            for (const auto &key : arr) {
                if (key.isString()) {
                    keys.append(key.toString());
                } else {
                    qWarning() << "sshHostKeys contains non-string";
                }
            }
        } else {
            qWarning() << "\"SSHHostKeys\" is not an array";
        }
    }
    setSSHHostKeys(keys);
}

bool Peer::setTo(const Peer *other)
{
    bool result = setId(other->id());
    result |= setPublicKey(other->publicKey());
    result |= setHostName(other->hostName());
    result |= setDNSName(other->dnsName());
    result |= setOs(other->os());
    result |= setTailscaleIps(other->tailscaleIps());
    result |= setRelay(other->relay());
    result |= setRxBytes(other->rxBytes());
    result |= setTxBytes(other->txBytes());
    result |= setCreated(other->created());
    result |= setLastSeen(other->lastSeen());
    result |= setIsOnline(other->isOnline());
    result |= setIsActive(other->isActive());
    result |= setIsCurrentExitNode(other->isCurrentExitNode());
    result |= setIsExitNode(other->isExitNode());
    result |= setSSHHostKeys(other->sshHostKeys());
    return result;
}
QString Peer::getSSHCommand() const
{
    if (!mIsRunningSSH) {
        return "";
    }
    return QString("tailscale ssh %1").arg(mDNSName);
}

const QString &Peer::id() const
{
    return mId;
}

const QString &Peer::publicKey() const
{
    return mPublicKey;
}

const QString &Peer::hostName() const
{
    return mHostName;
}

const QString &Peer::dnsName() const
{
    return mDNSName;
}

const QString &Peer::os() const
{
    return mOs;
}

const QStringList &Peer::tailscaleIps() const
{
    return mTailscaleIps;
}

const QString &Peer::relay() const
{
    return mRelay;
}

long Peer::rxBytes() const
{
    return mRxBytes;
}

long Peer::txBytes() const
{
    return mTxBytes;
}

const QDateTime &Peer::created() const
{
    return mCreated;
}

const QDateTime &Peer::lastSeen() const
{
    return mLastSeen;
}

bool Peer::isOnline() const
{
    return mIsOnline;
}

bool Peer::isActive() const
{
    return mIsActive;
}
bool Peer::isCurrentExitNode() const
{
    return mIsCurrentExitNode;
}
bool Peer::isExitNode() const
{
    return mIsExitNode;
}
const QStringList &Peer::sshHostKeys() const
{
    return mSSHHostKeys;
}
bool Peer::isRunningSSH() const
{
    return mIsRunningSSH;
}

Peer &Peer::operator=(const Peer &other)
{
    if (this == &other) {
        return *this;
    }
    this->setTo(&other);
    return *this;
}
