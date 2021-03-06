//
// Copyright (C) 2013 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "shill/mock_ppp_device_factory.h"

namespace shill {

namespace {

base::LazyInstance<MockPPPDeviceFactory> g_mock_ppp_device_factory
    = LAZY_INSTANCE_INITIALIZER;

}  // namespace

MockPPPDeviceFactory::MockPPPDeviceFactory() {}
MockPPPDeviceFactory::~MockPPPDeviceFactory() {}

MockPPPDeviceFactory* MockPPPDeviceFactory::GetInstance() {
  return g_mock_ppp_device_factory.Pointer();
}

}  // namespace shill
