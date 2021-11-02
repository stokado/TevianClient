#include <qcoreapplication.h>
#include "clientcli.h"

int main(int argc, char** argv)
{
	QCoreApplication a(argc, argv);
	ClientCLI client(argc, argv);
	return a.exec();
}