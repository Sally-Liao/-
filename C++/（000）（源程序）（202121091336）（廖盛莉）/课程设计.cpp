#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//�Ա�����
enum SexType {
    UNKNOWN = 0U,MALE,FEMALE
};

//Ա������
enum StaffType {
    ENGINEER,LEADER,CHAIRMAN
};

//�Ա�
class Sex {
private:
    SexType type_;
	
public:
    Sex()  {

    }

    ~Sex() {

    }

    SexType getType() const { 
        return type_;
    }

    //�������� 
    friend istream& operator >> (istream& input, Sex& sex) {
        int value;
        input >> value;
        switch (value) {
        case 1:
            sex.type_ = MALE;
            break;
        case 2:
            sex.type_ = FEMALE;
            break;
        }
        return input;
    }

    //�������
    friend ostream& operator << (ostream& output, const Sex& sex) {
        switch (sex.type_) {
        case UNKNOWN:
            output << "δ֪";
            break;
        case MALE:
            output << "����";
            break;
        case FEMALE:
            output << "Ů��";
        }
        return output;
    }

    void load(ifstream& input) {
        string sex;
        input >> sex;
        if (sex == "����") {
            type_ = MALE;
        } else if (sex == "Ů��") {
            type_ = FEMALE;
        }
    }

    void save(ofstream& output) const {
        output << *this << " ";
    }
};

//Ա����
class Staff {
protected:
    string id_;         //���
    string name_;       //����
    int age_;           //����
    Sex sex_;           //�Ա� 
    
public:
    Staff(){

    }

    virtual ~Staff() {

    }

    //�༭Ա����Ϣ
    virtual void edit() = 0;
    //��ӡԱ����Ϣ
    virtual void print() const = 0;
    //��Ա����Ϣ�����ļ�
    virtual void load(ifstream& input) = 0;
    //��Ա����Ϣ���ļ������ 
    virtual void save(ofstream& output) const = 0;
    //��ȡԱ������
    virtual StaffType type() const = 0;
    //��ȡԱ�����
    const string& getID() const {
        return id_;
    }

    //����Ա�����
    void setID(const string& id) {
        id_ = id;
    }

    //��ȡԱ������
    const string& getName() const {
        return name_;
    }

    void editStaff() {
        cout << "��ţ�" << id_ << endl;
        cout << "���" << getTypeName() << endl;
        cout << "������";
        cin >> name_;
        cout << "�Ա𣺣�������ʾ��1�����ԣ�2��Ů�ԣ�";
        cin >> sex_;
        cout << "���䣺";
        cin >> age_;
    }

    void printStaff() const {
        cout << "��ţ�" << id_ << " ";
        cout << "���" << getTypeName() << " ";
        cout << "������" << name_ << " ";
        cout << "�Ա�" << sex_ << " ";
        cout << "���䣺" << age_ << " ";
    }

	//��Ա����Ϣ�����ļ� 
    void loadStaff(ifstream& input) {
        input >> id_;
        input >> name_;
        sex_.load(input);
        input >> age_;
    }

    //��Ա����Ϣ�ļ������ 
    void saveStaff(ofstream& output) const {
        output << id_ << " ";
        output << name_ << " ";
        sex_.save(output);
        output << age_ << " ";
    }

	//��ȡԱ������
    string getTypeName() const {
        switch (type()) {
        case ENGINEER:
            return "����ʦ";
        case LEADER:
            return "�쵼";
        case CHAIRMAN:
            return "���ι���ʦ";
        default:
            return "δ֪";
        }
    }
};

//����ʦ�࣬��̳�
class Engineer : public virtual Staff {
protected:
    string major_;      //רҵ
    string title_;      //ְ��
	
public:
    Engineer() {

    }

    virtual ~Engineer() {

    }
    
    virtual StaffType type() const {
        return ENGINEER;
    }

    void editEngineer() {
        cout << "רҵ��";
        cin >> major_;
        cout << "ְ�ƣ�";
        cin >> title_;
    }

    void printEngineer() const {
        cout << "רҵ��" << major_ << " ";
        cout << "ְ�ƣ�" << title_ << " ";
    }

	
    void loadEngineer(ifstream& input) {
        input >> major_;
        input >> title_;
    }

    void saveEngineer(ofstream& output) const {
        output << major_ << " ";
        output << title_ << " ";
    }

    virtual void edit() {
        editStaff();
        editEngineer();
    }

    virtual void print() const {
        printStaff();
        printEngineer();
        cout << endl;
    }

    virtual void load(ifstream& input) {
        loadStaff(input);
        loadEngineer(input);
    }

    virtual void save(ofstream& output) const {
        saveStaff(output);
        saveEngineer(output);
    }
};

//�쵼�࣬��̳�
class Leader : public virtual Staff {
protected:
    string job_;            //ְ��
    string department_;     //����
	
public:
    Leader() {

    }

    virtual ~Leader() {

    }
    
    virtual StaffType type() const {
        return LEADER;
    }

    void editLeader() {
        cout << "ְ��";
        cin >> job_;
        cout << "���ţ�";
        cin >> department_;
    }

    void printLeader() const {
        cout << "ְ��" << job_ << " ";
        cout << "���ţ�" << department_ << " ";
    }

    void loadLeader(ifstream& input) {
        input >> job_;
        input >> department_;
    }

    void saveLeader(ofstream& output) const {
        output << job_ << " ";
        output << department_ << " ";
    }

    virtual void edit() {
        editStaff();
        editLeader();
    }

    virtual void print() const {
        printStaff();
        printLeader();
        cout << endl;
    }

    virtual void load(ifstream& input) {
        loadStaff(input);
        loadLeader(input);
    }

    virtual void save(ofstream& output) const {
        saveStaff(output);
        saveLeader(output);
    }
};

//���ι���ʦ�࣬���ؼ̳�
class Chairman : public Leader, public Engineer {
public:
    Chairman() {

    }

    virtual ~Chairman() {

    }

    virtual void edit() {
        editStaff();
        editLeader();
        editEngineer();
    }

    virtual void print() const {
        printStaff();
        printLeader();
        printEngineer();
        cout << endl;
    }

    virtual void load(ifstream& input) {
        loadStaff(input);
        loadLeader(input);
        loadEngineer(input);
    }

    virtual void save(ofstream& output) const {
        saveStaff(output);
        saveLeader(output);
        saveEngineer(output);
    }

    virtual StaffType type() const {
        return CHAIRMAN;
    }
};

//Ա������
typedef vector<Staff*> StaffArray;

//�˵�
class Menu {
protected:
    StaffArray staffs_;
	
public:
    Menu() {

    }

    void run() {
        load();
        while (1) {
            cout << "#��˾Ա����Ϣ����ϵͳ#" << endl;
            cout << " 1 ��ʾԱ����Ϣ" << endl;
            cout << " 2 ���Ա����Ϣ" << endl;
            cout << " 3 ����Ա����Ϣ" << endl;
            cout << " 4 �޸�Ա����Ϣ" << endl;
            cout << " 5 ɾ��Ա����Ϣ" << endl;
            cout << " 0 �˳�ϵͳ" << endl;
            int option;
            cin >> option;
            switch (option) {
            case 1:
                showStaffs();
                break;
            case 2:
                addStaff();
                break;
            case 3:
                searchStaff();
                break;
            case 4:
                updateStaff();
                break;
            case 5:
                deleteStaff();
                break;
            case 0:
                return;
            }
        }
    }
    
    
	//�õ�Ա����� 
    Staff* findStaffByID(string id) const {
        for (int i = 0; i < staffs_.size(); i++) {
            Staff* employee = staffs_[i];
            if (employee->getID() == id) {
                return employee;
            }
        }
        return NULL;
    }

	//�õ�Ա������ 
    int findStaffByName(string name, int position = 0) const {
        for (int i = position; i < staffs_.size(); i++) {
            Staff* employee = staffs_[i];
            if (employee->getName() == name) {
                return (int)i;
            }
        }
        return -1;
    }


	//չʾԱ����Ϣ 
    void showStaffs() const {
        cout << "#��ʾԱ����Ϣ#" << endl;
        for ( int i = 0; i < staffs_.size(); ++i) {
            Staff* employee = staffs_[i];
            employee->print();
        }
    }

	//���Ա����Ϣ 
    void addStaff() {
            string id = generateStaffID();
            Staff* employee = generateStaff();
            if (employee) {
                employee->setID(id);
                cout << "#���Ա����Ϣ#" << endl;
                employee->edit();
                staffs_.push_back(employee);
                save();
                cout << "#����Ա����Ϣ#" << endl;
                employee->print();
            }
    }

	//���Ա����� 
    string generateStaffID() {
        cout << "#����Ա�����#" << endl;
        cout << "��ţ�";
        string id;
        cin >> id;
        return id;
    }

	//���Ա������
    Staff* generateStaff() {
        cout << "#���Ա������#" << endl;
        cout << " 1 ����ʦ" << endl;
        cout << " 2 �쵼" << endl;
        cout << " 3 ���ι���ʦ" << endl;
        cout << " 0 ����" << endl;
        int option;
        cin >> option;
        Staff* employee = NULL;
        switch (option) {
        case 1:
            employee = createStaff(ENGINEER);
            break;
        case 2:
            employee = createStaff(LEADER);
            break;
        case 3:
            employee = createStaff(CHAIRMAN);
            break;
        }
        return employee;
    }
    
    Staff* createStaff(StaffType type) {
        switch (type) {
        case ENGINEER:
            return new Engineer();//�൱��Engineer e = new Engineer();return e;
        case LEADER:
            return new Leader();
        case CHAIRMAN:
            return new Chairman();
        }
        return NULL;
    }

	//Ѱ��Ա�� 
    void searchStaff() {
        while (1) {
            cout << "#����Ա����Ϣ#" << endl;
            cout << " 1 ����Ų���" << endl;
            cout << " 2 ����������" << endl;
            cout << " 0 ����" << endl;
            int option;
            cin >> option;
            switch (option) {
            case 1:
                searchStaffByID();
                break;
            case 2:
                searchStaffByName();
                break;
            case 0:
                return;
            }
        }
    }

	//�����Ѱ��Ա����Ϣ 
    void searchStaffByID() {
        cout << "#����Ų���#" << endl;
        cout << "����Ա����ţ�";
        string id;
        cin >> id;
        Staff* employee = findStaffByID(id);
        if (employee) {
            employee->print();
        } else {
            cout << "δ�ҵ���ؼ�¼��" << endl;
        }
    }

	//������Ѱ��Ա����Ϣ 
    void searchStaffByName() {
        cout << "#����������#" << endl;
        cout << "����Ա��������";
        string name;
        cin >> name;
        int position = findStaffByName(name);
        if (position != -1) {
            do {
                staffs_[position]->print();
                position = findStaffByName(name, position + 1);
            } while (position != -1);
        } else {
            cout << "δ�ҵ���ؼ�¼��" << endl;
        }
    }

	//����Ա����Ϣ 
    void updateStaff() {
        cout << "#�޸�Ա����Ϣ#" << endl;
        cout << "����Ա����ţ�";
        string id;
        cin >> id;
        Staff* employee = findStaffByID(id);
        if (employee) {
            cout << "#��ǰԱ����Ϣ#" << endl;
            employee->print();
            cout << endl;
            cout << "���±༭Ա����Ϣ��" << endl;
            employee->edit();
            save();
            cout << "�޸ĳɹ���" << endl;
        } else {
            cout << "δ�ҵ���ؼ�¼��" << endl;
        }
    }

	//ɾ��Ա�� 
    void deleteStaff() {
        cout << "#ɾ��Ա����Ϣ#" << endl;
        cout << "����Ա����ţ�";
        string id;
        cin >> id;
        if (removeStaffByID(id)) {
            save();
            cout << "ɾ���ɹ���" << endl;
        } else {
            cout << "δ�ҵ���ؼ�¼��" << endl;
        }
    }


	//ͨ�����ɾ��Ա����Ϣ 
    bool removeStaffByID(string id) {
        for (StaffArray::iterator iter = staffs_.begin(); iter != staffs_.end(); ++iter) {
            Staff* employee = *iter;//�Ե����������ã�������ʵ�ʶ��� 
            if (employee->getID() == id) {
                delete employee;
                staffs_.erase(iter);//ɾ�� 
                return true;
            }
        }
        return false;
    }


    //���ļ������� 
    void load() {
        ifstream input;
        input.open("staffs.txt", ios::in);
        if (input.is_open()) {
            int count;
            input >> count;
            for (int i = 0; i < count; i++) {
                int type;
                input >> type;
                Staff* employee = createStaff((StaffType)type);
                if (employee) {
                    employee->load(input);
                    staffs_.push_back(employee);
                } 
            }
        }
    }

    //���ļ������ 
    void save() const {
        ofstream output;
        output.open("staffs.txt", ios::out);
        if (output.is_open()) {
            output << staffs_.size() << endl;
            for (int i = 0; i < staffs_.size(); i++) {
                Staff* employee = staffs_[i];
                output << employee->type() << " ";
                employee->save(output);
                output << endl;
            }
        }
    }


    void free() {
        while (!staffs_.empty()) {
            delete staffs_.back();
            staffs_.pop_back();//�����ݴ������ 
        }
    }
    
    virtual ~Menu() {
        //����ʱ�ͷ��ڴ�
        free();
    }
};

int main() {
    Menu m;
    m.run();
    return 0;
}

