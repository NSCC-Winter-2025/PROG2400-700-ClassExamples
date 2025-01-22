#include <iostream>
#include <memory>

struct Student {
    std::string _id;
    std::string _name;
    Student() { std::cout << "Student created" << std::endl; }
    ~Student() { std::cout << "Student destroyed" << std::endl; }
};

class SmartPtr {
    Student* _student{nullptr};

public:
    explicit SmartPtr(Student* student) : _student(student) {
    }

    SmartPtr(SmartPtr&& ptr) {
        _student = ptr._student;
        ptr._student = nullptr;
    }

    ~SmartPtr() {
        if (_student) std::cout << "deallocating student" << std::endl;
        delete _student;
    }

    Student* get() { return _student; }

    static SmartPtr make_smartptr() {
        std::cout << "allocating new student" << std::endl;
        return SmartPtr(new Student());
    }

    Student* operator->() const noexcept { return _student; }
};


int main() {
    auto print = [](auto& desc, auto& student) {
        std::cout << desc << student->_name << " (" << student->_id << ")" << std::endl;
    };

    {
        // regular pointers
        auto s = new Student();
        s->_id = "W111222";
        s->_name = "john";
        print("OLD PTR: ", s);
        // you can't forget!
        delete s;
    }
    std::cout << "--------------" << std::endl;
    {
        // custom smart pointer
        auto sp1 = SmartPtr::make_smartptr();
        sp1->_id = "W222333";
        sp1->_name = "jane";
        print("ORIGINAL: ", sp1);

        // borrow a reference to the data
        auto student = sp1.get();
        print("REFERENCED: ", student);

        // give ownership
        auto sp2 = std::move(sp1);
        print("MOVED: ", sp2);
    }
    std::cout << "--------------" << std::endl;
    {
        auto up1 = std::make_unique<Student>();
        up1->_id = "W333444";
        up1->_name = "jill";
        print("UNIQUE: ", up1);

        // borrow a reference to the data
        auto student = up1.get();
        print("REFERENCED: ", student);

        // give ownership
        auto up2 = std::move(up1);
        print("MOVED: ", up2);
    }

    return 0;
}
