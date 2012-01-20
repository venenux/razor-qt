/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -p org_freedesktop_UPower UPowerInterface.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef ORG_FREEDESKTOP_UPOWER_H_1325775979
#define ORG_FREEDESKTOP_UPOWER_H_1325775979

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.freedesktop.UPower - to be replaced by razorpower library functionality
 */
class OrgFreedesktopUPowerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.UPower"; }

public:
    OrgFreedesktopUPowerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopUPowerInterface();

    Q_PROPERTY(bool CanHibernate READ canHibernate)
    inline bool canHibernate() const
    { return qvariant_cast< bool >(property("CanHibernate")); }

    Q_PROPERTY(bool CanSuspend READ canSuspend)
    inline bool canSuspend() const
    { return qvariant_cast< bool >(property("CanSuspend")); }

    Q_PROPERTY(QString DaemonVersion READ daemonVersion)
    inline QString daemonVersion() const
    { return qvariant_cast< QString >(property("DaemonVersion")); }

    Q_PROPERTY(bool IsDocked READ isDocked)
    inline bool isDocked() const
    { return qvariant_cast< bool >(property("IsDocked")); }

    Q_PROPERTY(bool LidForceSleep READ lidForceSleep)
    inline bool lidForceSleep() const
    { return qvariant_cast< bool >(property("LidForceSleep")); }

    Q_PROPERTY(bool LidIsClosed READ lidIsClosed)
    inline bool lidIsClosed() const
    { return qvariant_cast< bool >(property("LidIsClosed")); }

    Q_PROPERTY(bool LidIsPresent READ lidIsPresent)
    inline bool lidIsPresent() const
    { return qvariant_cast< bool >(property("LidIsPresent")); }

    Q_PROPERTY(bool OnBattery READ onBattery)
    inline bool onBattery() const
    { return qvariant_cast< bool >(property("OnBattery")); }

    Q_PROPERTY(bool OnLowBattery READ onLowBattery)
    inline bool onLowBattery() const
    { return qvariant_cast< bool >(property("OnLowBattery")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> AboutToSleep(const QString &action)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(action);
        return asyncCallWithArgumentList(QLatin1String("AboutToSleep"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> > EnumerateDevices()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("EnumerateDevices"), argumentList);
    }

    inline QDBusPendingReply<> Hibernate()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Hibernate"), argumentList);
    }

    inline QDBusPendingReply<bool> HibernateAllowed()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("HibernateAllowed"), argumentList);
    }

    inline QDBusPendingReply<> Suspend()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Suspend"), argumentList);
    }

    inline QDBusPendingReply<bool> SuspendAllowed()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("SuspendAllowed"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void Changed();
    void DeviceAdded(const QString &in0);
    void DeviceChanged(const QString &in0);
    void DeviceRemoved(const QString &in0);
    void NotifyResume(const QString &in0);
    void NotifySleep(const QString &in0);
    void Resuming();
    void Sleeping();
};

namespace org {
  namespace freedesktop {
    typedef ::OrgFreedesktopUPowerInterface UPower;
  }
}
#endif
