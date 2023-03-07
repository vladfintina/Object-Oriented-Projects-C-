#pragma once
//Produse
#include <QtWidgets/QMainWindow>
#include "ui_Produse.h"
#include <QtWidgets/qtableview.h>
#include "Service.h"
#include <qlayout.h>
#include <qlineedit.h>
#include <qslider.h>
#include <qformlayout.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlabel.h>
//#include <>

class MyTable : public QAbstractTableModel {

	vector<Produs> v;
	Service& service;
	double pret = 0;

public:
	MyTable(QObject* parent, Service& service) :service{ service } ,QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return v.size();

	}

	int columnCount(const QModelIndex& parent = QModelIndex())const override {
		return 5;

	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		
		Produs produs = v.at(index.row());
		if (role == Qt::DisplayRole)
		{
			if (index.column() == 0)
			{
				return QString::number(produs.get_id());
			}

			if (index.column() == 1)
			{
				return QString::fromStdString(produs.get_nume());
			}

			if (index.column() == 2)
			{
				return QString::fromStdString(produs.get_tip());
			}

			if (index.column() == 3)
			{
				return QString::number(produs.get_pret());
			}

			if (index.column() == 4)
			{
				int nr = service.nrVocale(produs);
				return QString::number(nr);


			}
			

		}

		if (role == Qt::BackgroundRole)
		{
			if (produs.get_pret() <= pret)
				return QColor(Qt::red);
		}
		return QVariant();

	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				switch (section)
				{
				case 0:
					return tr("ID");
				case 1:
					return tr("Nume");
				case 2:
					return tr("Tip");
				case 3:
					return tr("Pret");
				case 4:
					return tr("NR Vocale");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}

	MyTable() = default;

	void setElems(vector<Produs> ve, double pret)
	{
		v = ve;
		this->pret = pret;
		auto top = createIndex(0, 0);
		auto bottom = createIndex(ve.size(), 5);
		emit dataChanged(top, bottom);
		emit layoutChanged();


	}


};


class typeWindow : public QWidget, public Observer
{
	Service& service;
	string type;
public:
	QLabel* label = new QLabel;
	typeWindow(Service& service, string type) : service{ service }, type{ type } {
		this->setWindowTitle(QString::fromStdString(type));
		label->setText(QString::number(service.typeNumber(type)));
		QFormLayout* form = new QFormLayout();
		form->addRow("Numar produse:", label);
		this->setLayout(form);
		this->show();
	}

	void update() override {
		label->setText(QString::number(service.typeNumber(type)));

	}

};


class GUI : public QWidget, public Observable 
{
	Service& service;

public:
	GUI(Service& service) : service{ service } {
		
		QHBoxLayout* mainLayout = new QHBoxLayout();
		QVBoxLayout* rightLayout = new QVBoxLayout();
		QVBoxLayout* leftlayout = new QVBoxLayout();

		QFormLayout* form = new QFormLayout();
		form->addRow("ID", idEdit);
		form->addRow("Nume", numeEdit);
		form->addRow("tip", tipEdit);
		form->addRow("pret", pretEdit);
		form->addRow(add_btn);

		slider->setOrientation(Qt::Horizontal);
		slider->setRange(1, 100);
		form->addRow(slider);

		leftlayout->addLayout(form);
		mainLayout->addLayout(leftlayout);

		tableView->setModel(table);
		rightLayout->addWidget(tableView);
		table->setElems(service.getAll(),0);

		mainLayout->addLayout(rightLayout);

		this->setLayout(mainLayout);

		set<string> types = service.tipuriProdus();
		for (auto elem : types)
		{
			typeWindow* twindow = new typeWindow(service, elem);
			this->addObserver(twindow);
		}

		//connections

		QObject::connect(add_btn, &QPushButton::clicked, [&]{
			int id = idEdit->text().toInt();
			string nume = numeEdit->text().toStdString();
			string tip = tipEdit->text().toStdString();
			double pret = pretEdit->text().toDouble();

			try {
				service.addProdus(id, nume, tip, pret);
			}
			catch (string exceptie)
			{
				QMessageBox::warning(nullptr, "Error", QString::fromStdString(exceptie));
				return;
			}
			table->setElems(service.getAll(),0);
			notify();

			});

		QObject::connect(slider, &QSlider::valueChanged, [&] {
			double pret = slider->value();
			table->setElems(service.getAll(), pret);
			
			});

	}
	MyTable* table = new MyTable(0, service);
	QTableView* tableView = new QTableView;
	
	QLineEdit* numeEdit = new QLineEdit;
	QLineEdit* idEdit = new QLineEdit;
	QLineEdit* tipEdit = new QLineEdit;
	QLineEdit* pretEdit = new QLineEdit;
	
	QPushButton* add_btn = new QPushButton("Adauga");

	QSlider* slider = new QSlider();


};
