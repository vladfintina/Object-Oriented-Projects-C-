#pragma once
//Tractoare
#include <QtWidgets/QMainWindow>
#include "ui_Tractoare.h"
#include <qtableview.h>
#include <qtablewidget.h>
#include "Service.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <qspinbox.h>
#include "qpainter.h"



class MyTable : public QAbstractTableModel
{

	vector<Tractor> v;
	Service& service;
	string tip = "";


public:
	MyTable(QObject* parent, Service& service): service{service}, QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return v.size();

	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override{
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		
		Tractor tractor = v.at(index.row());
		if (role == Qt::DisplayRole)
		{


			if (index.column() == 0)
			{
				return QString::number(tractor.get_id());
			}
			if (index.column() == 1)
			{
				return QString::fromStdString(tractor.get_denumire());
			}
			if (index.column() == 2)
			{
				return QString::fromStdString(tractor.get_tip());
			}
			if (index.column() == 3)
			{
				return QString::number(tractor.get_nrRoti());
			}
			if (index.column() == 4)
			{
				int nr = 0;
				nr = service.sameType(tractor);
				return QString::number(nr);
			}

		}
		if (role == Qt::BackgroundRole)
			{
			if (tractor.get_tip() == tip)
				return QColor(Qt::red);
			}

		
		return QVariant();

	}
	MyTable() = default;

	void setElems(vector<Tractor> ve, string tip)
	{
		v = ve;
		this->tip = tip;
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
	MyTable* table = new MyTable(0, service);
	QTableView* tableView = new QTableView;
	
	
	QSpinBox* idEdit = new QSpinBox;
	QLineEdit* denumireEdit = new QLineEdit;
	QLineEdit* tipEdit = new QLineEdit;
	QSpinBox* nrRotiEdit = new QSpinBox;
	QPushButton* add_button = new QPushButton("Adauga");
	QComboBox* tipFiltrare = new QComboBox();

	void innit()
	{

		QHBoxLayout* mainWindowlayout = new QHBoxLayout;
		tableView->setMaximumHeight(300);
		auto idLabel = new QLabel("ID:");
		auto denumireLabel = new QLabel("Denumire:");
		auto tipLabel = new QLabel("Tip:");
		auto nrRotiLabel = new QLabel("Numar roti:");
		QVBoxLayout* leftLayout = new QVBoxLayout;

		idEdit->setMinimum(0);
		idEdit->setMaximum(1000);

		nrRotiEdit->setMinimum(2);
		nrRotiEdit->setMaximum(16);
		nrRotiEdit->setSingleStep(2);


		leftLayout->addWidget(idLabel);
		leftLayout->addWidget(idEdit);
		leftLayout->addWidget(denumireLabel);
		leftLayout->addWidget(denumireEdit);
		leftLayout->addWidget(tipLabel);
		leftLayout->addWidget(tipEdit);
		leftLayout->addWidget(nrRotiLabel);
		leftLayout->addWidget(nrRotiEdit);

		leftLayout->addWidget(add_button);

		leftLayout->addWidget(tipFiltrare);

		mainWindowlayout->addLayout(leftLayout);

		tableView->setModel(table);
		QVBoxLayout* rightLayout = new QVBoxLayout;

		rightLayout->addWidget(tableView);
		table->setElems(service.getAll(), "");

		mainWindowlayout->addLayout(rightLayout);

		this->setLayout(mainWindowlayout);

		
		//connections
		QObject::connect(add_button, &QPushButton::clicked, this, &GUI::add);
		QObject::connect(tipFiltrare, &QComboBox::currentTextChanged, [&]() {
			string tip = tipFiltrare->currentText().toStdString();
			table->setElems(service.getAll(), tip);
			
			});
		QObject::connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
			repaint();
			});

		//

		update_comboBox();
	}

	void add()
	{
		int id, nrRoti;
		string denumire, tip;
		
		denumire = denumireEdit->text().toStdString();
		tip = tipEdit->text().toStdString();
		id = idEdit->value();
		nrRoti = nrRotiEdit->value();

		try {
			service.addTractor(id, denumire, tip, nrRoti);
		}
		catch (string exceptie)
		{
			QMessageBox::warning(nullptr, "VALIDATION ERROR", QString::fromStdString(exceptie));
			return;
		}

		table->setElems(service.getAll(), "");
		update_comboBox();
		

	}

	void update_comboBox()
	{
		tipFiltrare->clear();
		auto types = service.Types();
		for (auto type : types)
		{
				tipFiltrare->addItem(QString::fromStdString(type));
		}

	}

	void paintEvent(QPaintEvent* eveniment) override {
		QPainter g{ this };
		g.setPen(Qt::green);

		auto sTable = tableView->selectionModel();
		if (sTable->selectedIndexes().isEmpty())
		{
			g.drawPoint(0, 0);
			return;
		}

		auto row = sTable->selectedIndexes().at(0).row();
		auto cellIndex = tableView->model()->index(row, 3);
		int roti = tableView->model()->data(cellIndex, Qt::DisplayRole).toInt();
		for (int i = 1;i <= roti;i++)
		{
			g.drawEllipse(width() - i * 50, height() - 50, 50, 50);

		}




	}


};
