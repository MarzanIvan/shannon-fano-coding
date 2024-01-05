//
// Created by bossm on 22/12/2023.
//

#ifndef PROJECT_SHANNONNODE_H
#define PROJECT_SHANNONNODE_H

#include <string>

namespace custom {

    struct ShannonNode {

        char letter;
        int frequency;
        std::string code;

        ShannonNode() {
            this->letter = 0;
            code = "";
            frequency = 0;
        }

        ShannonNode(char letter) {
            this->letter = letter;
            code = "";
            frequency = 0;
        }

        ShannonNode(char letter, int frequency) {
            this->letter = letter;
            code = "";
            this->frequency = frequency;
        }

        ShannonNode(const ShannonNode& node) {
            this->letter = node.letter;
            this->frequency = node.frequency;
            this->code = node.code;
        }

        ShannonNode operator=(ShannonNode& node) {
            this->letter = node.letter;
            this->frequency = node.frequency;
            this->code = node.code;
            return node;
        }



        void SetCode(bool code, int level) {
            this->code[level] = char(code);
        }

        bool operator==(ShannonNode& node) {
            if (this->letter == node.letter) {
                return true;
            } else {
                return false;
            }
        }

        bool operator<(ShannonNode& node) {
            if (this->frequency < node.frequency) {
                return true;
            } else {
                return false;
            }
        }

        bool operator>(ShannonNode& node) {
            if (this->frequency > node.frequency) {
                return true;
            } else {
                return false;
            }
        }

    };

} // custom

#endif //PROJECT_SHANNONNODE_H
