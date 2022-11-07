/***************************************************************************
 * QGeoView is a Qt / C ++ widget for visualizing geographic data.
 * Copyright (C) 2018-2022 Andrey Yaroshenko.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see https://www.gnu.org/licenses.
 ****************************************************************************/

#include "mainwindow.h"

#include <QGeoView/QGVLayerBing.h>
#include <QGeoView/QGVLayerGoogle.h>
#include <QGeoView/QGVLayerOSM.h>
#include <QRadioButton>
#include <QVBoxLayout>

MainWindow::MainWindow()
{
    setWindowTitle("QGeoView Samples - background");

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(new QVBoxLayout());

    QGV::setNetworkManager(new QNetworkAccessManager());

    mMap = new QGVMap(this);

    // Selection list
    centralWidget()->layout()->addWidget(createSelectionList());

    // Map itself
    centralWidget()->layout()->addWidget(mMap);

    // Show whole world
    auto target = mMap->getProjection()->boundaryGeoRect();
    mMap->cameraTo(QGVCameraActions(mMap).scaleTo(target));
}

MainWindow::~MainWindow()
{}

QGroupBox* MainWindow::createSelectionList()
{
    const QString customURI = "http://c.tile.stamen.com/watercolor/${z}/${x}/${y}.jpg";
    const QList<QPair<QString, QGVLayer*>> layers = {
        { "GOOGLE_SATELLITE", new QGVLayerGoogle(QGV::TilesType::Satellite) },
        { "GOOGLE_HYBRID", new QGVLayerGoogle(QGV::TilesType::Hybrid) },
        { "GOOGLE_SCHEMA", new QGVLayerGoogle(QGV::TilesType::Schema) },
        { "BING_SATELLITE", new QGVLayerBing(QGV::TilesType::Satellite) },
        { "BING_HYBRID", new QGVLayerBing(QGV::TilesType::Hybrid) },
        { "BING_SCHEMA", new QGVLayerBing(QGV::TilesType::Schema) },
        { "CUSTOM_OSM", new QGVLayerOSM(customURI) },
        { "OSM", new QGVLayerOSM() },
    };

    QGroupBox* groupBox = new QGroupBox(tr("Background maps"));
    groupBox->setLayout(new QVBoxLayout);

    QRadioButton* radioButton;

    for (auto pair : layers) {
        auto name = pair.first;
        auto layer = pair.second;

        layer->hide();
        mMap->addItem(layer);

        radioButton = new QRadioButton(name);

        connect(radioButton, &QRadioButton::clicked, this, [layer, layers](const bool checked) {
            if (!checked)
                return;

            for (auto pair : layers) {
                auto layer = pair.second;
                layer->hide();
            }
            layer->show();
        });

        groupBox->layout()->addWidget(radioButton);
    }

    // Last map will be default
    radioButton->click();

    return groupBox;
}
