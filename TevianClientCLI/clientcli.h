#include <qobject>
#include <qtestsupport_core.h>

#include "manager.h"

class ClientCLI : public QObject
{
	Q_OBJECT

public:
	ClientCLI(int argc, char** argv);

signals:
	void signal_postImage(QString);

private:
	Manager manager;
};