/*
	Copyright (C) 2008 by Warzone Resurrection Team

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this program. If not, see
	<http://www.gnu.org/licenses/>.
*/
#ifndef QWZM_H
#define QWZM_H

#include <QApplication>
#include <QMainWindow>
#include <QtOpenGL>

#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

extern "C" {
#include "wzmutils.h"
}

#include "ui_qwzm.h"
#include "ui_animationview.h"
#include "ui_connectorview.h"

/** Animation view */
class QAnimViewer : public QDialog, private Ui_AnimationView
{
	Q_OBJECT
	public:
	QAnimViewer(QWidget *parent = 0);
	~QAnimViewer();
	void setModel(QStandardItemModel *model);
	void updateModel();
	QModelIndex selectedIndex();
	void setSelectedIndex(int idx);
};

/** Connector view */
class QConnectorViewer : public QDialog, private Ui_ConnectorView
{
	Q_OBJECT
	public:
	QConnectorViewer(QWidget *parent = 0);
	~QConnectorViewer();
	void setModel(QStandardItemModel *model);
	void updateModel();
	QModelIndex selectedIndex();
	void setSelectedIndex(int idx);
};

/** WZM Viewer */
class QWzmViewer : public QMainWindow, private Ui::QWZM
{
	Q_OBJECT
	public:
	QWzmViewer(QWidget *parent = 0);
	~QWzmViewer();

	protected slots:
	void saveAs();
	void save();
	void open3DS();
        void open();
	void toggleWireframe();
	void toggleCulling();
	void setTeam(int index);
	void tick();
	void toggleAnimation();
	void toggleScale();
	void toggleSwapYZ();
	void toggleReverseWinding();
	void toggleFlipVerticalTexCoords();
	void setMesh(int index);
	void toggleEditAnimation();
	void toggleEditConnectors();
	void animLock();
	void animUnlock();

        void rowsChanged(const QModelIndex &parent, int start, int end);
        void dataChanged(const QModelIndex &first, const QModelIndex &last);
	void reloadFrames();

	void prependFrame();
	void appendFrame();
	void removeFrame();

	private:
	QString filename;
	MODEL *psModel;
	QStandardItemModel anim, connectors;
        MODEL *load3DS(QString input);
        MODEL *loadPIE(QString input);
        int savePIE(const char *filename, const MODEL *psModel, int pieVersion, int type);
        void setModel(const QFileInfo &texPath);
	QAnimViewer *animView;
	QConnectorViewer *connectorView;

private slots:
        void on_cb_visMesh_currentIndexChanged(int index);
};
#endif
