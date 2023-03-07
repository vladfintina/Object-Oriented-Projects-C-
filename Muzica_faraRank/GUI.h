#pragma once
//Melodii fara rank
#include <QtWidgets/QMainWindow>
#include "ui_Muzica_faraRank.h"
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
#include <qformlayout.h>
#include "qpainter.h"


class MyTable :public QAbstractTableModel {

private:
	vector<Song> v;
	Service& service;

public:
	MyTable(QObject *parent, Service& s): service{s}, QAbstractTableModel(parent){}

	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return v.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 6;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		Song song = v.at(index.row());
		if (role == Qt::DisplayRole)
		{

			if (index.column() == 0)
			{
				return QString::number(song.get_id());
			}

			if (index.column() == 1)
			{

				return QString::fromStdString(song.get_titlu());
			}

			if (index.column() == 2)
			{

				return QString::fromStdString(song.get_artist());
			}

			if (index.column() == 3)
			{

				return QString::fromStdString(song.get_gen());
			}

			if (index.column() == 4)
			{
				int nr = 0;
				nr = service.nrSameArtist(song);
				return QString::number(nr);
			}

			if (index.column() == 5)
			{
				int nr = service.nrSameGenres(song);
				return QString::number(nr);
			}


		}

		return QVariant();


	}

	QVariant headerData(int section, Qt::Orientation ori, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (ori == Qt::Horizontal)
			{
				switch (section)
				{
				case 0:
					return tr("ID");
				case 1:
					return tr("Nume");
				case 2:
					return tr("Artist");
				case 3:
					return tr("Gen");
				case 4:
					return tr("Acelasi artist");
				case 5:
					return tr("Acelasi gen");

				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}

	MyTable() = default;

	void setElems(vector<Song> ve)
	{
		v = ve;
		auto top = createIndex(0, 0);
		auto bottom = createIndex(ve.size(), 6);
		emit dataChanged(top, bottom);
		emit layoutChanged();

	}


};


class GUI : public QWidget
{
private:
	Service& service;

public:
	GUI(Service& s) : service{ s } {
		QHBoxLayout* mainLayout = new QHBoxLayout;

		tableView->setModel(table);
		table->setElems(service.getAll());

		auto leftLayout = new QVBoxLayout;
		auto form = new QFormLayout;
		form->addRow("Titlu", titluEdit);
		form->addRow("Artist", artistEdit);
		genEdit->addItem("pop");
		genEdit->addItem("rock");
		genEdit->addItem("folk");
		genEdit->addItem("disco");
		form->addRow("Gen", genEdit);
		form->addRow(addBtn);
		form->addRow(deleteBtn);

		leftLayout->addLayout(form);
		mainLayout->addLayout(leftLayout);

		auto rightLayout = new QVBoxLayout;
		rightLayout->addWidget(tableView);

		mainLayout->addLayout(rightLayout);

		this->setLayout(mainLayout);

		repaint();

		//connections
		QObject::connect(addBtn, &QPushButton::clicked, [&]() {
			
			string titlu = titluEdit->text().toStdString();
			string artist = artistEdit->text().toStdString();
			string gen = genEdit->currentText().toStdString();
			service.addSong(titlu, artist, gen);
			table->setElems(service.getAll());
			repaint();
			});

		QObject::connect(deleteBtn, &QPushButton::clicked, [&]() {

			if (tableView->selectionModel()->selectedIndexes().isEmpty())
				return;

			auto row = tableView->selectionModel()->selectedIndexes().at(0).row();
			auto cellIndex = tableView->model()->index(row, 0);
			int id = tableView->model()->data(cellIndex, Qt::DisplayRole).toInt();

			service.deleteSong(id);
			table->setElems(service.getAll());
			repaint();

			});



	}
	MyTable* table = new MyTable(0, service);
	QTableView* tableView = new QTableView;

	QLineEdit* idEdit = new QLineEdit;
	QLineEdit* titluEdit = new QLineEdit;
	QLineEdit* artistEdit = new QLineEdit;
	QComboBox* genEdit = new QComboBox;

	QPushButton* addBtn = new QPushButton("Adauga");
	QPushButton* deleteBtn = new QPushButton("Sterge");


	void paintEvent(QPaintEvent* ev) override
	{
		QPoint c1(50, 50);
		QPoint c2(width() - 50, 50);
		QPoint c3(50, height() - 50);
		QPoint c4(width() - 50, height() - 50);
		QPainter p{ this };
		p.drawEllipse(c1, 10, 10);
		p.drawEllipse(c2, 10, 10);
		p.drawEllipse(c3, 10, 10);
		p.drawEllipse(c4, 10, 10);

		int pop = 0;
		int folk = 0;
		int rock = 0;
		int disco = 0;

		auto melodii = service.getAll();
		for (auto each : melodii)
		{
			if (each.get_gen() == "pop")
				pop++;
			if (each.get_gen() == "folk")
				folk++;
			if (each.get_gen() == "rock")
				rock++;
			if (each.get_gen() == "disco")
				disco++;
		}

		int i;
		for (i = 1; i <= pop; i++)
		{
			p.drawEllipse(c1, (i + 1) * 10, (i + 1) * 10);
		}

		for (i = 1; i <= folk; i++)
		{
			p.drawEllipse(c2, (i + 1) * 10, (i + 1) * 10);
		}

		for (i = 1; i <= rock; i++)
		{
			p.drawEllipse(c3, (i + 1) * 10, (i + 1) * 10);
		}

		for (i = 1; i <= disco; i++)
		{
			p.drawEllipse(c4, (i + 1) * 10, (i + 1) * 10);
		}
	}
};

