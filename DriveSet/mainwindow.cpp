#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include <QMessageBox>
#include <math.h>
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
		
	
	QString str;
	
	qDebug()<<"sssss";
	
	ui->tableWidget->setColumnWidth(3, 500);
	ui->tableWidget->setColumnWidth(2, 500);
	QFont font(QStringLiteral("宋体"), 10, QFont::Normal);
	ui->tabWidget->setFont(font);
	ui->tabWidget->setTabText(0, QStringLiteral("通讯配置"));

	
	
	QString path = QCoreApplication::applicationDirPath();
	path.append("/GPS.cfg");
	qDebug()<<"path"<<path;
	if (!QFileInfo(path).exists())
	{
		 QMessageBox::information(this, QStringLiteral("丢失"), QStringLiteral("无法找到GPS.cfg文件"));
		 return;
	}
	else
	{
		db = QSqlDatabase::addDatabase("QSQLITE", "drive");//打开数据库
		db.setDatabaseName(path);
		db.open();
		if (!db.isOpen())
		{
			QMessageBox::information(this, QStringLiteral("数据库错误"), QStringLiteral("无法打开数据库"));
			return;
		}
	}

	ui->tabWidget->setCurrentIndex(0);
	on_tabWidget_currentChanged(0);
}

MainWindow::~MainWindow()
{


	for (int i=0; i<v_int.size(); i++)
	{
		QWidget *widget = ui->tableWidget->cellWidget(v_int.at(i), 1);
		delete widget;
	}
	v_int.clear();

	delete ui;
}

void MainWindow::on_closeButton_clicked()
{
	close();
}

void MainWindow::AddItem(QComboBox *combo, QStringList &editList ,QString &value)
{


	for (int i=1; i<editList.size(); i++)
	{
		QStringList twoList = editList.at(i).split("/");
		combo->addItem(twoList.at(1));

		if (twoList.at(0) == value)
		{
			combo->setCurrentIndex(i-1);
		}
	}


}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	curIndex = index;
	qDebug()<<"index"<<index;
	if ( index == 0)
	{
		if (Update == "0")
		{
			ui->addButton->hide();
			ui->deleteButton->hide();
			ui->tableWidget->hideColumn(3);
		}
		ui->tableWidget->clearContents();
		int row = ui->tableWidget->rowCount();
		for (int i=0; i<row; i++)
		{
			ui->tableWidget->removeRow(0);
		}
		if (row != 0)
		{
			for (int i=0; i<v_int.size(); i++)
			{
				ui->tableWidget->removeCellWidget(v_int.at(i), 1);

			}
			v_int.clear();
		}

		QSqlTableModel model(this, db);
		model.setEditStrategy(QSqlTableModel::OnManualSubmit);
		model.setTable("comm");
		model.select();
		int rowCount = model.rowCount();

		for (int i=0; i<rowCount; i++)
		{
			ui->tableWidget->insertRow(i);
			model.submitAll();
			int id = model.data(model.index(i, 0)).toInt();
			QString value = model.data(model.index(i, 1)).toString();
			QString descr = model.data(model.index(i, 2)).toString();
			QString edit = model.data(model.index(i, 3)).toString();
			QTableWidgetItem *table1 = new QTableWidgetItem(QString::number(id));
			ui->tableWidget->setItem(i, 0, table1);

			QStringList editList = edit.split(" ", QString::SkipEmptyParts);
			if ((editList.size() == 0) || (editList.at(0) != "Dropdown:"))
			{
				QTableWidgetItem *table2 = new QTableWidgetItem(value);
				ui->tableWidget->setItem(i, 1, table2);
			}
			else
			{
				combo = new QComboBox(this);
				AddItem( combo , editList, value);
				ui->tableWidget->setCellWidget(i, 1, combo);
				v_int.append(i);
			}

			QTableWidgetItem *table3 = new QTableWidgetItem(descr);
			ui->tableWidget->setItem(i, 2, table3);
			QTableWidgetItem *table4 = new QTableWidgetItem(edit);
			ui->tableWidget->setItem(i, 3, table4);
			model.submitAll();
		}

	}


}

void MainWindow::on_addButton_clicked()
{


	if (curIndex == 0)
	{
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		int column = ui->tableWidget->columnCount();
		for (int i=0; i<column; i++)
		{
			QTableWidgetItem *item = new QTableWidgetItem("");
			ui->tableWidget->setItem(row, i, item);
		}
	}

}

void MainWindow::on_deleteButton_clicked()
{

	if (curIndex == 0)
	{
		QModelIndex index = ui->tableWidget->currentIndex();

		if (!index.isValid())
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先选择一行"));
			return;
		}
		int row = index.row();

		ui->tableWidget->removeRow(row);
	}


}

void MainWindow::on_saveButton_clicked()
{
	if (curIndex == 0)
	{
		qDebug()<<"curIndex = 0";
		QSqlQuery query(db);
		query.exec("delete from comm");
		QSqlTableModel model(this, db);
		model.setEditStrategy(QSqlTableModel::OnManualSubmit);
		model.setTable("comm");
		model.select();

		int row = ui->tableWidget->rowCount();
		qDebug()<<"row"<<row;
		for (int i=0; i<row; i++)
		{
			model.insertRow(i);
			model.submitAll();
			QString id = ui->tableWidget->item(i, 0)->text();
			QString value ;

			QString descr = ui->tableWidget->item(i, 2)->text();
			QString edit = ui->tableWidget->item(i, 3)->text();
			QStringList editList = edit.split(" ", QString::SkipEmptyParts);
			if ((editList.size() == 0) || (editList.at(0) != "Dropdown:"))
			{
				if (ui->tableWidget->item(i, 1) == 0)
				{
					QComboBox *combo = (QComboBox*)ui->tableWidget->cellWidget(i, 1);
					QString text = combo->currentText();
				}
				else
				{
					value = ui->tableWidget->item(i, 1)->text();
				}
			}
			else
			{
				if (ui->tableWidget->item(i, 1) == 0)
				{
					QComboBox *combo = (QComboBox*)ui->tableWidget->cellWidget(i, 1);
					QString text = combo->currentText();
					for (int i=1; i<editList.size(); i++)
					{
						QStringList twoList = editList.at(i).split("/");
						if (twoList.at(1) == text)
						{
							value = twoList.at(0);
						}
					}
				}
				else
				{
					value = ui->tableWidget->item(i, 1)->text();
				}


			}

			model.setData(model.index(i, 0), id);
			qDebug()<<"i value"<<value;
			model.setData(model.index(i, 1), value);
			model.setData(model.index(i, 2), descr);
			model.setData(model.index(i, 3), edit);
			model.submitAll();
		}

	}

}

void MainWindow::on_helpButton_clicked()
{
	QProcess process(this);
	QString path = QCoreApplication::applicationDirPath();
	path.append("/readme.doc");
	QStringList s;
	s.append(path);
	process.startDetached("hh.exe", s);
}

