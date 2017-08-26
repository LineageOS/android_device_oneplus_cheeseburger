/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "healthd-dash"
#include <healthd/healthd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

using namespace android;

static int read_sysfs(const char *path, char *buf, size_t size) {
    char *cp = NULL;

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        KLOG_ERROR(LOG_TAG, "Could not open '%s'\n", path);
        return -1;
    }

    ssize_t count = TEMP_FAILURE_RETRY(read(fd, buf, size));
    if (count > 0)
        cp = (char *)memrchr(buf, '\n', count);

    if (cp)
        *cp = '\0';
    else
        buf[0] = '\0';

    close(fd);
    return count;
}


int healthd_board_battery_update(struct BatteryProperties *props)
{
    const int SIZE = 10;
    char buf[SIZE];
	int value = 0;
    if (read_sysfs("/sys/class/power_supply/battery/fastchg_status", buf, SIZE) > 0)
	{
		value = atoi(buf);
		if 
			props->maxChargingCurrent = 4000000;
		else
			props->maxChargingCurrent = 500000;
	}
    // return 0 to log periodic polled battery status to kernel log
    return 1;
}

void healthd_board_init(struct healthd_config *config) {}