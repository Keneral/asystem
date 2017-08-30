/*
 * Copyright (C) 2015 The Android Open Source Project
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

#define LOG_TAG "fingerprintd"

#include <cutils/log.h>
#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/PermissionCache.h>
#include <utils/String16.h>

#include <keystore/IKeystoreService.h>
#include <keystore/keystore.h> // for error codes

#include <hardware/hardware.h>
#include <hardware/fingerprint.h>
#include <hardware/hw_auth_token.h>

#include "FingerprintDaemonProxy.h"
#include "fcntl.h"
#include "cutils/properties.h"

int main() {
    ALOGI("Starting " LOG_TAG);
	//add for fingerprint compatible
	if(open("/dev/goodix_fp",O_RDONLY) <  0){
		ALOGE(LOG_TAG "open /dev/goodix_fp error\n");
	}else{
		ALOGE(LOG_TAG "open /dev/goodix_fp ok\n");
		property_set("persist.fingerprint","goodix");
	}
	if(open("/dev/madev0",O_RDONLY) < 0){
		ALOGE(LOG_TAG "open test /dev/madev0 error\n");
	}else{
		ALOGE(LOG_TAG "open /dev/madev0 ok\n");
		property_set("persist.fingerprint","microarray");
	}
	//add end
    android::sp<android::IServiceManager> serviceManager = android::defaultServiceManager();
    android::sp<android::FingerprintDaemonProxy> proxy =
            android::FingerprintDaemonProxy::getInstance();
    android::status_t ret = serviceManager->addService(
            android::FingerprintDaemonProxy::descriptor, proxy);
    if (ret != android::OK) {
        ALOGE("Couldn't register " LOG_TAG " binder service!");
        return -1;
    }

    /*
     * We're the only thread in existence, so we're just going to process
     * Binder transaction as a single-threaded program.
     */
    android::IPCThreadState::self()->joinThreadPool();
    ALOGI("Done");
    return 0;
}
