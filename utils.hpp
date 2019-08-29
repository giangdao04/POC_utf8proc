#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "stdlib.h"
#include "stdio.h"
using namespace std;

#ifdef _WIN32
#include <os/windows/w_dirent.h>
#else
#include <dirent.h>
#endif
#include "sys/types.h"
#include "sys/sysinfo.h"

/**
 * Get all text files in a file path
 */

#if __cplusplus==201703L // C++17
#include <filesystem>
namespace fs = std::filesystem;
bool GetAllTextFilesFromPath(const std::string& path, std::vector<std::string>& output){
    if (!std::filesystem::exists(path)) {
        return false;
    }
    output.clear();
    const std::string text_suffix = ".txt";
    const size_t text_suffix_len = text_suffix.length();
    for (const auto & entry : fs::directory_iterator(path)) {
        output.emplace_back(std::move(entry.path()));
    }
       
    return true;
}
#else // C++11 is __cplusplus==201103L
bool GetAllTextFilesFromPath(const std::string& path, std::vector<std::string>& output) {
    DIR *dir;
    struct dirent *ent;
    output.clear();
    if ((dir = opendir (path.c_str())) != NULL) {
        const std::string text_suffix = ".txt";
        const size_t text_suffix_len = text_suffix.length();
        while ((ent = readdir (dir)) != NULL) {
            std::string file_name(ent->d_name);
            if (file_name.length() < text_suffix_len) {
                continue;
            }
            if (0 != file_name.compare (file_name.length() - text_suffix_len, 
                text_suffix_len, text_suffix)) {
                continue;
            }
            // Join path to image to image
            if (path.back() == '/') {
                auto full_path = path + std::move(file_name);
                output.emplace_back(std::move(full_path));
            } else {
                auto full_path = path + "/" + std::move(file_name);
                output.emplace_back(std::move(full_path));
            }
            
        }
        closedir (dir);
        return true;
    } else {
        /* could not open directory */
        perror ("");
        return false;
    }
}
#endif

string GetLanguage(string file_path) {
    auto start = file_path.find_last_of('/') + 1;
    return file_path.substr(start, file_path.find('.') - start);
}

std::vector<std::string> SplitString( std::string const& original, const char separator=',') {
    std::vector<std::string> results;
    std::string::const_iterator start = original.begin();
    std::string::const_iterator end = original.end();
    std::string::const_iterator next = std::find( start, end, separator );
    while ( next != end ) {
        results.push_back( std::string( start, next ) );
        start = next + 1;
        next = std::find( start, end, separator );
    }
    results.push_back( std::string( start, next ) );
    return results;
}



struct sysinfo memInfo;



int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int32_t CurrentMemoryUsed(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

