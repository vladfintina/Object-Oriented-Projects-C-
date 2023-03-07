#pragma once
//Melodii Rank
#include <QtWidgets/QWidget>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qslider.h>
#include "Service.h"
#include <QtWidgets/QFormLayout.h>
#include <QtWidgets/QMessageBox.h>
#include <QPainter.h>
#include <qlistwidget.h>
#include <qlabel.h>



class MyView :public QAbstractTableModel {
	vector<Melodie> v;
	Service& service;

public:

	MyView(QObject *parent, Service& service): service{service}, QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return v.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
		{
			Melodie melodie = v.at(index.row());
			if (index.column() == 0)
			{
				return QString::number(melodie.get_id());
			}
			if (index.column() == 1)
			{

				return QString::fromStdString(melodie.get_titlu());
			}
			if (index.column() == 2)
			{

				return QString::fromStdString(melodie.get_artist());
			}
			if (index.column() == 3)
			{

				return QString::number(melodie.get_rank());

			}
			if (index.column() == 4)
			{
				int nr = service.filtrareRankEgal(melodie);
				return QString::number(nr);
			}

		}

		return QVariant();

	}

	MyView() = default;
	void setElems(vector<Melodie> ve)
	{
		v = ve;
		auto top = createIndex(0, 0);
		auto bottom = createIndex(ve.size(), 5);
		emit dataChanged(top, bottom);
		emit layoutChanged();
	}

};


class GUI : public QWidget
{
	Service& service;
	

public:
	GUI(Service& service) : service{ service } {
		innit();
	}

	QLineEdit* titlu = new QLineEdit;
	QSlider* slider = new QSlider;

	void innit() {

		auto mainLayout = new QHBoxLayout();
		
		//left layout
		auto form = new QFormLayout();
		auto leftLayout = new QVBoxLayout();
		auto label = new QLabel("Titlu");
		/*auto titlu = new QLineEdit;
		auto slider = new QSlider;*/
		slider->setRange(0, 10);
		slider->setOrientation(Qt::Horizontal);
		auto buton_update = new QPushButton("Update");
		auto buton_delete = new QPushButton("Delete");

		form->addRow("Titlu", titlu);
		//form->addWidget(label);
		form->addWidget(titlu);
		form->addWidget(buton_update);
		form->addWidget(buton_delete);
		form->addWidget(slider);
		leftLayout->addLayout(form);

		mainLayout->addLayout(leftLayout);

		//right layout
		auto rightLayout = new QHBoxLayout();
		tablel->setModel(model);
		model->setElems(service.get_All());
		rightLayout->addWidget(tablel);
		
		mainLayout->addLayout(rightLayout);
		//
		auto underLayout = new QHBoxLayout();
		mainLayout->addLayout(underLayout);

		this->setLayout(mainLayout);

		//connections

		QObject::connect(tablel->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			auto sModel = tablel->selectionModel();
			if (sModel->selectedIndexes().isEmpty())
			{ 
				titlu->setText("");
				slider->setValue(0);
				return;
			}
			auto index = sModel->selectedIndexes().at(0);
			
			if (sModel->selectedIndexes().size() != 1)
			{
				auto index2 = sModel->selectedIndexes().at(1);
				auto index3 = sModel->selectedIndexes().at(3);
				//qDebug() << index.data(Qt::DisplayRole).toString();
				titlu->setText(index2.data(Qt::DisplayRole).toString());// ?? de ce nu merge
				slider->setValue(index3.data(Qt::DisplayRole).toInt());
			}
			
			});;

		QObject::connect(buton_update, &QPushButton::clicked, this, &GUI::update);
		QObject::connect(buton_delete, &QPushButton::clicked, this, &GUI::delete_song);
		

	}

	void update()
	{
		auto sModel = tablel->selectionModel();
		if (sModel->selectedIndexes().isEmpty())
			return;
		auto index = sModel->selectedIndexes().at(0);
		int id = index.data(Qt::DisplayRole).toInt();
		string titlu_update = titlu->text().toStdString();
		int rank_update = slider->value();
		service.update(id, titlu_update, rank_update);
		model->setElems(service.get_All());
		repaint();
	}

	void delete_song()
	{
		auto sModel = tablel->selectionModel();
		if (sModel->selectedIndexes().isEmpty())
			return;
		auto index = sModel->selectedIndexes().at(0);
		auto index2 = sModel->selectedIndexes().at(2);
		int id = index.data(Qt::DisplayRole).toInt();
		//auto artist = index2.data(Qt::DisplayRole).toString();
		string artist = service.artistMelodie(id);
		int numar_melodii = service.nrMelodiiArtist(artist);

		if (numar_melodii == 1)
		{
			QMessageBox::warning(nullptr, "Error", "Artistul mai are doar 1 melodie!");
			return;

		}
		service.stergeMelodie(id);
		model->setElems(service.get_All());
		repaint();
	}

	void paintEvent(QPaintEvent* ev)override {
		QPainter p{ this };
		vector<int>inaltime(11);
		for (auto& so : service.get_All()) {
			int nr = so.get_rank();
			inaltime[nr]++;
		}
		p.drawRect(500, p.device()->height() - 20 * inaltime[0], 20, 500);
		p.drawRect(0, p.device()->height() - 20 * inaltime[1], 20, 500);
		p.drawRect(50, p.device()->height() - 20 * inaltime[2], 20, 500);
		p.drawRect(100, p.device()->height() - 20 * inaltime[3], 20, 500);
		p.drawRect(150, p.device()->height() - 20 * inaltime[4], 20, 500);
		p.drawRect(200, p.device()->height() - 20 * inaltime[5], 20, 500);
		p.drawRect(250, p.device()->height() - 20 * inaltime[6], 20, 500);
		p.drawRect(300, p.device()->height() - 20 * inaltime[7], 20, 500);
		p.drawRect(350, p.device()->height() - 20 * inaltime[8], 20, 500);
		p.drawRect(400, p.device()->height() - 20 * inaltime[9], 20, 500);
		p.drawRect(450, p.device()->height() - 20 * inaltime[10], 20, 500);
	}
	MyView* model = new MyView(0, service);
	QTableView* tablel = new QTableView;
private:
};
