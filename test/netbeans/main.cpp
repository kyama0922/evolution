#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <evolution.h>
#include <vector>

/*
 * 
 */
int main(int argc, char** argv) {


    EVOLUTION::CORE::THREAD::IThreadPool* thread_pool;

    EVOLUTION::FUNCTION::CreateThreadPool(&thread_pool, EVOLUTION::KByte * 512, 10, 10000);

    class Test : public EVOLUTION::CORE::THREAD::ITask {
    public:
        int num;

        void Execute(const EVOLUTION::CORE::THREAD::IParameter* parameter, EVOLUTION::CORE::THREAD::IResult* result) {
            printf("%d\n", num);
        }
        //タスクが終了するとThreadPoolから呼び出せます。

        void OnEndExecute(const EVOLUTION::CORE::THREAD::IResult* result) {

        }
    };

    Test t[10];

    for (int i = 0; i < 10; i++) {
        t[i].num = i;
        thread_pool->TaskExecute(&t[i], nullptr);
    }

    while (thread_pool->TaskExecuteCount() != 0) {
        thread_pool->Execute(0);
    }
    
    EVOLUTION_RELEASE(thread_pool);
    return 0;
}

