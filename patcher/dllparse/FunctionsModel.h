#pragma once

#include <QAbstractTableModel>
#include <Formatter.h>

#include "LibraryInfo.h"

class FunctionsModel : public QAbstractTableModel
{
	Q_OBJECT

public slots:
    void modelChanged() { reset(); }
    void on_currentndexChanged(int index)
    {
         m_libIndex = index;
         reset();
    }

public:
    enum COLS
    {
        COL_NAME = 0,
        COUNT_COL
    };

	FunctionsModel(QObject *v_parent)
		: QAbstractTableModel(v_parent), m_LibInfos(NULL) {}

	virtual ~FunctionsModel() { }

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

	int columnCount(const QModelIndex &parent) const { return COUNT_COL; }
	int rowCount(const QModelIndex &parent) const { return countElements(); }

	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &, const QVariant &, int);

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const
	{
		//no index item pointer
		return createIndex(row, column);
	}

	QModelIndex parent(const QModelIndex &index) const { return QModelIndex(); } // no parent

public slots:
    void setLibraries(LibInfos* exes)
    {
        if (this->m_LibInfos != NULL) {
            //disconnect old
            QObject::disconnect(this->m_LibInfos, SIGNAL(listChanged()), this, SLOT( on_listChanged() ) );
        }
        this->m_LibInfos = exes;
        reset();
        if (this->m_LibInfos != NULL) {
            QObject::connect(this->m_LibInfos, SIGNAL(listChanged()), this, SLOT( on_listChanged() ) );
        }
    }
protected slots:
    void on_listChanged() { reset(); }

protected:
    int countElements() const;

	LibInfos* m_LibInfos;
    size_t m_libIndex;
};
