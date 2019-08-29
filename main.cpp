#include "utf8proc.h"
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <chrono>
#include <cstring>
#include <fstream>
#include "utils.hpp"
#include "slog.hpp"
#include <locale>
#include <numeric>
#include <iomanip>
using namespace std;
using namespace std::chrono;
const int MAXN = 1e4 + 4;
uint8_t a[MAXN];

struct CodePoint {
    bool valid;
    string cp;
    string desc;
    CodePoint(bool v, string s): valid(v), cp(s) {}
     CodePoint(bool v, string s, string d): valid(v), cp(s), desc(d) {}
};
void EncodeAndDecodeTest() {
    std::cout << "============================================================================\n\n";
    slog::info << "Testing encode and decode\n\n" << slog::endl;

    /**
     * ===================================================
     * Initialize test data
     * @ref data/codepoint/codepoint.txt
     */ 
    typedef wchar_t ucs4_t;
    vector<CodePoint> code_points;
    code_points.emplace_back(true,"a", "Valid ASCII");
    code_points.emplace_back(true,"\xc3\xb1", "Valid 2 Octet Sequence");
    code_points.emplace_back(false,"\xc3\x28", "Invalid 2 Octet Sequence");
    code_points.emplace_back(false,"\xa0\xa1", "Invalid Sequence Identifier");
    code_points.emplace_back(true,"\xe2\x82\xa1", "Valid 3 Octet Sequence");
    code_points.emplace_back(false,"\xe2\x28\xa1", "Invalid 3 Octet Sequence (in 2nd Octet)");
    code_points.emplace_back(false,"\xe2\x82\x28", "Invalid 3 Octet Sequence (in 3rd Octet)");
    code_points.emplace_back(true,"\xf0\x90\x8c\xbc", "Valid 4 Octet Sequence");
    code_points.emplace_back(false,"\xf0\x28\x8c\xbc", "Invalid 4 Octet Sequence (in 2nd Octet)");
    code_points.emplace_back(false,"\xf0\x90\x28\xbc", "Invalid 4 Octet Sequence (in 3rd Octet)");
    code_points.emplace_back(false,"\xf0\x28\x8c\x28", "Invalid 4 Octet Sequence (in 4th Octet)");
    /*===================================================*/

    vector<size_t> original_lengths;
    vector<nanoseconds> encode, validate, decode;
    for (auto &code_point : code_points) {
        original_lengths.emplace_back(code_point.cp.size());
        memset(a, 0, sizeof a);
        for (size_t i = 0; i < code_point.cp.length(); ++i) {
            a[i] = code_point.cp[i];
        }
        /*
        * ===========
        * Encode
        * ===========
        */
        uint8_t *c = a;
        utf8proc_int32_t dst;
        auto t1 = high_resolution_clock::now();
        auto encode_size_t = utf8proc_iterate(c, code_point.cp.size(), &dst);
        encode.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - t1));   

        /*
        * ===========
        * Validate
        * ===========
        */
        t1 = high_resolution_clock::now();
        auto res = utf8proc_codepoint_valid(dst);
        validate.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - t1));
        if (res != code_point.valid) slog::err << left << setw(50) << code_point.desc << "[❌]" << slog::endl;
        else slog::info << left << setw(50) << code_point.desc << "[✅]" << slog::endl;
        /*
        * ===========
        * Decode
        * ===========
        */
        t1 = high_resolution_clock::now();
        auto decode_size_t = utf8proc_encode_char(dst, a);
        decode.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - t1));
        if (code_point.valid) slog::info << "Decoded UTF-8 character looks like " <<  a << slog::endl;
    } 
    int64_t total_encode = 0;
    int64_t total_validate = 0;
    int64_t total_decode = 0;
    for (size_t i = 0; i < code_points.size(); ++i) {
        total_encode += encode[i].count();
        total_decode += decode[i].count();
        total_validate += validate[i].count();
    }
    double avg_size = 0;
    for (auto &l : original_lengths) {
        avg_size += l;
    }
    avg_size /= original_lengths.size();
    slog::info << "Encoding takes " << ((double) total_encode / encode.size()) / avg_size << " ns/byte on average." << slog::endl;
    slog::info << "Validation takes " << ((double) total_validate / validate.size()) / avg_size << " ns/byte on average." << slog::endl;
    slog::info << "Decoding takes " << ((double) total_decode / decode.size()) / avg_size << " ns/byte on average." << slog::endl;
    std::cout << "\n============================================================================\n";
}

void BenchmarkNormalization(string path_to_data="/home/giang/Project/stuff/utf8proc/data/language") {
    std::cout << "============================================================================\n\n";
    slog::info << "Benchmarking NFC normalization for different languages\n\n" << slog::endl;
    vector<string> file_names;
    GetAllTextFilesFromPath(path_to_data, file_names);
    for (auto &file_name : file_names) {
        string language = GetLanguage(file_name);
        ifstream file(file_name);
        string b; 
        vector<nanoseconds> times;
        vector<size_t> original_lengths;
        while (std::getline(file, b)) {
            original_lengths.emplace_back(b.length());
            memset(a, 0, sizeof a);
            for (size_t i = 0; i < b.length(); ++i) {
                a[i] = b[i];
            }
            uint8_t *c = a;
            
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            utf8proc_NFC(c);
            times.emplace_back(duration_cast<nanoseconds>(high_resolution_clock::now() - t1));

        }
        int64_t total = 0;
        for (auto &v : times) {
            total += v.count();
        }
        double avg_size = 0;
        for (auto &l : original_lengths) {
            avg_size += l;
        }
        avg_size /= original_lengths.size();
        slog::info << "NFC normalization for " << language << " takes " << ((double) total / times.size()) / avg_size << " ns/byte on average." << slog::endl;
        
    } 
    std::cout << "\n============================================================================\n";
}

void NormalizationMemoryUsageTest(string path_to_data="/home/giang/Project/stuff/utf8proc/data/language") {
    std::cout << "============================================================================\n\n";
    slog::info << "Memory usage for normalization\n\n" << slog::endl;
    vector<string> file_names;
    GetAllTextFilesFromPath(path_to_data, file_names);
    for (auto &file_name : file_names) {
        
        string language = GetLanguage(file_name);
        ifstream file(file_name);
        string b; 
        vector<size_t> original_lengths, normalized_lengths;
        double mem_used = 0.0f;
        bool can = true;
        while (std::getline(file, b)) {
            original_lengths.emplace_back(b.size());
            memset(a, 0, sizeof a);
            for (size_t i = 0; i < b.length(); ++i) {
                a[i] = b[i];
            }
            uint8_t *d = a;
            
            auto before = CurrentMemoryUsed();
            auto res = utf8proc_NFC(d);
            auto after = CurrentMemoryUsed();

            mem_used += after - before;
            string fin(reinterpret_cast< char const* >(res));
            normalized_lengths.emplace_back(fin.size());
        }
        
        double total = 0.0f;
        for (size_t i = 0; i < original_lengths.size(); ++i) {
            total += 1.0f *  ((double) normalized_lengths[i] - original_lengths[i]) / original_lengths[i] * 100;
        }
        slog::info << language << " saw a " << total/original_lengths.size() << 
            "\% increase in memory consumption for string storage after  NFC normalization." << slog::endl;
        slog::info << "Normalization process consumed about ~" <<  mem_used/original_lengths.size()<< "Kb/bytes of string normalized." << slog::endl;
        

    }     
    std::cout << "============================================================================\n\n";
}

void NormalizeValidation() {
    std::cout << "============================================================================\n\n";
    slog::info << "Validating normalization\n\n";
    memset(a, 0, sizeof a);
    const string kosme = "κόσμε";
    slog::info  << kosme << " with size " << kosme.length() <<slog::endl;
    assert(kosme.length() == 11);
    for (size_t i = 0; i < kosme.length(); ++i) {
        a[i] = kosme[i];
    }
    uint8_t *b = a;
    string NFC(reinterpret_cast< char const* >(utf8proc_NFC(b)));
    slog::info << "Normalization C:  " << NFC << " with size " << NFC.length() << slog::endl;
    assert(NFC.length() == 10);
    string NFD(reinterpret_cast< char const* >(utf8proc_NFD(b)));
    slog::info << "Normalization D:  " << NFD << " with size " << NFD.length() <<slog::endl;
    assert(NFD.length() == 12);
    string NFKD(reinterpret_cast< char const* >(utf8proc_NFKD(b)));
    slog::info << "Normalization KD: " << NFKD << " with size " << NFKD.length() <<slog::endl;
    assert(NFKD.length() == 12);
    string NFKC(reinterpret_cast< char const* >(utf8proc_NFKC(b)));
    slog::info << "Normalization KC: " << NFKC << " with size " << NFKC.length() <<slog::endl;
    assert(NFKC.length() == 10);
    std::cout << "============================================================================\n\n";
}
int main() { 
    BenchmarkNormalization();
    EncodeAndDecodeTest();
    NormalizationMemoryUsageTest();
    NormalizeValidation();
    return 0;
}
