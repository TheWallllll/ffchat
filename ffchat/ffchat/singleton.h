/******************************************************************************
 *
 * @file       singleton.h
 * @brief      单例类基类
 *
 * @author     TheWall
 * @date       2024/09/10
 * @history
 *****************************************************************************/
#ifndef SINGLETON_H
#define SINGLETON_H
#include <global.h>
template <typename T>
class Singleton{
    // 写成保护是为了子类可以构造
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator = (const Singleton<T>& st) = delete;
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            // 注意这里不可应用make_share，继承模板单例类的子类构造函数也为private，make_share无法访问。
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
