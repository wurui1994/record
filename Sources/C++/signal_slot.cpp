// c++11 single thread version
// ref:http://quinnftw.com/c++-signals-and-slots/

#include <string>
#include <vector>
#include <iostream>
#include <functional>

template <typename R, typename... Args>
class Signal
{
private:
    using fn_t = std::function<R(Args...)>;
    std::vector<fn_t> observers;

public:
    void connect(fn_t f)
    {
        observers.push_back(f);
    }

    template <typename M, typename T>
    void connect(M f, T t)
    {
        using namespace std::placeholders;
        fn_t ff = std::bind(f, std::ref(t), _1);
        observers.push_back(ff);
    }

    void operator()(Args... a)
    {
        for (auto i : observers)
            i(a...);
    }
};

struct button
{
    Signal<void, std::string> update;

    void click()
    {
        update("clicked!");
    }
};

struct label
{
    std::string text;
    void changeText(std::string s)
    {
        text = s;
        std::cout << s << std::endl;
    }
};

int main()
{
    label label1;
    label label2;

    button button1;
    auto &update = button1.update;
    update.connect(&label::changeText, label1);
    update.connect([&](std::string s)
                   { label1.changeText(s); });
    update.connect(&label::changeText, label2);
    update.connect([](std::string)
                   { puts("hello"); });
    button1.click();
    return 0;
}