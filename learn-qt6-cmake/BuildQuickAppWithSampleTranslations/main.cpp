#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDir>
#include <QStringList>
#include <QDebug>
#include <QLibraryInfo>

QStringList getAllFilesRecursively(const QString& dirPath,
                                  const QStringList& nameFilters = QStringList())
{
    QStringList fileList;
    QDir dir(dirPath);

    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << dirPath;
        return fileList;
    }

    // 设置过滤器（只关心文件）
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    if (!nameFilters.isEmpty()) {
        dir.setNameFilters(nameFilters);
    }

    // 首先添加当前目录的文件
    const auto files = dir.entryList();
    for (const QString& file : files) {
        fileList.append(dir.absoluteFilePath(file));
    }

    // 然后递归处理子目录
    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    const auto subdirs = dir.entryList();
    for (const QString& subdir : subdirs) {
        fileList.append(getAllFilesRecursively(dir.absoluteFilePath(subdir), nameFilters));
    }

    return fileList;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //输出资源文件里的文件列表
    const QStringList prefixes = {"qrc:/", ":/"};
    for (const QString& prefix : prefixes) {
        qDebug().noquote() << "Files under " << prefix << ":";
        foreach (const QString& file, getAllFilesRecursively(prefix)) {
            qDebug().noquote() << "  " << file;
        }
        qDebug() << ""; // 添加空行分隔不同前缀的输出
    }

    QQmlApplicationEngine engine;
    engine.setUiLanguage("en");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Translation", "Main");

    return app.exec();
}
