/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "memory_guard.h"

#include "iam_logger.h"
#include "malloc.h"

#define LOG_TAG "FINGERPRINT_AUTH_SA"

namespace OHOS {
namespace UserIam {
namespace FingerprintAuth {
MemoryGuard::MemoryGuard()
{
#ifdef CONFIG_USE_JEMALLOC_DFX_INTF
    int32_t ret1 = mallopt(M_SET_THREAD_CACHE, M_THREAD_CACHE_DISABLE);
    int32_t ret2 = mallopt(M_DELAYED_FREE, M_DELAYED_FREE_DISABLE);
    IAM_LOGI("disable thread cache and delay free, result[%{public}d, %{public}d]", ret1, ret2);
#endif
}

MemoryGuard::~MemoryGuard()
{
#ifdef CONFIG_USE_JEMALLOC_DFX_INTF
    int32_t ret = mallopt(M_FLUSH_THREAD_CACHE, 0);
    IAM_LOGI("flush thread cache, result: %{public}d", ret);
#endif
}
} // namespace FingerprintAuth
} // namespace UserIam
} // namespace OHOS