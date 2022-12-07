#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//性别类型
enum SexType {
    UNKNOWN = 0U,MALE,FEMALE
};

//员工类型
enum StaffType {
    ENGINEER,LEADER,CHAIRMAN
};

//性别
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

    //重载输入 
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

    //重载输出
    friend ostream& operator << (ostream& output, const Sex& sex) {
        switch (sex.type_) {
        case UNKNOWN:
            output << "未知";
            break;
        case MALE:
            output << "男性";
            break;
        case FEMALE:
            output << "女性";
        }
        return output;
    }

    void load(ifstream& input) {
        string sex;
        input >> sex;
        if (sex == "男性") {
            type_ = MALE;
        } else if (sex == "女性") {
            type_ = FEMALE;
        }
    }

    void save(ofstream& output) const {
        output << *this << " ";
    }
};

//员工类
class Staff {
protected:
    string id_;         //编号
    string name_;       //姓名
    int age_;           //年龄
    Sex sex_;           //性别 
    
public:
    Staff(){

    }

    virtual ~Staff() {

    }

    //编辑员工信息
    virtual void edit() = 0;
    //打印员工信息
    virtual void print() const = 0;
    //将员工信息输入文件
    virtual void load(ifstream& input) = 0;
    //将员工信息从文件中输出 
    virtual void save(ofstream& output) const = 0;
    //获取员工类型
    virtual StaffType type() const = 0;
    //获取员工编号
    const string& getID() const {
        return id_;
    }

    //设置员工编号
    void setID(const string& id) {
        id_ = id;
    }

    //获取员工姓名
    const string& getName() const {
        return name_;
    }

    void editStaff() {
        cout << "编号：" << id_ << endl;
        cout << "类别：" << getTypeName() << endl;
        cout << "姓名：";
        cin >> name_;
        cout << "性别：（输入提示：1、男性，2、女性）";
        cin >> sex_;
        cout << "年龄：";
        cin >> age_;
    }

    void printStaff() const {
        cout << "编号：" << id_ << " ";
        cout << "类别：" << getTypeName() << " ";
        cout << "姓名：" << name_ << " ";
        cout << "性别：" << sex_ << " ";
        cout << "年龄：" << age_ << " ";
    }

	//将员工信息输入文件 
    void loadStaff(ifstream& input) {
        input >> id_;
        input >> name_;
        sex_.load(input);
        input >> age_;
    }

    //将员工信息文件中输出 
    void saveStaff(ofstream& output) const {
        output << id_ << " ";
        output << name_ << " ";
        sex_.save(output);
        output << age_ << " ";
    }

	//获取员工类型
    string getTypeName() const {
        switch (type()) {
        case ENGINEER:
            return "工程师";
        case LEADER:
            return "领导";
        case CHAIRMAN:
            return "主任工程师";
        default:
            return "未知";
        }
    }
};

//工程师类，虚继承
class Engineer : public virtual Staff {
protected:
    string major_;      //专业
    string title_;      //职称
	
public:
    Engineer() {

    }

    virtual ~Engineer() {

    }
    
    virtual StaffType type() const {
        return ENGINEER;
    }

    void editEngineer() {
        cout << "专业：";
        cin >> major_;
        cout << "职称：";
        cin >> title_;
    }

    void printEngineer() const {
        cout << "专业：" << major_ << " ";
        cout << "职称：" << title_ << " ";
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

//领导类，虚继承
class Leader : public virtual Staff {
protected:
    string job_;            //职务
    string department_;     //部门
	
public:
    Leader() {

    }

    virtual ~Leader() {

    }
    
    virtual StaffType type() const {
        return LEADER;
    }

    void editLeader() {
        cout << "职务：";
        cin >> job_;
        cout << "部门：";
        cin >> department_;
    }

    void printLeader() const {
        cout << "职务：" << job_ << " ";
        cout << "部门：" << department_ << " ";
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

//主任工程师类，多重继承
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

//员工数组
typedef vector<Staff*> StaffArray;

//菜单
class Menu {
protected:
    StaffArray staffs_;
	
public:
    Menu() {

    }

    void run() {
        load();
        while (1) {
            cout << "#公司员工信息管理系统#" << endl;
            cout << " 1 显示员工信息" << endl;
            cout << " 2 添加员工信息" << endl;
            cout << " 3 查找员工信息" << endl;
            cout << " 4 修改员工信息" << endl;
            cout << " 5 删除员工信息" << endl;
            cout << " 0 退出系统" << endl;
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
    
    
	//得到员工编号 
    Staff* findStaffByID(string id) const {
        for (int i = 0; i < staffs_.size(); i++) {
            Staff* employee = staffs_[i];
            if (employee->getID() == id) {
                return employee;
            }
        }
        return NULL;
    }

	//得到员工姓名 
    int findStaffByName(string name, int position = 0) const {
        for (int i = position; i < staffs_.size(); i++) {
            Staff* employee = staffs_[i];
            if (employee->getName() == name) {
                return (int)i;
            }
        }
        return -1;
    }


	//展示员工信息 
    void showStaffs() const {
        cout << "#显示员工信息#" << endl;
        for ( int i = 0; i < staffs_.size(); ++i) {
            Staff* employee = staffs_[i];
            employee->print();
        }
    }

	//添加员工信息 
    void addStaff() {
            string id = generateStaffID();
            Staff* employee = generateStaff();
            if (employee) {
                employee->setID(id);
                cout << "#添加员工信息#" << endl;
                employee->edit();
                staffs_.push_back(employee);
                save();
                cout << "#新添员工信息#" << endl;
                employee->print();
            }
    }

	//添加员工编号 
    string generateStaffID() {
        cout << "#创建员工编号#" << endl;
        cout << "编号：";
        string id;
        cin >> id;
        return id;
    }

	//添加员工类型
    Staff* generateStaff() {
        cout << "#添加员工类型#" << endl;
        cout << " 1 工程师" << endl;
        cout << " 2 领导" << endl;
        cout << " 3 主任工程师" << endl;
        cout << " 0 返回" << endl;
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
            return new Engineer();//相当于Engineer e = new Engineer();return e;
        case LEADER:
            return new Leader();
        case CHAIRMAN:
            return new Chairman();
        }
        return NULL;
    }

	//寻找员工 
    void searchStaff() {
        while (1) {
            cout << "#查找员工信息#" << endl;
            cout << " 1 按编号查找" << endl;
            cout << " 2 按姓名查找" << endl;
            cout << " 0 返回" << endl;
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

	//按编号寻找员工信息 
    void searchStaffByID() {
        cout << "#按编号查找#" << endl;
        cout << "输入员工编号：";
        string id;
        cin >> id;
        Staff* employee = findStaffByID(id);
        if (employee) {
            employee->print();
        } else {
            cout << "未找到相关记录！" << endl;
        }
    }

	//按姓名寻找员工信息 
    void searchStaffByName() {
        cout << "#按姓名查找#" << endl;
        cout << "输入员工姓名：";
        string name;
        cin >> name;
        int position = findStaffByName(name);
        if (position != -1) {
            do {
                staffs_[position]->print();
                position = findStaffByName(name, position + 1);
            } while (position != -1);
        } else {
            cout << "未找到相关记录！" << endl;
        }
    }

	//更新员工信息 
    void updateStaff() {
        cout << "#修改员工信息#" << endl;
        cout << "输入员工编号：";
        string id;
        cin >> id;
        Staff* employee = findStaffByID(id);
        if (employee) {
            cout << "#当前员工信息#" << endl;
            employee->print();
            cout << endl;
            cout << "重新编辑员工信息：" << endl;
            employee->edit();
            save();
            cout << "修改成功！" << endl;
        } else {
            cout << "未找到相关记录！" << endl;
        }
    }

	//删除员工 
    void deleteStaff() {
        cout << "#删除员工信息#" << endl;
        cout << "输入员工编号：";
        string id;
        cin >> id;
        if (removeStaffByID(id)) {
            save();
            cout << "删除成功！" << endl;
        } else {
            cout << "未找到相关记录！" << endl;
        }
    }


	//通过编号删除员工信息 
    bool removeStaffByID(string id) {
        for (StaffArray::iterator iter = staffs_.begin(); iter != staffs_.end(); ++iter) {
            Staff* employee = *iter;//对迭代器解引用，并访问实际对象 
            if (employee->getID() == id) {
                delete employee;
                staffs_.erase(iter);//删除 
                return true;
            }
        }
        return false;
    }


    //向文件中输入 
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

    //从文件中输出 
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
            staffs_.pop_back();//将数据存进容器 
        }
    }
    
    virtual ~Menu() {
        //析构时释放内存
        free();
    }
};

int main() {
    Menu m;
    m.run();
    return 0;
}

