#pragma once
//Taskuri
#include "Service.h"
#include <QtWidgets/QTableView>
#include <QtWidgets/qboxlayout>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qtablewidget.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlineedit.h>
#include <QtWidgets/QListView>


class MyView :public QAbstractTableModel {
private:
    vector<Task> v;
    Service& s;
public:
    MyView(QObject* parent, Service& s) :s
    { s }, QAbstractTableModel(parent)
    {}
    int rowCount(const QModelIndex& parent = QModelIndex())const override {
        return v.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex())const override {
        return 4;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
        if (role == Qt::DisplayRole)
        {
            Task a = v.at(index.row());
            if (index.column() == 0)
                return QString::number(a.get_id());
            if (index.column() == 1)
                return QString::fromStdString(a.get_descriere());
            if (index.column() == 2)
                return QString::number(a.get_programatori().size());
            if (index.column() == 3)
                return QString::fromStdString(a.get_stare());
        }

        return QVariant();
    }
    MyView() = default;
    void setElems(vector<Task>ve)
    {
        v = ve;
        auto top = createIndex(0, 0);
        auto bottom = createIndex(ve.size(), 1);
        emit dataChanged(top, bottom);
        emit layoutChanged();
    }
};


class GUI : public QWidget, public Observer
{
public:
    GUI(Service s) :s
    { s } {
        innit();
        innit_w();
    }
private:
    //initializare
    void innit() {
        s.addObserver(this);
        auto layout_main = new QHBoxLayout;
        this->setLayout(layout_main);
        auto layout_st = new QVBoxLayout;
        auto layout_dr = new QVBoxLayout;
        layout_main->addLayout(layout_st);
        layout_main->addLayout(layout_dr);
        auto btn_add = new QPushButton{ "add" };
        auto form = new QFormLayout;
        form->addRow("Id", id);
        form->addRow("Descriere", descriere);
        form->addRow("Prof1", prof1);
        form->addRow("Prof2", prof2);
        form->addRow("Prof3", prof3);
        form->addRow("Prof4", prof4);
        form->addRow("Stare", stare);
        form->addRow("Cautare", cautare);
        tablel->setModel(model);
        model->setElems(s.getAll());
        layout_st->addLayout(form);
        layout_st->addWidget(btn_add);
        layout_dr->addWidget(tablel);
        QObject::connect(cautare, &QLineEdit::textChanged, this, &GUI::filtrare);
        QObject::connect(btn_add, &QPushButton::clicked, this, &GUI::add);
    }
    void innit_w()
    {
        auto layout_main1 = new QVBoxLayout;
        auto layout_main2 = new QVBoxLayout;
        auto layout_main3 = new QVBoxLayout;
        open->setLayout(layout_main1);
        open->setWindowTitle("Open");
        inprogress->setWindowTitle("Progres");
        closed->setWindowTitle("Closed");
        inprogress->setLayout(layout_main2);
        closed->setLayout(layout_main3);
        layout_main1->addWidget(tablel1);
        layout_main2->addWidget(tablel2);
        layout_main3->addWidget(tablel3);
        tablel1->setModel(model1);
        tablel2->setModel(model2);
        tablel3->setModel(model3);
        string Open = "Open";
        string Inprogress = "Inprogress";
        string Closed = "Closed";
        model1->setElems(s.filtrareStare(Open));
        model2->setElems(s.filtrareStare(Inprogress));
        model3->setElems(s.filtrareStare(Closed));
        auto btn_1_o = new QPushButton{ "Open" };
        auto btn_1_c = new QPushButton{ "Closed" };
        auto btn_1_i = new QPushButton{ "Inprogress" };
        auto btn_2_o = new QPushButton{ "Open" };
        auto btn_2_c = new QPushButton{ "Closed" };
        auto btn_2_i = new QPushButton{ "Inprogress" };
        auto btn_3_o = new QPushButton{ "Open" };
        auto btn_3_c = new QPushButton{ "Closed" };
        auto btn_3_i = new QPushButton{ "Inprogress" };
        layout_main1->addWidget(btn_1_o);
        layout_main1->addWidget(btn_1_c);
        layout_main1->addWidget(btn_1_i);
        layout_main2->addWidget(btn_2_o);
        layout_main2->addWidget(btn_2_c);
        layout_main2->addWidget(btn_2_i);
        layout_main3->addWidget(btn_3_o);
        layout_main3->addWidget(btn_3_c);
        layout_main3->addWidget(btn_3_i);
        open->show();
        inprogress->show();
        closed->show();
        QObject::connect(btn_1_o, &QPushButton::clicked, [&] {
            auto sModel = tablel1->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Open);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_1_i, &QPushButton::clicked, [&] {
            auto sModel = tablel1->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            qDebug() << id;
            s.updateStatus(id, Inprogress);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_1_c, &QPushButton::clicked, [&] {
            auto sModel = tablel1->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Closed);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_2_o, &QPushButton::clicked, [&] {
            auto sModel = tablel2->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Open);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_2_i, &QPushButton::clicked, [&] {
            auto sModel = tablel2->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Inprogress);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_2_c, &QPushButton::clicked, [&] {
            auto sModel = tablel2->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Closed);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_3_o, &QPushButton::clicked, [&] {
            auto sModel = tablel3->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Open);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_3_i, &QPushButton::clicked, [&] {
            auto sModel = tablel3->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Inprogress);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
        QObject::connect(btn_3_c, &QPushButton::clicked, [&] {
            auto sModel = tablel3->selectionModel();
            if (sModel->selectedIndexes().isEmpty())
                return;
            auto index = sModel->selectedIndexes().at(0);
            int id = index.data(Qt::DisplayRole).toInt();
            s.updateStatus(id, Closed);
            model1->setElems(s.filtrareStare(Open));
            model2->setElems(s.filtrareStare(Inprogress));
            model3->setElems(s.filtrareStare(Closed));
            });
    }
    Service s;
    MyView* model = new MyView(0, s);
    QLineEdit* id = new QLineEdit;
    QLineEdit* descriere = new QLineEdit;
    QLineEdit* stare = new QLineEdit;
    QLineEdit* prof1 = new QLineEdit;
    QLineEdit* prof2 = new QLineEdit;
    QLineEdit* prof3 = new QLineEdit;
    QLineEdit* prof4 = new QLineEdit;
    QLineEdit* cautare = new QLineEdit;
    QTableView* tablel = new QTableView;
    QWidget* open = new QWidget;
    QWidget* inprogress = new QWidget;
    QWidget* closed = new QWidget;
    MyView* model1 = new MyView(0, s);
    MyView* model2 = new MyView(0, s);
    MyView* model3 = new MyView(0, s);
    QListView* tablel1 = new QListView;
    QListView* tablel2 = new QListView;
    QListView* tablel3 = new QListView;
    void filtrare()
    {
        vector<Task>v;
        if (cautare->text().toStdString() == "")
            v = s.getAll();
        else v = s.cautaTaskProg(cautare->text().toStdString());
        model->setElems(v);
    }
    void add()
    {
        string  descrieres, prof1s, prof2s, prof3s, prof4s, stares;
        int ids = id->text().toInt();
        descrieres = descriere->text().toStdString();
        prof1s = prof1->text().toStdString();
        prof2s = prof2->text().toStdString();
        prof3s = prof3->text().toStdString();
        prof4s = prof4->text().toStdString();
        stares = stare->text().toStdString();
        try {
            prof4->text().toStdString();
            s.adaugaTask(ids, descrieres, prof1s, prof2s, prof3s, prof4s, stares);
        }
        catch (int e)
        {
            QMessageBox::warning(nullptr, "Error", "ba.");
        }
        filtrare();
    }
    void update() override {
        string Open = "Open";
        string Inprogress = "Inprogress";
        string Closed = "Closed";
        model1->setElems(s.filtrareStare(Open));
        model2->setElems(s.filtrareStare(Inprogress));
        model3->setElems(s.filtrareStare(Closed));
        filtrare();
    }
    void change_o(MyView* model, string st)
    {
        auto sModel = tablel->selectionModel();
        if (sModel->selectedIndexes().isEmpty())
            return;
        auto index = sModel->selectedIndexes().at(0);
        int id = index.data(Qt::DisplayRole).toInt();
        string Open = "Open";
        s.updateStatus(id, Open);
        model->setElems(s.filtrareStare(st));
    }
    void change_p(MyView* model, string st)
    {
        auto sModel = tablel->selectionModel();
        if (sModel->selectedIndexes().isEmpty())
            return;
        auto index = sModel->selectedIndexes().at(0);
        int id = index.data(Qt::DisplayRole).toInt();
        string Inprogress = "Inprogress";
        s.updateStatus(id, Inprogress);
        model->setElems(s.filtrareStare(st));
    }
    void change_c(MyView* model, string st)
    {
        auto sModel = tablel->selectionModel();
        if (sModel->selectedIndexes().isEmpty())
            return;
        auto index = sModel->selectedIndexes().at(0);
        int id = index.data(Qt::DisplayRole).toInt();
        string Closed = "Closed";
        s.updateStatus(id, Closed);
        model->setElems(s.filtrareStare(st));
    }
};
