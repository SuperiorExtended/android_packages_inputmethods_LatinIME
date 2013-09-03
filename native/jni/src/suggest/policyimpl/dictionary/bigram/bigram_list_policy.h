/*
 * Copyright (C) 2013 The Android Open Source Project
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

#ifndef LATINIME_BIGRAM_LIST_POLICY_H
#define LATINIME_BIGRAM_LIST_POLICY_H

#include <stdint.h>

#include "defines.h"
#include "suggest/core/policy/dictionary_bigrams_structure_policy.h"
#include "suggest/policyimpl/dictionary/bigram/bigram_list_read_write_utils.h"

namespace latinime {

class BigramListPolicy : public DictionaryBigramsStructurePolicy {
 public:
    explicit BigramListPolicy(const uint8_t *const bigramsBuf) : mBigramsBuf(bigramsBuf) {}

    ~BigramListPolicy() {}

    void getNextBigram(int *const outBigramPos, int *const outProbability, bool *const outHasNext,
            int *const pos) const {
        const BigramListReadWriteUtils::BigramFlags flags =
                BigramListReadWriteUtils::getFlagsAndForwardPointer(mBigramsBuf, pos);
        *outBigramPos = BigramListReadWriteUtils::getBigramAddressAndForwardPointer(
                        mBigramsBuf, flags, pos);
        *outProbability = BigramListReadWriteUtils::getProbabilityFromFlags(flags);
        *outHasNext = BigramListReadWriteUtils::hasNext(flags);
    }

    void skipAllBigrams(int *const pos) const {
        BigramListReadWriteUtils::skipExistingBigrams(mBigramsBuf, pos);
    }

 private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(BigramListPolicy);

    const uint8_t *const mBigramsBuf;
};
} // namespace latinime
#endif // LATINIME_BIGRAM_LIST_POLICY_H
