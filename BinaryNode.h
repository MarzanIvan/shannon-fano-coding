#pragma once

/*
 * MarzanIvan/CppTrees is licensed under the
 * GNU General Public License v3.0
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/
#ifdef DICTIONARY
#endif
template <class ValueType, class KeyType=ValueType>
struct binarynode {
    ValueType value;
    KeyType key;
    int TextIncludingFrequency;

    binarynode<ValueType, KeyType>* left_node;
    binarynode<ValueType, KeyType>* right_node;

    void operator=(const binarynode<ValueType, KeyType> &) = delete;

    binarynode( ValueType value,
                KeyType key,
                binarynode<ValueType, KeyType>* left_node = nullptr,
                binarynode<ValueType, KeyType>* right_node = nullptr,
                int TextIncludingFrequency = 1
    ) {
        this->value = value;
        this->key = key;
        this->left_node = left_node;
        this->right_node = right_node;
        this->TextIncludingFrequency = TextIncludingFrequency;
    }
};