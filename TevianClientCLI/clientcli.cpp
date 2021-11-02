#include "clientcli.h"

ClientCLI::ClientCLI(int argc, char** argv)
{
	connect(this, &ClientCLI::signal_postImage, &manager, &Manager::postImage);
	for (int i = 1; i < argc; i++)
	{
		QTest::qWait(2000);
		emit signal_postImage(argv[i]);
	}
}