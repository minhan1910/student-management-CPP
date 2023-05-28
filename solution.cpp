#include <bits/stdc++.h>

using namespace std;

// MAGIC STRING
#define endl "\n"
#define space ' '
#define YES "YES"
#define NO "NO"
    
// FOR-LOOPS
#define FOR(i,a,b) for (auto i = (a); i <= (b); ++i)
#define REVFOR(i,a,b) for (auto i = (a); i >= (b); --i)
#define spFore(a) for (const auto& it : (a)) cout << it << ' '
#define endlFore(a) for (const auto& it : (a)) cout << it << "\n"
#define endlForeMap(a) for (auto it = (a).begin(); it != (a).end(); it++) \
    cout << it->first << ' ' << it->second << endl 
#define spRevForeSet(a) for (auto ist = (a).rbegin(); it != (a).rend(); it++) \
    cout << *it << ' '

// FUNCTIONS
#define pb push_back
#define pf pop_front
#define fi first
#define se second
#define mkp make_pair
#define ep emplace
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define gcd(a, b) __gcd((a),(b))

// FAST I/O
#define op() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

// TYPES
typedef long long ll;
typedef unsigned long long ull;
typedef double d;

// MAPS
typedef map<int, int> mii;

typedef unordered_map<int, int> umii;

// SETS
typedef set<int> si;

// VECTORS
typedef vector<int> vi;
typedef vector<string> vs;

// PAIRS
typedef pair<int, int> pii;
typedef pair<d, d> pdd;

struct Student {
    string name, 
           dob, 
           address;

    double chemistryScore, 
           physicScore, 
           mathScore,
           averageScore;

    int totalScore;

    bool isPass, isVale;

    Student() {
        this->averageScore = 0;
        this->totalScore = 0;
        this->isPass = false;
        this->isVale = false;
    }

    // Student(string name, string dob, string address, double chemistryScore,
    //     double physicScore, double mathScore) {
    //     this->name = name;
    //     this->dob = dob;
    //     this->address = address;        
    //     this->chemistryScore = chemistryScore;
    //     this->physicScore = physicScore;
    //     this->mathScore = mathScore;
    // }

    void SetAverageScore(double averageScore) {
        this->averageScore = averageScore;
    }

    void SetTotalScore(int totalScore) {
        this->totalScore = totalScore;
    }

    void DisplayInformation() {
        cout << this->name << ' '
             << this->dob  << ' '
             << this->address << ' '
             << fixed << setprecision(2) << this->averageScore;  

        // if (!isVale) {
        //     if (isPass)
        //         cout << "DO";
        //     else cout << "TRUOT";
        // } 
    }    

    void SetInformation() {
        cin.ignore();

        getline(cin, this->name);
        getline(cin, this->dob);
        getline(cin, this->address);

        // cin >> this->mathScore 
        //     >> this->physicScore 
        //     >> this->chemistryScore;
        cin >> this->averageScore;
    }
};

struct StringUtil {
    int getMonthDob(const string& dob) {
        stringstream ss(dob);
        
        string word;

        string month;

        int i = 1;
        while (getline(ss, word, '/')) {

            if (i == 2) {
                if (word[0] == '0') {
                    month += to_string(word[1]);
                } else {
                    month += word;
                }
            }

            ++i;
        }

        return stoi(month);
    }
};

struct StudentController {
    const int SCORE_PASS = 24;    

    int numberOfStudents;
    vector<struct Student> students;
    vector<struct Student> studentValedictorians;
    struct StringUtil stringUtil;

    StudentController(struct StringUtil stringUtil) {
        this->numberOfStudents = 0;
        this->stringUtil = stringUtil;
    }

    StudentController(int numberOfStudents, struct StringUtil stringUtil) {
        this->numberOfStudents = numberOfStudents;
        this->stringUtil = stringUtil;
    }

    void CalculateTotalScore(struct Student& student) {
        int totalScore = student.mathScore + student.physicScore + student.chemistryScore;

        student.SetTotalScore(totalScore);
    }

    void CheckPassStudent(struct Student& student) {
        if (IsStudentPass(student)) {
            student.isPass = true;
        }
    }

    void AddNewStudent(struct Student& s) {
        this->CalculateTotalScore(s);
        this->CheckPassStudent(s);        
        this->students.pb(s);
    }

    void RemoveAllStudentsNotPass() {
        vector<struct Student> newStudents;

        for (auto it = this->students.begin(); it != this->students.end(); ++it) {
            if ((*it).averageScore >= 1.0) {
                newStudents.pb(*it);
            }
        }

        this->students = newStudents;
        this->numberOfStudents = this->students.size(); 
    }

    void PrintAllStudents() {
        // cout << "KET QUA XET TUYEN:" << endl;
        if (this->numberOfStudents > 0) {
            stable_sort(all(students), [](const struct Student& s1, const struct Student& s2) -> bool {
                string s1Address = s1.address,
                       s2Address = s2.address;

                if (s1Address == s2Address) {
                    return s1.averageScore > s2.averageScore;
                }

                return s1Address + s2Address < s2Address + s1Address;
            });

            FOR(i,0,this->students.size() - 1) {
                this->students[i].DisplayInformation();
                cout << endl;
            }
        }
    }

    void PrintAllMaxAddress() {
        unordered_map<string, int> distAddress;
        vector<pair<string, int>> vDistAddress;

        int maxv = -1;

        FOR (i,0,this->numberOfStudents - 1) {
            string address = this->students[i].address;

            if (distAddress.count(address)) {
                distAddress[address]++;
            } else {
                distAddress.insert({address, 1});
            }

            maxv = max(distAddress[address], maxv);
        }

        for (const auto& it : distAddress)
            vDistAddress.pb(it);

        sort(all(vDistAddress));

        FOR (i,0,vDistAddress.size() - 1) {
            if (vDistAddress[i].se == maxv) {
                cout << vDistAddress[i].fi << endl;
            }
        }

    }

   
    void PrintAllAprilDob() {
        FOR (i,0,this->numberOfStudents - 1) {
            int monthDob = this->stringUtil.getMonthDob(this->students[i].dob);

            if (monthDob == 4) {
                this->students[i].DisplayInformation();
                cout << endl;
            }
        }
    }

    void PrintAllGoodStudents() {
         if (this->numberOfStudents > 0) {
            FOR(i,0,this->numberOfStudents - 1) {

                string address = this->students[i].address;
                double gpa = this->students[i].averageScore;

                if (address == "Nam Dinh" && gpa >= 2.5) {
                    this->students[i].DisplayInformation();
                    cout << endl;
                }
            }
        }
    }

    void PrintAllValedictorians() {
        this->CheckValeDictorianStudent();

        cout << "DANH SACH THU KHOA :" << endl;
        if (!this->studentValedictorians.empty()) {


            int nValedictorians = this->studentValedictorians.size();
            FOR(i,0,nValedictorians - 1) {
                this->studentValedictorians[i].DisplayInformation();
                cout << endl;
            }
        }
    }

    void PrintAdmissionResult() {
        PrintAllValedictorians();
        PrintAllStudents();
    }

    int FindMaxTotalScore() {
        int maxTotalScore = -1;

        FOR (i,0,this->numberOfStudents - 1) {
            maxTotalScore = max(this->students[i].totalScore, maxTotalScore);
        }

        return maxTotalScore;
    }


    void CheckValeDictorianStudent() {
        int maxTotalScore = this->FindMaxTotalScore();
        
        FOR (i,0,this->numberOfStudents - 1) {
            if (students[i].totalScore == maxTotalScore) {     
                struct Student stdVale = students[i];          
                stdVale.isVale = true;
                this->studentValedictorians.pb(stdVale);
            }
        }
    }

    bool IsStudentPass(const struct Student& s) {
        return s.totalScore >= SCORE_PASS;
    }

};

void solve() {            
    int n; cin >> n;

    struct StringUtil stringUtil;
    struct StudentController studentController(n, stringUtil);

    FOR(i,0,n - 1) {
        struct Student s;
        s.SetInformation();    
        studentController.AddNewStudent(s);        
    }
    
    studentController.PrintAllAprilDob();
}

int main(int argc, char** argv) {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    op();
    
    solve();

    return 0;   
}  
