#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
int main() {
	char computer[256];
	struct utsname uts;
	if (gethostname(computer,255)!=0 || uname(&uts)<0) {
		fprintf(stderr,"could not get host information \n");
		exit(1);
	}
	printf("computer host name is %s\n",computer);
	printf("system is %s on %s hardware\n", uts.sysname, uts.machine);
	printf("nodename is %s\n", uts.release, uts.version);
	exit(0);
}

