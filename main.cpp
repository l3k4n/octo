#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QWidget main_window(nullptr);

  main_window.show();
  return app.exec();
}
