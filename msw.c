#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>

// threshold in milliseconds for direction change
#define THRESH_MS 20

static inline long long time_ms(){
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000LL);
}

inline void event_write(const struct input_event *event) {
	if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
		exit(EXIT_FAILURE);
}

int main(void) {
	setbuf(stdin, NULL), setbuf(stdout, NULL);
	struct input_event ev;
	int prev_dir = 0;
	long long qTime = 0;
	while (fread(&ev, sizeof(struct input_event), 1, stdin) == 1) {
		if (ev.type != EV_REL || ev.code != REL_WHEEL){
			event_write(&ev);
			continue;
		}
		if ((ev.value < 0) != prev_dir && time_ms() < qTime)
			continue;
		prev_dir = ev.value < 0;
		qTime = time_ms() + THRESH_MS;
		event_write(&ev);
	}
	fprintf(stderr, "stdin got EOF. Bye Bye\n");
}
