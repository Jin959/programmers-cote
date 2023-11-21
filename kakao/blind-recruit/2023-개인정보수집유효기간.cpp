// https://school.programmers.co.kr/learn/courses/30/lessons/150370

/* 
* 테스트 17 case 다음의 예외에서 걸렸었다. 월이 12의 배수이면
* 입력값 〉 "2020.12.17", ["A 12"], ["2010.01.01 A", "2019.12.17 A"]
* 기댓값 〉 [1, 2]
* 
* 날짜 형식 객체 다 필요없다.
* 그냥 일자로 다 바꿔서 비교하는 게 코드도 짧고 시간도 덜 걸리고
* 예외 날 경우도 별로 없다.
*
* https://school.programmers.co.kr/questions/51273
* https://cheonjoosung.github.io/blog/pg-privacy
*/

// 1. terms 유효기간은 달이다. 이를 pribacy 월에 더하고 12 초과(13)이면 년을 1 더한다. 일은 -1 한다.
// 2. 모든 달은 28일 이 마지막날이다.
// 3. 오늘이 유효기간 마지막 날이면 보존한다.
// 존재하는 약관은 나오지않는다.
// 달과 월은 두자리로만 나타난다. 한자리일 경우 05.02 등.
// 파기할 privacy는 반드시 1개 이상이다.

#include <string>
#include <vector>
#include <iostream>

#define MAX_DAY 28
#define MAX_PRIVACY 100

using namespace std;

int terms[200];
int privacies_sz;
vector<int> expired; // answer

struct Date {
    int year, month, day;

    bool operator>= (Date date) const {
        if (this->year > date.year) {
            return true;
        }
        if (this->year == date.year) {
            if (this->month > date.month) return true;
            if (this->month == date.month) {
                if (this->day >= date.day) return true;
            }
        }

        return false;
    }
} today;

struct Privacy {
    Date date;
    char term;

} privacies[MAX_PRIVACY];

Date splitDate(string day) {
    day.push_back('.');
    int s = 0, e = 0;
    vector<int> v;

    while (1) {
        e = day.find('.', s);
        if (e == -1) break;
        int sz = e - s;
        string tmp = day.substr(s, sz);
        v.push_back(stoi(tmp));
        s = e + 1;
    }
    return { v[0], v[1], v[2] };
}

void splitTerms(vector<string> termvec) {
    int sz = termvec.size();
    int sep;
    for (string tar : termvec) {
        sep = tar.find(' ', 0);

        string term = tar.substr(0, 1);
        string month = tar.substr(sep + 1);
        // cout << month << endl;
        terms[term[0]] = stoi(month);
    }
}

void parsePrivacies(vector<string> pri) {
    int sz = pri.size();
    for (int i = 0; i < sz; i++) {
        string tar = pri[i];
        int sep = tar.find(' ', 0);

        int date_sz = sep;
        string date = tar.substr(0, date_sz);
        // cout << '.' << date << '.' << endl;

        char term = tar.substr(sep + 1, 1)[0];
        // cout << term << endl;
        privacies[i] = { splitDate(date), term };
    }
}

void getExpired() {
    for (int i = 0; i < privacies_sz; i++) {
        Date agreed = privacies[i].date;
        char term = privacies[i].term;

        // 1. terms 유효기간은 달이다. 이를 pribacy 월에 더하고 일은 -1 한다.
        // 여기서 일은 -1 안하고 오늘이 유효기간 보다 이상(유효기간과 같음 포함)이면 expire
        Date expire = { agreed.year, agreed.month + terms[term], agreed.day };


        // 12 초과(13)이면 년을 1 더한다. 유효기간은 100달 까지 가능함.
        if (expire.month > 12) {
            // 12의 배수일 때, 테스트 케이스 걸림. 월이 12의 배수이면 한해 더 많이 더해지고 0월이 되어벼렸다.
            if (expire.month % 12 == 0) {
                expire.year += (expire.month / 12 - 1);
                expire.month = 12;
            }
            else {
                expire.year += expire.month / 12;
                expire.month = expire.month % 12;
            }
        }
        // 3. 오늘이 유효기간 마지막 날이면 보존한다. = 오늘이 유효기간 보다 크면 expire
        // 방금, day는 유지했기 때문에 오늘이 유효기간 보다 이상(유효기간과 같음 포함)이면 expire
        if (today >= expire) {
            // cout << expire.year << ' ' << expire.month<< ' ' << expire.day << endl;
            expired.push_back(i + 1);
        }
    }
}

vector<int> solution(string today_, vector<string> terms_, vector<string> privacies_) {
    // init
    privacies_sz = privacies_.size();
    today = splitDate(today_);
    splitTerms(terms_);
    parsePrivacies(privacies_);

    getExpired();

    return expired;
}