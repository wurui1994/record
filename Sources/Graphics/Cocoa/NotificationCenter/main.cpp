#include "NotificationCenter.h"

int main()
{
    NotificationCenterInstance.startServer("server");
    NotificationCenterInstance.sendMessage("server","test");
    NotificationCenterInstance.runLoop();
}

