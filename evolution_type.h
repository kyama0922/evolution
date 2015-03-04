#ifndef __EVOLUTION_TYPE__
#define __EVOLUTION_TYPE__

#if defined(WIN32) || defined(WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if defined(SSE)
#include <emmintrin.h>
#include <smmintrin.h>
#endif
//-------------------------------
//	デフォルト型定義
//-------------------------------
namespace EVOLUTION{

    typedef signed char        s8;  //符号あり8bit整数型
    typedef signed short       s16; //符号あり16bit整数型
    typedef signed int         s32; //符号あり32bit整数型
    typedef signed long long   s64; //符号あり64bit整数型

    typedef unsigned char       u8;  //符号なし8bit整数型
    typedef unsigned short      u16; //符号なし16bit整数型
    typedef unsigned int        u32; //符号なし32bit整数型
    typedef unsigned long long	u64; //符号なし64bit整数型

#if defined(WIN32) | defined(WIN64)
    __declspec(align(16))
#endif
    typedef struct{
        union
        {
#if defined(SSE)
            __m128 m128;
            __m128i m128i;
#endif
            s8 s8_d[16];
            s16 s16_d[8];
            s32 s32_d[4];
            s64 s64_d[2];

            u8 u8_d[16];
            u16 u16_d[8];
            u32 u32_d[4];
            u64 u64_d[2];
        };
    }e128;//EVOLUTION128bit型


    typedef float   f32; //32bit浮動小数型 
    typedef double  f64; //64bit倍精度浮動小数型 

    typedef char    c8;  //1byte文字
    typedef wchar_t c16; //2byte文字

#if defined(UNICODE)
    typedef c16   tchar; //2byte文字
#else
    typedef c8      tchar; //1byte文字
#endif


#if defined(_X32)
    typedef unsigned int ptr_t;//32bitポインター(アーキテクチャによって変更されます)
    typedef unsigned int ptr_size_t;//32bitポインターサイズ(アーキテクチャによって変更されます)
#elif defined(_X64)
    typedef unsigned long long ptr_t;//64bitポインター(アーキテクチャによって変更されます)
    typedef unsigned long long ptr_size_t;//64bitポインターサイズ(アーキテクチャによって変更されます)
#endif

    
    static const u32 Byte = 1; //1バイト
    static const u32 KByte = 1024 * Byte;//1キロバイト
    static const u32 MByte = 1024 * KByte;//1メガバイト
    static const u32 GByte = 1024 * MByte;//1ギガバイト



#if defined(WIN32) || defined(WIN64)
#if !defined(EVOLUTION_INLINE)
    //inlineのマクロ定義
#define EVOLUTION_INLINE __inline
#endif
#else
#if !defined(EVOLUTION_INLINE)
    //inlineのマクロ定義
#define EVOLUTION_INLINE inline
#endif
#endif


    //-------------------------
    //Globally Unique Identifier
    //-------------------------
    typedef struct{
        u32  Data1;
        u16 Data2;
        u16 Data3;
        u8  Data4[8];
    }_GUID;

    //EVOLUTION GUID構造体
    typedef _GUID EVOLUTION_IID;


    //RESULT
    // S_ok = 0L,
    // S_false = 1L,
    // E_unknown = 0xFFFFFFFFL,
    // E_no_instance = 0x80004002L,
    struct _RESULT{
        enum _TYPE{
            S_ok = 0L,
            S_false = 1L,
            E_unknown = 0xFFFFFFFFL,
            E_no_instance = 0x80004002L,
        };
    };
    //RESULT 
    typedef _RESULT::_TYPE RESULT;

    //--------------------------------------------------------------------------------------------------------------------------------------
    //すべてのコンポーネント オブジェクト モデル (COM) オブジェクトは、IUnknown というインターフェイスをサポートする。
    //このインターフェイスは、オブジェクトの有効期間を制御する機能と、オブジェクトが実装する他のインターフェイスを取得する機能を提供する。
    //IUnknown は、次の 3 つのメソッドを持つ。
    //--------------------------------------------------------------------------------------------------------------------------------------
    class IUnknown
    {
    public:
        //インターフェイスの参照カウントを 1 ずつ増やす。
        virtual u32 AddRef() = 0;
        //オブジェクトが特定の COM インターフェイスをサポートしているかどうかを判別する。インターフェイスをサポートしている場合、システムはオブジェクトの参照カウントを増やす。アプリケーションは、そのインターフェイスをすぐに使える。
        virtual RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject) = 0;
        //インターフェイスの参照カウントを 1 ずつ減らす。
        virtual u32 Release() = 0;
    };

    //------------------------------------------------------------------
    //InstanceCounter
    //IUnknownを継承しているクラスの参照カウンターの管理を行う
    //------------------------------------------------------------------
    class InstanceCounter{
    private:
        u32 m_counter;

        //コピー禁止
        InstanceCounter(const InstanceCounter&){}
    public:
        InstanceCounter() :m_counter(1){

        }
        //カウントを 1 ずつ増やす。
        EVOLUTION_INLINE u32 AddRef(){
            return ++this->m_counter;
        }
        //カウントを 1 ずつ減らす。
        EVOLUTION_INLINE u32 Release(){
            return --this->m_counter;
        }

    };


    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        //IUnknown
        const EVOLUTION_IID IID_IUnknown = { 0x00000000, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
    }

    namespace FUNCTION{
        //成功したかの検証
        EVOLUTION_INLINE bool IsSucceeded(u32 hr){
            return hr >= 0;
        }

        //失敗したかの検証
        EVOLUTION_INLINE bool IsFailed(u32 hr){
            return hr < 0;
        }

        //失敗したらthrowする
        EVOLUTION_INLINE void IsFailedThrow(u32 hr){
            if( hr < 0)
            {
                throw;
            }
        }

        EVOLUTION_INLINE e128* LoadGuidtoE128(e128& _out, const EVOLUTION_IID& guid){
            _out.u64_d[0] = ((e128*)&guid)->u16_d[0];
            _out.u64_d[1] = ((e128*)&guid)->u16_d[1];
            return &_out;
        }

        //-------------------------------------------------------
        //GUIDの比較
        //-------------------------------------------------------
        EVOLUTION_INLINE bool IsEqualGuid(const EVOLUTION_IID& guid1, const EVOLUTION_IID& guid2)
        {
#if defined(SSE)
            e128 guid1_128, guid2_128;
            LoadGuidtoE128(guid1_128 , guid2);
            LoadGuidtoE128(guid2_128 , guid2);
            __m128i ret = _mm_cmpeq_epi64(guid1_128.m128i, guid2_128.m128i);
            return ret.m128i_u64[0] == ret.m128i_u64[1];
#else
            if (guid1.Data1 != guid2.Data1)
            {
                return false;
            }
            if (guid1.Data2 != guid2.Data2)
            {
                return false;
            }
            if (guid1.Data3 != guid2.Data3)
            {
                return false;
            }

            u32* guid1_data4 = (u32*)&guid1.Data4[0];
            u32* guid2_data4 = (u32*)&guid2.Data4[0];
            if (*guid1_data4++ != *guid2_data4++)
            {
                return false;
            }

            if (*guid1_data4 != *guid2_data4)
            {
                return false;
            }
            return true;
#endif
        }

    }
}

#ifndef EVOLUTION_EQUALGUID
//GUIDのチェック
#define EVOLUTION_EQUALGUID(guid1 ,guid2) ::EVOLUTION::FUNCTION::IsEqualGuid(guid1 ,guid2)
#endif

#ifndef EVOLUTION_SUCCEEDED
//成功したかの検証
#define EVOLUTION_SUCCEEDED(hr) ::EVOLUTION::FUNCTION::IsSucceeded(hr)
#endif


#ifndef EVOLUTION_FAILED
//失敗したかの検証
#define EVOLUTION_FAILED(hr) ::EVOLUTION::FUNCTION::IsFailed(hr)
#endif

#ifndef EVOLUTION_ENABLE_STATE
//BitのOn
#define EVOLUTION_ENABLE_STATE(VALUE , FLG) (VALUE |= FLG)
#endif


#ifndef EVOLUTION_DISABLED_STATE
//BitのOff
#define EVOLUTION_DISABLED_STATE(VALUE , FLG) (VALUE =  ~(~VALUE | FLG))
#endif


#ifndef EVOLUTION_IS_STATE
//BitのFlagCheck
#define EVOLUTION_IS_STATE(VALUE , FLG) ((VALUE & FLG) == FLG)
#endif

#ifndef EVOLUTION_IS_NOT_STATE
//BitのFlagCheck
#define EVOLUTION_IS_NOT_STATE(VALUE , FLG) ((VALUE & FLG) != FLG)
#endif

#ifndef EVOLUTION_DELETE
//DeleteしてポインタをNullにします
#define EVOLUTION_DELETE(p) {if(p != nullptr){delete p; p = nullptr;}}
#endif

#ifndef EVOLUTION_DELETE_ARRAY
//配列DeleteしてポインタをNullにします
#define EVOLUTION_DELETE_ARRAY(p) {if(p != nullptr){delete [] p; p = nullptr;}}
#endif

#ifndef EVOLUTION_RELEASE
//ReleaseしてポインタをNullにします
#define EVOLUTION_RELEASE(p) {if(p != nullptr){p->Release(); p = nullptr;}}
#endif


#ifndef EVOLUTION_NOT_DESTRUCTOR
//デストラクタの禁止
#define EVOLUTION_NOT_DESTRUCTOR(CLASS_NAME) protected: virtual ~CLASS_NAME(){}
#endif


#ifndef EVOLUTION_ARRAYSIZE
//配列のサイズの取得
#define EVOLUTION_ARRAYSIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif

#ifndef EVOLUTION_MAX
#define EVOLUTION_MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif                     

#ifndef EVOLUTION_MIN     
#define EVOLUTION_MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif



//Newが定義されていなかった時用
#ifndef NEW

#if defined(_DEBUG)

#if defined(WIN32) || defined(WIN64)
#include <crtdbg.h>
#define NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW new
#endif//!defined(WIN32) || defined(WIN64)
#else 
#define NEW new
#endif //defined(_DEBUG)
#endif //!NEW


#endif// !__EVOLUTION_TYPE__