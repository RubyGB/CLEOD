#include "mcleodide.h"
#include "ui_mcleodide.h"
#include "Frontend/Scanner.h"
#include "MiddleEnd/Compiler.h"
#include "Backend/VirtualMachine.h"
#include "dialog.h"

McleodIDE::McleodIDE(QWidget *parent) : QMainWindow(parent), ui(new Ui::McleodIDE) {
    ui->setupUi(this);
    setAcceptDrops(true);
    setWindowIcon(QIcon(":/mcleod.png"));
    setWindowTitle("Mcleod IDE");
    SetupTabWidget();
    SetupFileDock();
    CreateDocWindows();
    CreateFile();
    SetupMenu();
    setCentralWidget(tabs);
    tabs->currentWidget()->setFocus();
}

McleodIDE::~McleodIDE()
{
    delete ui;
}

void McleodIDE::SetupTabWidget(){
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);
    tabs->setTabShape(QTabWidget::Triangular);
    tabs->setAutoFillBackground(true);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(Close(int)));
    QToolButton* newTab_button = new QToolButton;
    newTab_button -> setText("+");
    tabs->setCornerWidget(newTab_button, Qt::TopRightCorner);
    connect(newTab_button, SIGNAL(clicked()),this, SLOT(CreateFile()));
}

void McleodIDE::SetupFileDock(){
    file_system_model = new QDirModel;
    file_system_view  = new QTreeView;
    file_system_view->setModel(file_system_model);
    file_system_view->setRootIndex(file_system_model->index("/home"));
    file_system_view->setColumnHidden(1, true);
    file_system_view->setColumnHidden(2, true);
    file_system_view->setColumnHidden(3, true);
    file_system_view->setHeaderHidden(true);
    connect(file_system_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OpenFile(QModelIndex)));

    file_explorer_dock = new QDockWidget("Project", this);

    file_explorer_dock->setWidget(file_system_view);
    file_explorer_dock->setFeatures(QDockWidget::DockWidgetClosable);
    file_explorer_dock->hide();

    addDockWidget(Qt::LeftDockWidgetArea, file_explorer_dock);
}

void McleodIDE::CreateDocWindows(){
    opened_docs_widget = new QListWidget;

    connect(tabs->tabBar(),      SIGNAL(tabMoved(int, int)),            this, SLOT(ChangeTabIndexInList(int, int)));
    connect(opened_docs_widget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(UpdateCurrentIndex(QListWidgetItem*)));
    connect(opened_docs_widget, SIGNAL(currentRowChanged(int)),        tabs, SLOT(setCurrentIndex(int)));
    connect(tabs->tabBar(),      SIGNAL(currentChanged(int)),           this, SLOT(UpdateCurrentIndex(int)));
    connect(tabs->tabBar(),      SIGNAL(tabCloseRequested(int)),        this, SLOT(UpdateCurrentIndexOnDelete(int)));

    opened_docs_dock  = new QDockWidget("Open Documents", this);
    opened_docs_dock->setWidget(opened_docs_widget);
    opened_docs_dock->setFeatures(QDockWidget::DockWidgetClosable);
    opened_docs_dock->hide();
    addDockWidget(Qt::RightDockWidgetArea, opened_docs_dock);

//    QDockWidget *dock = new QDockWidget(tr("console output"), this);
//    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    consoleOutput = new QListWidget(dock);
//    consoleOutput->addItems(QStringList() << "need to deal with this later, just trying to build console right now");
//    dock->setWidget(consoleOutput);
//    addDockWidget(Qt::RightDockWidgetArea, dock);
//    viewMenu->addAction(dock->toggleViewAction());

//    dock = new QDockWidget(tr("file directory"), this);
//    fileDirectory = new QListWidget(dock);
//    fileDirectory->addItems(QStringList() << "need to deal with this later");
//    dock->setWidget(fileDirectory);
//    addDockWidget(Qt::RightDockWidgetArea, dock);
//    viewMenu->addAction(dock->toggleViewAction());
}

void McleodIDE::SetupMenu(){
    QMenu* fileMenu = new QMenu("File");
    QMenu* editMenu = new QMenu("Edit");
    QMenu* viewMenu = new QMenu("View");

    fileMenu->addAction("New File",   this, SLOT(CreateFile()));
    fileMenu->addAction("Open File",  this, SLOT(OpenFile()));
    fileMenu->addSeparator();
    fileMenu->addAction("Save File",  this, SLOT(SaveFile()),Qt::CTRL + Qt::Key_S);
    fileMenu->addAction("Save As...", this, SLOT(SaveFileAs()));
    fileMenu->addSeparator();
    fileMenu->addAction("Compile & Execute", this, SLOT(CompileAndExecute()));
    fileMenu->addSeparator();
    fileMenu->addAction("Close", this, SLOT(Close()));

    editMenu->addAction("Cut",this, SLOT(Cut()));
    editMenu->addAction("Copy",this, SLOT(Copy()),Qt::CTRL + Qt::Key_C);
    editMenu->addAction("Paste",this, SLOT(Paste()),Qt::CTRL + Qt::Key_V);
    editMenu->addAction("Undo",this, SLOT(Undo()));
    editMenu->addAction("Redo",this, SLOT(Redo()));

    viewMenu->addAction(file_explorer_dock->toggleViewAction());
    viewMenu->addAction(opened_docs_dock->toggleViewAction());

    ui->menubar->addMenu(fileMenu);
    ui->menubar->addMenu(editMenu);
    ui->menubar->addMenu(viewMenu);
}

void McleodIDE::ChangeTabIndexInList(int old_index, int new_index) {
    QListWidgetItem* first_item  = opened_docs_widget->takeItem(old_index);
    opened_docs_widget->insertItem(new_index, first_item);
}

void McleodIDE::UpdateCurrentIndex(QListWidgetItem* current_item) {
    int index = current_item->listWidget()->row(current_item);
    tabs->setCurrentIndex(index);
}

void McleodIDE::UpdateCurrentIndex(int new_selection_index) {

    opened_docs_widget->setCurrentRow(new_selection_index);

    QString file = tabs->tabBar()->tabText(new_selection_index);
    QString file_extension = QFileInfo(file).suffix();
}

void McleodIDE::UpdateCurrentIndexOnDelete(int) {
    opened_docs_widget->setCurrentRow(opened_docs_widget->count() - 1);
}

void McleodIDE::CreateFile() {
    TextEditor* new_text_edit = new TextEditor;
    int index = tabs->addTab(new_text_edit, "untitled");
    tabs->setCurrentIndex(index);
    tabs->setTabToolTip(index, "");
    tabs->setTabWhatsThis(index, "No changes");

    QListWidgetItem* new_item = new QListWidgetItem;
    new_item->setText(tabs->tabText(index));
    new_item->setToolTip(tabs->tabToolTip(index));
    opened_docs_widget->addItem(new_item);
    UpdateCurrentIndex(index);
}

void McleodIDE::OpenFile(){
    QString filePath = QFileDialog::getOpenFileName(this, "Choose File", "/home");
    if(filePath.isEmpty())
        return;
    OpenFile(filePath);
}

void McleodIDE::OpenFile(const QString& filepath){
    for (int i = 0; i < tabs->count(); ++i)
        if (tabs->tabToolTip(i) == filepath) {
            QMessageBox::warning(this, "Duplicate", "Opened already",
                                          QMessageBox::Ok);
            return;
        }

    QString filename =
            filepath.section("/",-1,-1);
    QFile file(filepath);

    if (file.open(QIODevice::ReadOnly)) {
        TextEditor* temp_text = (TextEditor*)tabs->currentWidget();
        if (temp_text->document()->isEmpty() &&
            tabs->tabToolTip(tabs->currentIndex()) == "" &&
            tabs->tabText(tabs->currentIndex()) == "untitled") {
            delete tabs->widget(tabs->currentIndex());
        }

        TextEditor* new_text_edit = new TextEditor;
        QString content = file.readAll();
        file.close();
        new_text_edit->appendPlainText(content);
        int index = tabs->addTab(new_text_edit, filename);
        tabs->setCurrentIndex(index);
        tabs->setTabToolTip(index, filepath);
        tabs->setTabWhatsThis(index, "No changes");
        QListWidgetItem* new_item = new QListWidgetItem;
        new_item->setText(tabs->tabText(index));
        new_item->setToolTip(tabs->tabToolTip(index));
        opened_docs_widget->addItem(new_item);

        tabs->setTabWhatsThis(index, "No changes");
    } else {
        (new QErrorMessage(this))->showMessage("Cannot open file!");
        return;
    }
}

void McleodIDE::OpenFile(QModelIndex file_index){
    if(!file_system_model->isDir(file_index))
        OpenFile(file_system_model->filePath(file_index));
}

void McleodIDE::SaveFile()
{
    if (tabs->tabToolTip(tabs->currentIndex()) == "") {
        SaveFileAs();
        return;
    }
    QString filepath = tabs->tabToolTip(tabs->currentIndex());
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(((TextEditor*)tabs->currentWidget())->document()->toPlainText().toUtf8()); // unsafe getting!
        file.close();
        tabs->setTabWhatsThis(tabs->currentIndex(), "No changes");
    } else {
        (new QErrorMessage(this))->showMessage("Cannot save file!");
        return;
    }
}

void McleodIDE::SaveFileAs()
{  
    QString filename = tabs->tabText(tabs->currentIndex());
    QString filepath = QFileDialog::getSaveFileName(this, "Save " + filename, "/home/" + filename);
    if (filepath.isEmpty()){
        return;
    } else {
        QFile file(filepath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(((TextEditor*)tabs->currentWidget())->document()->toPlainText().toUtf8()); // unsafe getting!
            file.close();
        } else {
            (new QErrorMessage(this))->showMessage("Cannot save file!");
            return;
        }
    }
    filename = filepath.section("/",-1,-1);
    tabs->tabBar()->setTabText(tabs->currentIndex(), filename);
    tabs->tabBar()->setTabToolTip(tabs->currentIndex(), filepath);
    tabs->setTabWhatsThis(tabs->currentIndex(), "No changes");
}

void McleodIDE::Close(int index_) {
    if (tabs->tabWhatsThis(tabs->currentIndex()) != "No changes") {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Saving changes", "Save changes before closing?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            SaveFile();
        }
    }
    delete tabs->widget(index_);

    DeleteTabFromList(index_);

    if (!tabs->count())
        CreateFile();
    tabs->currentWidget()->setFocus();
}

void McleodIDE::DeleteTabFromList(int index) {
    QListWidgetItem* temp_item = opened_docs_widget->takeItem(index);
    delete temp_item;
}

void McleodIDE::Close() {
    Close(tabs->currentIndex());
}

void McleodIDE::Cut(){
    ((TextEditor*)tabs->currentWidget())->cut();
}
void McleodIDE::Copy(){
    ((TextEditor*)tabs->currentWidget())->copy();
}
void McleodIDE::Paste(){
    ((TextEditor*)tabs->currentWidget())->paste();
}
void McleodIDE::Undo(){
    ((TextEditor*)tabs->currentWidget())->undo();
}
void McleodIDE::Redo(){
    ((TextEditor*)tabs->currentWidget())->redo();
}

void McleodIDE::CompileAndExecute() {
    //  init dialog and clear output stream
    dialog = new Dialog(this);
    dialog->show();
    consoleStream.str("");

    try {
        Scanner s(tabs->tabToolTip(tabs->currentIndex()).toStdString());
        Compiler c(s.scanTokens());
        Bytecode bc = c.compile();

        VirtualMachine vm(bc, consoleStream);
        vm.execute();
    }
    catch(ByteOutOfRangeException &be) {
        consoleStream << be.what() << std::endl;
    }
    catch(CompilationException &ce) {
        consoleStream << ce.what() << std::endl;
    }
    catch(ExecutionException &ee) {
        consoleStream << ee.what() << std::endl;
    }

    QPlainTextEdit *qpte = dialog->findChild<QPlainTextEdit *>("plainTextEdit");
    qpte->setPlainText(QString(consoleStream.str().c_str()));
}
