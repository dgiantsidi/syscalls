#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>


static int pci_get_kernel_driver_by_path(const char *filename, char *dri_name) {
	int count;
	char path[1000];
	char *name;

	if (!filename || !dri_name)
		return -1;

	count = readlink(filename, path, 1000);
	if (count >= 1000)
		return -1;
	
	/* For device does not have a driver */
	if (count < 0) {
		fprintf(stdout, "does not have a driver %s\n", strerror(errno));
		return 1;
	}

	path[count] = '\0';

	name = strrchr(path, '/');
	if (name) {
		strncpy(dri_name, name + 1, strlen(name + 1) + 1);
		return 0;
	}

	return -1;
}

int main(int args, char* argv[]) {
	char driver[1000];
	char filename[1000] = "/sys/bus/pci/devices/0000:03:00.0/driver";
	int ret = pci_get_kernel_driver_by_path(filename, driver);
	fprintf(stdout, "driver : %s\n", (ret != -1) ? driver : "failed");
	return 0;
}
