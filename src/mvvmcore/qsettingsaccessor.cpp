#include "qsettingsaccessor.h"
using namespace QtMvvm;

namespace QtMvvm {

class QSettingsAccessorPrivate
{
public:
	QSettingsAccessorPrivate(QSettings *settings);

	QSettings *settings;
};

}

QSettingsAccessor::QSettingsAccessor(QObject *parent) :
	QSettingsAccessor{new QSettings{}, parent}
{}

QSettingsAccessor::QSettingsAccessor(QSettings *settings, QObject *parent) :
	ISettingsAccessor{parent},
	d{new QSettingsAccessorPrivate{settings}}
{
	d->settings->setParent(this);
}

QSettingsAccessor::~QSettingsAccessor() = default;

bool QSettingsAccessor::contains(const QString &key) const
{
	return d->settings->contains(key);
}

QVariant QSettingsAccessor::load(const QString &key, const QVariant &defaultValue) const
{
	return d->settings->value(key, defaultValue);
}

void QSettingsAccessor::save(const QString &key, const QVariant &value)
{
	d->settings->setValue(key, value);
	emit entryChanged(key, value);
}

void QSettingsAccessor::remove(const QString &key)
{
	d->settings->remove(key);
	emit entryRemoved(key);
}

void QSettingsAccessor::sync()
{
	d->settings->sync();
}



QSettingsAccessorPrivate::QSettingsAccessorPrivate(QSettings *settings) :
	settings{settings}
{}
