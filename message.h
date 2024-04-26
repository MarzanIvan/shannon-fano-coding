//
// Created by bossm on 22/12/2023.
//

#ifndef PROJECT_MESSAGE_H
#define PROJECT_MESSAGE_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ShannonNode.h"
#include <algorithm>
#include "filesize.h"
#include <utility>
#include <vector>

namespace custom {
    class message {
    private:
        std::vector<custom::ShannonNode> ShannonNodes;
        uintmax_t LetterAmount;
        uintmax_t MessageSize;
    public:
        message() {
            ShannonNodes.reserve(255);
            MessageSize = 0;
            LetterAmount = 0;
        }

        message(const custom::message & copy) {

        }

        ~message() {

        }

        void readfile() {
            try {
                for (const auto &entry: std::filesystem::directory_iterator(std::filesystem::current_path()))
                    std::cout << entry.path() << std::endl;
                std::string path;
                std::cout << "\nEnter file path: ";
                std::getline(std::cin, path);
                std::ifstream file;
                file.open(path);
                if (!file.is_open()) {
                    std::cerr << "File is not found!\n\n";
                    readfile();
                    return;
                }
                std::filesystem::path {path};
                this->MessageSize =  std::filesystem::file_size(path);
                unsigned int* Frequencies = new unsigned int[255];
                unsigned int* p{Frequencies};
                for(size_t i = 0; i < 255; i++) {
                    p[i] = 0;
                }
                while (!file.eof()) {
                    char nextletter {0};
                    file >> nextletter;
                    ++Frequencies[(unsigned)nextletter];
                }
                file.close();
                for (int i = 0; i < 255; ++i) {
                    if (Frequencies[i]) {
                        custom::ShannonNode NewNode((char)i,Frequencies[i]);
                        NewNode.code.reserve(255);
                        ShannonNodes.push_back(NewNode);
                    }
                }
                delete Frequencies;
                LetterAmount = ShannonNodes.size();
            } catch(...) {
                std::cerr << "Ooops:(\nSomething went wrong!";
                std::terminate();
            }
        }

        void writetoconsole() {
            std::cout << "message MessageSize is: ";
            show_filesize(this->MessageSize);
            std::cout << "\ncodes:\n";
            for(auto elem : ShannonNodes) {
                std::cout << elem.letter << "(code:" << (int)elem.letter << "): " << elem.frequency << std::endl;
            }
        }

        void compress() {
            SortShannonNodes(0,ShannonNodes.size() - 1);
            ShannonCodeGenerating(0, ShannonNodes.size() - 1, 0);
            std::cout << "\n\nCodes:\n";
            for (auto elem : ShannonNodes) {
                std::cout << elem.letter << ": " << elem.code << std::endl;
            }
        }

        int CurrentCodeLevel = 0;
        void ShannonCodeGenerating(int start, int end, int GroupLevel) {
            int i{start}, j{end};
            unsigned int LeftGroupSum{ShannonNodes[i].frequency}, RightGroupSum{ShannonNodes[j].frequency};
            if(GroupLevel > CurrentCodeLevel) {
                CurrentCodeLevel = GroupLevel;
            }
            while(i < (j-1)) {
                while(LeftGroupSum > RightGroupSum && i < (j - 1)) {
                    --j;
                    RightGroupSum += ShannonNodes[j].frequency;
                }
                while(LeftGroupSum < RightGroupSum && i < (j-1)) {
                    ++i;
                    LeftGroupSum += ShannonNodes[i].frequency;
                }
            }
            if(i == start) {
                ShannonNodes[start].code.push_back('0');
            }
            else if((i - start) >= 1) {
                for(int k = start; k <= i; ++k) {
                    ShannonNodes[k].code.push_back('0');
                }
                ShannonCodeGenerating(start, i, GroupLevel + 1);
            }
            if(j == end) {
                ShannonNodes[end].code.push_back('1');
            }
            else if((end - j) >= 1) {
                for(int k = j;k <= end; ++k) {
                    ShannonNodes[k].code.push_back('1');
                }
                ShannonCodeGenerating(j, end, GroupLevel + 1);
            }
        }


        void SortShannonNodes(int low, int high) {
            int i = low;
            int j = high;
            custom::ShannonNode* middle = &ShannonNodes.operator[]((low + high) >> 1);
            do
            {
                while (ShannonNodes.operator[](i).frequency < middle->frequency) ++i;
                while (ShannonNodes.operator[](j).frequency > middle->frequency) --j;
                if (i <= j)
                {
                    auto temp = ShannonNodes.operator[](i);
                    ShannonNodes.operator[](i) = ShannonNodes.operator[](j);
                    ShannonNodes.operator[](j) = temp;
                    i++; j--;
                }
            } while (i < j);
            if (low < j) SortShannonNodes(low, j);
            if (i < high) SortShannonNodes(i, high);
        }
    };

} // custom

#endif //PROJECT_MESSAGE_H
