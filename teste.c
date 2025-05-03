#include <unistd.h>

int main()
{
    char *envp[] = {"/nfs/homes/cayamash/bin:/nfs/homes/cayamash/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin://nfs/homes/cayamash/Android/Sdk/platform-tools:/opt/flutter/flutter/bin:/nfs/homes/cayamash/.config/Code/User/globalStorage/github.copilot-chat/debugCommand://nfs/homes/cayamash/Android/Sdk/platform-tools:/opt/flutter/flutter/bin", NULL};
    char *args[] = {"", NULL};
    execve("/bin/bash", envp, envp);
};