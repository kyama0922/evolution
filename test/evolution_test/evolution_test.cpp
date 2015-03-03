#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../evolution_type.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#define DEBUG_PRINT(fmt, ...)     { char message[2048]; sprintf_s(message, fmt ,__VA_ARGS__ ); Logger::WriteMessage(message);}



namespace evolution_test
{		
    TEST_CLASS(EvolutionTest)
	{
	public:



		TEST_METHOD(SSETest)
		{
			// TODO: テスト コードをここに挿入します
            __m128i v1, v2;
            v1.m128i_i64[0] = 1;
            v1.m128i_i64[1] = 1;
            v2.m128i_i64[0] = 1;
            v2.m128i_i64[1] = 1;
            __m128i ret = _mm_cmpeq_epi64(v1, v2);

            Assert::AreEqual(ret.m128i_u64[0] , ret.m128i_u64[1]);

		}


        TEST_METHOD(GUIDCmpTest)
        {
            // TODO: テスト コードをここに挿入します
            
            Assert::IsTrue(EVOLUTION_EQUALGUID(EVOLUTION::EVOLUTION_GUID::IID_IUnknown, EVOLUTION::EVOLUTION_GUID::IID_IUnknown));
            

        }
	};
}