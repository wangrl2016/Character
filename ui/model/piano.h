//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_PIANO_H
#define CHARACTER_PIANO_H

#include "ui/model/note.h"

namespace ui {
    class Piano {
    public:
        static const int kWhiteKeysPerOctave = 7;
        static const int kBlackKeysPerOctave = 5;
        // total 128
        static const int kNumWhiteKeys = 75;
        static const int kNumBlackKeys = 53;

        enum KeyType {
            kWhiteKey,
            kBlackKey,
        };

        static bool IsWhiteKey(int key);

        static bool IsBlackKey(int key);



    private:
        static bool IsValidKey(int key) {
            return 0 <= key && key < kNumKeys;
        }

    };
}


#endif //CHARACTER_PIANO_H
