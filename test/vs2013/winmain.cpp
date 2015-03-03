#include <evolution.h>
#include <evolution_etc.h>


using namespace EVOLUTION;
class Main{
private:
    FILE* fp;
public:
    Main() :fp(nullptr){
#if _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    }

    ~Main(){
        if (fp != nullptr)
        {
            fclose(fp);
        }
    }
    void CreateConsole(){
        AllocConsole();
        freopen_s(&fp, "CON", "w", stdout);
    }

    int main(int argc, char* args[]){

        system("pause");
        return 0;
    }
};



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    Main m;

    return m.main(0, nullptr);
}