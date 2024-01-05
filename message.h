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
#include <vector>
#include <algorithm>
#include "Dictionary.h"

namespace custom {

    class message {
    private:
        std::string* data;
    public:
        message() {
            data = nullptr;
        }

        message(const custom::message & copy) {
            if (copy.data) {
                this->data = new std::string(*copy.data);
            } else {
                this->data = nullptr;
            }
        }

        ~message() {
            if (data) {
                delete data;
            }
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
                data = new std::string();
                while (!file.eof()) {
                    file >> *data;
                }
                file.close();
            } catch(...) {
                std::cerr << "Ooops:(\nSomething went wrong!";
                std::terminate();
            }
        }

        void writetoconsole() {
            std::cout << "Your message is: \nmessage start:[";
            for(auto letter : *data) {
                std::cout << letter;
            }
            std::cout << "]: message end\n";
        }

        void readconsole() {
            try {
                std::cout << "Enter a message(UTF-8): ";
                data = new std::string();
                std::cin >> *data;
            } catch(...) {
                std::cerr << "Error has been happened while you had entered message.";
                std::terminate();
            }
        }

        void compress() {
            binarytree<char,char>* dictionary = new binarytree<char,char>;
            for (int i = 0; i < data->size();++i) {
                dictionary->insert(data->operator[](i),data->operator[](i));
            }
            std::vector<custom::ShannonNode>* nodes = dictionary->to_shannonarray();
            for (int i = 0; i < nodes->size();++i) {
                std::cout << nodes->operator[](i).letter << ": " <<  nodes->operator[](i).frequency << std::endl;
            }
        }

        void ShannonCodeGenerating(int start,int end,int arr[20], char code[20][20],int level) {
            int i=start;
            int j=end;
            int isum = arr[i],jsum = arr[j];

//            if(level>g_level) {
//                g_level = level;
//            }
            while(i<(j-1)) {
                while(isum>jsum && i<(j-1)) {
                    j--;
                    jsum += arr[j];
                }
                while(isum<jsum && i<(j-1)) {
                    i++;
                    isum += arr[i];
                }
            }

            if(i==start) {
                code[start][level]='0';
            } else if((i-start)>=1) {
                for(int k=start;k<=i;++k)
                    code[k][level] = '0';

                ShannonCodeGenerating(start,i,arr,code,level+1);
            }
            if(j==end) {
                code[end][level]='1';
            } else if((end-j)>=1) {
                for(int k=j;k<=end;++k) {
                    code[k][level] = '1';
                }
                ShannonCodeGenerating(j,end,arr,code,level+1);
            }
        }

        void quicksort(std::vector<custom::ShannonNode>* nodes, int low, int high) {
            int i = low;
            int j = high;
            custom::ShannonNode* middle = &nodes->operator[]((low + high) >> 1);
            do
            {
                while (nodes->operator[](i).frequency < middle->frequency) ++i;
                while (nodes->operator[](j).frequency > middle->frequency) --j;
                if (i <= j)
                {
                    auto temp = nodes->operator[](i);
                    nodes->operator[](i) = nodes->operator[](j);
                    nodes->operator[](j) = temp;
                    i++; j--;
                }
            } while (i < j);
            if (low < j) quicksort(nodes, low, j);
            if (i < high) quicksort(nodes, i, high);

        }

        bool DoesShannonNodesContain(char letter, std::vector<custom::ShannonNode>* nodes) {
            for (int i = 0; i < nodes->size(); ++i) {
                if (letter == nodes->operator[](i).letter) {
                    return true;
                }
            }
            return false;
        }


    };

} // custom

#endif //PROJECT_MESSAGE_H
