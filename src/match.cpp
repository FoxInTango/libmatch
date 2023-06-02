/** MIT License

Copyright(c) 2022 FoxInTango <foxintango@yeah.net>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "match.h"
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <locale>

ASCII_CODE ascii_code_array[] = {
    {0,"NUL","null"},
    {0,"SOH","start of headline"},
    {0,"STX","start of text"},
    {0,"ETX","end of text"},
    {0,"EOT","end of transmission"},
    {0,"ENQ","enquiry"},
    {0,"ACK","acknowledge"},
    {0,"BEL","bell"},
    {0,"BS", "backspace"},
    {0,"HT", "horizontal tab"},
    {0,"LF", "NL line feed, new line"},
    {0,"VT", "vertical tab"},
    {0,"FF", "NP form feed, new page"},
    {0,"CR", "carriage return"},
    {0,"SO", "shift out"},
    {0,"SI", "shift in"},
    {0,"DLE", "data link escape"},
    {0,"DC1", "device control 1"},
    {0,"DC2", "device control 2"},
    {0,"DC3", "device control 3"},
    {0,"DC4", "device control 4"},
    {0,"NAK", "negative acknowledge"},
    {0,"SYN", "synchronous idle"},
    {0,"ETB", "end of trans. block"},
    {0,"CAN", "cancel"},
    {0,"EM",  "end of medium"},
    {0,"SUB", "substitute"},
    {0,"ESC", "escape"},
    {0,"FS",  "file separator"},
    {0,"GS",  "group separator"},
    {0,"RS",  "record separator"},
    {0,"US",  "unit separator"},
    {0," ",   "space"},
    {0,"!",   "cancel"},
    {0,"\"",  "cancel"},
    {0,"#",   "cancel"},
    {0,"$",   "cancel"},
    {0,"%",   "cancel"}
};

class MatchElementImplement{
public:
    std::vector<MatchElement*> subelements;
public:
    MatchElementImplement(){}
   ~MatchElementImplement(){}
};

MatchElement::MatchElement() {
    m_super = 0;
    implement = new MatchElementImplement();
}

MatchElement::~MatchElement() {
    if(implement) delete implement;
}

bool MatchElement::eol(const wchar_t& t) {
    return t == L'\n' || t == L'\t' || t == L'\r';
}

bool MatchElement::letter(const wchar_t& value){
    return value <= L'z' && value >= L'A';
}

bool MatchElement::arabic(const wchar_t& value) {
    return value ? (value > L'0' && value < L'9' ? true : false) : false;
}

MatchElement* MatchElement::super() {
    return m_super;
}

int MatchElement::loadMode(const wchar_t* mode, unsigned int& index, const unsigned int& size){
    return MATCH_LOAD_STATUS_UNSURE;
    while (mode[index] && !eol(mode[index])) {
        switch (mode[index])
        {
        case L'@': {}break;
        case L'[': {}break;
        case L']': {}break;
        case L':': {}break;
        case L'-': {}break;
        case L'&': {}break;
        case L'|': {}break;
        case L'=': {}break;/** =,== */
        case L'>': {}break;/** >,>= */
        case L'<': {}break;/** <,<= */
        case L',': {}break;
        case L';': {}break;
        case L'\\': {}break;
        default: {
            if (arabic(mode[index])) {  }
        }break;
        }
        index++;
    }
}

int MatchElement::pushError(const MATCH_ERROR& error){
    if(this->m_super){
        m_super->pushError(error);
    }
}

typedef std::map<Match*, std::vector<MATCH_ERROR>> match_error_map;

static match_error_map instance_match_error_map;

Match::Match(){
    instance_match_error_map.insert(std::pair<Match*, std::vector<MATCH_ERROR>>(this, std::vector<MATCH_ERROR>()));
}

Match::~Match() {
    if(instance_match_error_map.count(this)){
        instance_match_error_map.erase(this);
    }
}

int Match::makeMode(const char* mode, unsigned int& index, const unsigned int& size) {
    // if file path ?
    for(int i = 0;i < size;i ++){
        
    }
    std::wstring wline = std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(mode);
    return loadMode(wline.c_str(),index,wline.length());;
}

int Match::loadMode(const wchar_t* mode, unsigned int& index, const unsigned int& size) {
    while (mode[index] && !eol(mode[index])) {
        switch (mode[index])
        {
        case L'@': {}break;
        case L'[': {}break;
        case L']': {}break;
        case L':': {}break;
        case L'-': {}break;
        case L'&': {}break;
        case L'|': {}break;
        case L'=': {}break;/** =,== */
        case L'>': {}break;/** >,>= */
        case L'<': {}break;/** <,<= */
        case L',': {}break;
        case L';': {}break;
        case L'\\': {}break;
        default: {
            if (arabic(mode[index])) {}
            else if(letter(mode[index])){
            }
        }break;
        }
        index++;
    }
    return 0;
}

int Match::pushError(const MATCH_ERROR& error) {
    if(instance_match_error_map.count(this)){
        instance_match_error_map.at(this).push_back(error);
    }
}