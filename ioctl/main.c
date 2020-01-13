#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <linux/vfio.h>
#include <sys/ioctl.h>      

#define VFIO_CONTAINER_PATH "/dev/vfio/vfio"

int main(int args, char* argv[]) {
	int vfio_container_fd = open(VFIO_CONTAINER_PATH, O_RDWR);
	if (vfio_container_fd < 0) {
		fprintf(stderr, "  cannot open VFIO container, "
				"error %i (%s)\n", errno, strerror(errno));
		return -1;
	}
	fprintf(stdout, "%s():  vfio_container_fd %d, VFIO_CONTAINER_PATH %s\n", __func__, vfio_container_fd, VFIO_CONTAINER_PATH);
	/* check VFIO API version */
	int ret = ioctl(vfio_container_fd, VFIO_GET_API_VERSION);
	if (ret != VFIO_API_VERSION) {
		if (ret < 0)
			fprintf(stderr, "  could not get VFIO API version, "
					"error %i (%s)\n", errno, strerror(errno));
		else
			fprintf(stderr, "  unsupported VFIO API version!\n");
		close(vfio_container_fd);
		return -1;
	}

	return 0;
}
