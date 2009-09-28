#include <QtGui>
#include <QtSql>
#include <QtNetwork>
#include "mainwindow.h"
#include "settingsdialog.h"
#include "downloaddialog.h"

MainWindow::MainWindow()
{
    setupUi(this);
    m_settings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
    setWindowTitle(QString("%1 [%2]").arg(QApplication::applicationName())
                   .arg(QApplication::applicationVersion()));

    QFile db_file(qApp->applicationDirPath()+QDir::separator()+"templates.db");
    if(!db_file.exists()){
        if (!db_file.open(QIODevice::WriteOnly))
         return;
        db_file.close();
    }
    QDir d;
    if(!d.exists("images"))
        d.mkdir("images");

    pathDir = m_settings->value("templatesDir","").toString();
    QDir dir;
    dir.setPath(pathDir);
    centralwidget->setEnabled(false);
    
   
    if(pathDir.isEmpty() || !dir.exists()){        
        SettingsDialog dlg(0);
        if(dlg.exec()){
            pathDir = m_settings->value("templatesDir","").toString();
            dir.setPath(pathDir);            
        }
    }
    if(!pathDir.isEmpty() && dir.exists()){
        centralwidget->setEnabled(true);
    }

    thumb=qApp->applicationDirPath()+QDir::separator()+"images"+QDir::separator();
    model= new QStandardItemModel(this);
    proxyModel=new QSortFilterProxyModel(this);
    proxyModel->setDynamicSortFilter(false);
    loadTemplates();

    sortBox->addItem(tr("All"));
    for(int i=0;i<26;i++)
        sortBox->addItem(tr("%1%2").arg(i).arg("000"));    

    connect(searchEdit,SIGNAL(textChanged(QString)),proxyModel,SLOT(setFilterWildcard(QString)));
    connect(templatesList,SIGNAL(clicked(QModelIndex)),this,SLOT(showScreen()));

    connect(sortBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(resortList(QString)));
    connect(action_Exit,SIGNAL(triggered(bool)),this,SLOT(close()));


}
void MainWindow::on_action_Download_images_triggered(){
    QMessageBox::StandardButton res;
    res = QMessageBox::warning(this, qApp->applicationName(),
                               tr("Do you want download all templates images?\n"
                                  "This may take a long time."),
                               QMessageBox::Ok
                               | QMessageBox::Cancel);
    if (res == QMessageBox::Ok){
       downloadImages();
       DownloadDialog downDlg(this);
       downDlg.append(urlList);
       if(downDlg.exec()==QDialog::Rejected){
            sortBox->setCurrentIndex(0);
            loadTemplates();
       }
   }

}
void MainWindow::downloadImages(){
    QString id_folder;
    bool ok;
    urlList.clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath()+QDir::separator()+"templates.db");
    //qDebug() << "Соединяюсь с базой данных...";
    if (!db.open()) {
        qDebug() << "Не могу соединиться:";
        qDebug() << db.lastError().text();
    }
    //qDebug() << "Соединение установлено!";
    QSqlQuery sql = QSqlQuery();
    sql.exec("SELECT name FROM templates");
    if ( sql.isActive() ) {
        while ( sql.next() ) {
            QString name = sql.value(0).toString();
            int s=name.toInt(&ok,10);
            if(!QFile::exists(thumb+name+"-m.jpg")){
                urlList << QString("http://images.templatemonster.com/screenshots/%1/%2-m.jpg")
                        .arg(qRound(s/100)*100).arg(name);
            }
            if(!QFile::exists(thumb+name+"-b.jpg")){
                urlList << QString("http://images.templatemonster.com/screenshots/%1/%2-b.jpg")
                        .arg(qRound(s/100)*100).arg(name);
            }
            qApp->processEvents();
        }
    }else{
          qDebug() << "Не могу получить данные:";
          qDebug() << sql.lastError().text();
    }

}
void MainWindow::on_openButton_clicked(){
    bool ok;
    QString ind=templatesList->currentIndex().data(0).toString();

    int s=ind.toInt(&ok,10);
    if(s<1000){
        ind=ind.rightJustified(4, '0');
    }else{
        ind=ind;
    }

    QString fName;
    if(QFile::exists(pathDir+QDir::separator()+ind+".zip")){
        fName=pathDir+QDir::separator()+ind+".zip";
    }else if(QFile::exists(pathDir+QDir::separator()+ind+".rar")){
        fName=pathDir+QDir::separator()+ind+".rar";
    }

         QStringList arguments;         
         arguments << "/c";
         arguments << fName;
         QProcess  *opnTmpl = new QProcess;
         opnTmpl->start("cmd.exe",arguments);

    qDebug() << fName;
}
void MainWindow::showScreen(){   
    QString ind=templatesList->currentIndex().data(0).toString();
    templateName->setText(tr("Template #%1").arg(ind));

    QString thumbImage;
    if(QFile::exists(thumb+ind+"-b.jpg")){
        thumbImage=thumb+ind+"-b.jpg";
    }else{
        thumbImage=":/images/NoImageBig.jpg";
    }
    QImage image(thumbImage);
    screen->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::loadTemplates(QString where){
    QStringList  itmList;
    QStringList  imgList;
    QString thumbImage;    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath()+QDir::separator()+"templates.db");
    //qDebug() << "Соединяюсь с базой данных...";
    if (!db.open()) {
        qDebug() << "Не могу соединиться:";
        qDebug() << db.lastError().text();
    }
    //qDebug() << "Соединение установлено!";
    QSqlQuery sql = QSqlQuery();
    if(where.isEmpty())
        sql.exec("SELECT name FROM templates");
    else
        sql.exec("SELECT name FROM templates WHERE serial="+where);
    if ( sql.isActive() ) {
        while ( sql.next() ) {
            QString name = sql.value(0).toString();
            if(QFile::exists(thumb+name+"-m.jpg")){
                thumbImage=thumb+name+"-m.jpg";
            }else{
                thumbImage=":/images/noimage.jpg";
            }
            //new QListWidgetItem(QIcon(thumbImage),name, tmList);
            itmList << name;
            imgList << thumbImage;
            qApp->processEvents();
        }     

    }else{
          qDebug() << "Не могу получить данные:";
          qDebug() << sql.lastError().text();
    }
    /////////////////////////////////////////////////    
    model->clear();
    model->setRowCount(itmList.size());
    model->setColumnCount(1);
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex index = model->index(i, 0);
        QString     str   = itmList.at(i);
        QString     img   = imgList.at(i);
        model->setData(index, str, Qt::DisplayRole);
        //model->setData(index, "ToolTip for " + str, Qt::ToolTipRole);
        model->setData(index, QIcon(img), Qt::DecorationRole);
        qApp->processEvents();
    }
     proxyModel->setSourceModel(model);
     templatesList->setModel(proxyModel);

}

bool MainWindow::rescan(){
    QDir dir(pathDir);
    QStringList filters;
    filters << "*.zip" << "*.rar" << "*.uha" << "*.7z";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name );

    QFileInfoList list = dir.entryInfoList();

    QProgressDialog progress(tr("Scanning templates..."), tr("Abort"), 0, list.size(), this);
    progress.setWindowTitle(qApp->applicationName());
    progress.setWindowModality(Qt::WindowModal);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath()+QDir::separator()+"templates.db");
    //qDebug() << "Соединяюсь с базой данных...";
    if (!db.open()) {
        qDebug() << "Не могу соединиться:";
        qDebug() << db.lastError().text();
        return false;
    }

    //qDebug() << "Соединение установлено!";
    QSqlQuery sql = QSqlQuery();

        QStringList dbtables = db.tables(QSql::Tables);

        if (dbtables.contains("templates", Qt::CaseInsensitive)) {
            //qDebug() <<"Таблица \"templates\" уже существует.";
            sql.exec("DROP TABLE templates");

            if ( sql.lastError().type() == QSqlError::NoError ) {
               //qDebug() <<"Удалили таблицу \"templates\" ";
            }else{
              qDebug() <<"Не могу удалить таблицу \"templates\":";
              qDebug() << sql.lastError().text();
              return false;
            }
        }
        sql.exec(
          "create table templates ( "
          "  id INTEGER PRIMARY KEY AUTOINCREMENT, "
          "  name VARCHAR(250), "
          "  serial INT(6) ) ");
        if ( sql.lastError().type() == QSqlError::NoError ) {
          //qDebug() << "Создали таблицу \"templates\".";
        }else{
          qDebug() << "Не могу создать таблицу \"templates\":";
          qDebug() << sql.lastError().text();
          return false;
        }
    QString serial;
    bool ok;
    if (sql.prepare("INSERT INTO templates VALUES (?,?,?)")) {

         for (int i = 0; i < list.size(); ++i) {
             QFileInfo fileInfo = list.at(i);

             QRegExp rx("(\\d+)");
              if(rx.exactMatch(fileInfo.baseName())){

                    if(fileInfo.baseName().length()>4){
                        serial = fileInfo.baseName().left(2);
                    }else{
                        serial = fileInfo.baseName().left(1);
                    }
                int s=fileInfo.baseName().toInt(&ok,10);
                QString nm = (s<1000) ? QString::number(s) : fileInfo.baseName();
                sql.bindValue(0, i);
                sql.bindValue(1, nm);
                sql.bindValue(2,serial);
                sql.exec();

                progress.setValue(i);
                if (progress.wasCanceled()){
                    return false;
                 }

                if ( sql.lastError().type() != QSqlError::NoError ) {
                    qDebug() <<"Не могу вставить новую запись:";
                    qDebug() <<sql.lastError().text();
                    return false;
                }
                qApp->processEvents();
            }
         }

    }else{
        qDebug() <<"Не могу подготовить запрос:";
        qDebug() <<sql.lastError().text();
        return false;
    }
    progress.setValue(list.size());    
    return true;
}

void MainWindow::resortList(const QString &serial){
    //qDebug() << serial;
    searchEdit->clear();
    QString tm;
    if(serial==tr("All")){
        loadTemplates();
    }else{
       if(serial.length()>4){
           tm = serial.left(2);
       }else{
           tm = serial.left(1);
       }
       loadTemplates(tm);
    }
}

void MainWindow::on_action_Preferences_triggered(){
    SettingsDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        pathDir = m_settings->value("templatesDir","").toString();
        QDir dir(pathDir);
        if(!pathDir.isEmpty() && dir.exists()){
            centralwidget->setEnabled(true);
        }else{
            centralwidget->setEnabled(false);
        }
    }

}
void MainWindow::on_action_Rescan_triggered(){
    QMessageBox::StandardButton res;
    res = QMessageBox::warning(this, qApp->applicationName(),
                               tr("Do you want rescan templates directory?\n"
                                  "This action will overwrite your database"),
                               QMessageBox::Ok
                               | QMessageBox::Cancel);
    if (res == QMessageBox::Ok)
        if(rescan()){
            sortBox->setCurrentIndex(0);            
            loadTemplates();
            QMessageBox::information(this,qApp->applicationName(),
                                     tr("Database update successfuly"));            
        }
}
void MainWindow::on_action_About_triggered(){
    QMessageBox::about(this,QString("%1 - %2").arg(qApp->applicationName())
                       .arg(tr("About")),QString("<h2>%1 %2</h2>"
                                            "Copyright © 2009 <b><a href='mailto:XpycT.TOP@gmail.com' style='text-decoration:none; color:#1a4d82;'>XpycT</a> & <a href='mailto:a.petrovskii@gmail.com' style='text-decoration:none; color:#1a4d82;'>ALEXANDER</a></b>. All rights reserved.<br /><br />"
                                            "%3<br /><b>Qt Open Source Edition %4</b><br />"
                                            "<br/><p>%5 : <b><a href='%6' style='text-decoration:none; color:#1a4d82;'>%6</a></b></p>")
                       .arg(qApp->applicationName()).arg(qApp->applicationVersion())
                       .arg(tr("This program used:")).arg(qVersion())
                       .arg(tr("Website")).arg(qApp->organizationDomain()));
}
void MainWindow::closeEvent(QCloseEvent *event){
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
        //qDebug() <<"Соединение с базой данных закрыто!";
        }
}
