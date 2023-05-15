// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2023 Fabian Köhler <me@fkoehler.org>
#ifndef TAILCTL_TAILDROP_PROCESS_H
#define TAILCTL_TAILDROP_PROCESS_H

#include <QObject>
#include <QProcess>

class TaildropProcess : public QObject
{
    Q_OBJECT

private:
    QProcess mProcess;
    QString mExecutable;
    bool mEnabled;
    QString mDirectory;
    QString mStrategy;

public:
    TaildropProcess(const QString &executable, bool enabled, const QString &directory, const QString &strategy, QObject *parent = nullptr);

protected:
    void stopProcess();
    void restartProcess();

public slots:
    void setExecutable(const QString &executable);
    void setEnabled(bool enabled);
    void setDirectory(const QString &directory);
    void setStrategy(const QString &strategy);
};

#endif /* TAILCTL_TAILDROP_PROCESS_H */
