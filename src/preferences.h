#ifndef KTAILCTL_PREFERENCES_H
#define KTAILCTL_PREFERENCES_H

#include <QObject>

#include "libtailctlpp.h"

class Preferences : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool acceptRoutes READ acceptRoutes WRITE setAcceptRoutes NOTIFY acceptRoutesChanged)
    Q_PROPERTY(bool acceptDNS READ acceptDNS WRITE setAcceptDNS NOTIFY acceptDNSChanged)
    Q_PROPERTY(bool advertiseExitNode READ advertiseExitNode WRITE setAdvertiseExitNode NOTIFY advertiseExitNodeChanged)
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)
    Q_PROPERTY(QString operatorUser READ operatorUser WRITE setOperatorUser NOTIFY operatorUserChanged)
    Q_PROPERTY(bool shieldsUp READ shieldsUp WRITE setShieldsUp NOTIFY shieldsUpChanged)
    Q_PROPERTY(bool ssh READ ssh WRITE setSSH NOTIFY sshChanged)

private:
    bool mAcceptRoutes;
    bool mAcceptDNS;
    bool mAdvertiseExitNode;
    QString mHostname;
    QString mOperatorUser;
    bool mShieldsUp;
    bool mSSH;

signals:
    void acceptRoutesChanged(bool);
    void acceptDNSChanged(bool);
    void advertiseExitNodeChanged(bool);
    void hostnameChanged(const QString &);
    void operatorUserChanged(const QString &);
    void shieldsUpChanged(bool);
    void sshChanged(bool);

public:
    explicit Preferences(QObject *parent = nullptr);

    Q_INVOKABLE void refresh();

    bool acceptRoutes() const;
    bool acceptDNS() const;
    bool advertiseExitNode() const;
    const QString &hostname() const;
    const QString &operatorUser() const;
    bool shieldsUp() const;
    bool ssh() const;

    void setAcceptRoutes(bool acceptRoutes);
    void setAcceptDNS(bool acceptDNS);
    void setAdvertiseExitNode(bool advertiseExitNode);
    void setHostname(const QString &hostname);
    void setOperatorUser(const QString &operatorUser);
    void setShieldsUp(bool shieldsUp);
    void setSSH(bool ssh);
};

#endif /* KTAILCTL_PREFERENCES_H */
