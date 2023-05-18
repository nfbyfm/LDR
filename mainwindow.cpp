#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "punktewolke.h"
#include "scatterdatamodifier.h"

#include "QMessageBox"
#include "QFileDialog"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QList>
#include "QTranslator"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->removeToolBar(this->ui->mainToolBar);
    this->ui->action_Qt->setChecked(true);

    setup_scatter();
    setAcceptDrops(true); //accept Drag&Drop-Operations

    //detect default-language
    QString defaultLang = QLocale::system().name();
    change_language(defaultLang);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_ffnen_triggered()
{
    //open file
    QString fileName = QFileDialog::getOpenFileName(this,tr("Datei öffnen"), "", tr("txt-Datei (*.txt *.xyz)"));
    open_File(fileName);
}

//Open File
void MainWindow::open_File(QString fileName)
{
    //check if txt or xyz-File
    if(fileName.toLower().contains(".xyz") || fileName.toLower().contains(".txt"))
    {
        //if file > 10MB, show message
        QFile fi(fileName);
        if(abs((int)(fi.size())/1048576) >10)
            this->statusBar()->showMessage(tr("Datei wird eingelesen. Bitte etwas Geduld."),2000);

        Punktewolke *pw = new Punktewolke(fileName);
        modifier->addData2(pw->getdataArray());
    }
    else
    {
        this->statusBar()->showMessage(tr("Datei kann nicht geöffnet werden. Nur xyz oder txt-Dateien möglich."),3000);
    }
}


void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        if(fileName.toLower().contains(".xyz") || fileName.toLower().contains(".txt"))
        {
            //open file
            open_File(fileName);
            return;
        }
    }
    this->ui->statusBar->showMessage(tr("Es können nur txt und xyz-Dateien geöffnet werden."), 2000);
}



//close program
void MainWindow::on_action_Beenden_triggered()
{
    this->close();
}

void MainWindow::setup_scatter()
{
    graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext())
    {
        QMessageBox::warning(this,tr("Kritischer Fehler"), tr("Konnte OpenGl nicht initialisieren."));
        this->close();
    }

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);


    this->modifier = new ScatterDataModifier(graph);


    this->setCentralWidget(widget);
}

void MainWindow::on_action_Qt_triggered() //"default"-theme
{
    set_style_actions_to_false();
    this->ui->action_Qt->setChecked(true);
    this->modifier->changeTheme(0);
    this->ui->action_Hintergrund_darstellen->setChecked(false);
    this->ui->action_Gitter_darstellen->setChecked(false);
}

void MainWindow::on_action_Primary_Colors_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Primary_Colors->setChecked(true);
    this->modifier->changeTheme(1);
}

void MainWindow::on_action_Digia_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Digia->setChecked(true);
    this->modifier->changeTheme(2);
}

void MainWindow::on_action_Stone_Moss_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Stone_Moss->setChecked(true);
    this->modifier->changeTheme(3);
}

void MainWindow::on_action_Army_Blue_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Army_Blue->setChecked(true);
    this->modifier->changeTheme(4);
    this->ui->action_Hintergrund_darstellen->setChecked(true);
    this->ui->action_Gitter_darstellen->setChecked(true);
}

void MainWindow::on_action_Retro_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Retro->setChecked(true);
    this->modifier->changeTheme(5);
}

void MainWindow::on_action_Ebony_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Ebony->setChecked(true);
    this->modifier->changeTheme(6);
}

void MainWindow::on_action_Isabelle_triggered()
{
    set_style_actions_to_false();
    this->ui->action_Isabelle->setChecked(true);
    this->modifier->changeTheme(7);
}

void MainWindow::set_style_actions_to_false()
{
    this->ui->action_Qt->setChecked(false);
    this->ui->action_Primary_Colors->setChecked(false);
    this->ui->action_Digia->setChecked(false);
    this->ui->action_Stone_Moss->setChecked(false);
    this->ui->action_Army_Blue->setChecked(false);
    this->ui->action_Retro->setChecked(false);
    this->ui->action_Ebony->setChecked(false);
    this->ui->action_Isabelle->setChecked(false);

    this->ui->action_Hintergrund_darstellen->setChecked(true);
    this->ui->action_Gitter_darstellen->setChecked(true);
}

void MainWindow::on_action_ber_triggered()
{
    QMessageBox::about(this,tr("Über LDR"),tr("LDR: simpler Punktewolkenbetrachter\n\nDrehen: Rechte Maustaste gedrückt halten.\nZoom: Mausrad\n\nEs werden maximal 200'000 Punkte geladen/angezeigt."));
}

void MainWindow::on_action_Hintergrund_darstellen_triggered()
{
    bool checked = this->ui->action_Hintergrund_darstellen->isChecked();
    this->ui->action_Hintergrund_darstellen->setChecked(checked);
    this->modifier->setBackgroundEnabled(checked);
}

void MainWindow::on_action_Gitter_darstellen_triggered()
{
    bool checked = this->ui->action_Gitter_darstellen->isChecked();
    this->ui->action_Gitter_darstellen->setChecked(checked);
    this->modifier->setGridEnabled(checked);
}

void MainWindow::on_action_Englisch_triggered()
{
    //change Language to english
    change_language("en");
}

void MainWindow::on_action_Deutsch_triggered()
{
    //change language to german
    change_language("de");
}


void MainWindow::on_action_Franz_sisch_triggered()
{
    //change language to french
    change_language("fr");
}


void MainWindow::change_language(QString language)
{
    //clear language selection
    this->ui->action_Englisch->setChecked(Qt::Unchecked);
    this->ui->action_Deutsch->setChecked(Qt::Unchecked);
    this->ui->action_Franz_sisch->setChecked(Qt::Unchecked);

    if(language.toLower().contains("en"))
        this->ui->action_Englisch->setChecked(true);

    if(language.toLower().contains("de"))
        this->ui->action_Deutsch->setChecked(true);

    if(language.toLower().contains("fr"))
        this->ui->action_Franz_sisch->setChecked(true);

    //search for fitting qm-file, switchtranslator
    QStringList qmFiles = findQmFiles();

    for (int i = 0; i < qmFiles.size(); ++i) {

        if (languageMatch(language, qmFiles[i]))
        {
            //qDebug() << "default language found: " << defaultLang;//checkBox->setCheckState(Qt::Checked);
            switchTranslator(m_translator,qmFiles[i]);
        }
    }
}


QStringList MainWindow::findQmFiles()
{
    QDir dir(":/translations");
    QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files, QDir::Name);
    QMutableStringListIterator i(fileNames);
    while (i.hasNext()) {
        i.next();
        i.setValue(dir.filePath(i.value()));
    }
    return fileNames;
}

QString MainWindow::languageName(const QString &qmFile)
{
    QTranslator translator;
    translator.load(qmFile);

    return translator.translate("MainWindow", "English");
}


bool MainWindow::languageMatch(const QString& lang, const QString& qmFile)
{
    //qmFile: i18n_xx.qm
    const QString prefix = "i18n_";
    const int langTokenLength = 2; /*FIXME: is checking two chars enough?*/
    return qmFile.midRef(qmFile.indexOf(prefix) + prefix.length(), langTokenLength) == lang.leftRef(langTokenLength);
}

void MainWindow::switchTranslator(QTranslator &translator, const QString &filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);

    // load the new translator
    if(translator.load(filename))
    {
        qApp->installTranslator(&translator);
        this->ui->retranslateUi(this);
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            this->ui->retranslateUi(this);
            break;

            // this event is send, if the system, language changes
        case QEvent::LocaleChange:
        {
            QString defaultLang = QLocale::system().name();
            change_language(defaultLang);
        }
            break;
        }
    }
    QMainWindow::changeEvent(event);
}
