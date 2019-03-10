#include "stdafx.h"
#include "CppUnitTest.h"

#include "../SimpleCore/astring.h"
#include "../SimpleCore/avector.h"
#include "../SimpleCore/types.h"
#include "../SimpleMySql/sqldatabase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleMySqlTest
{
    TEST_CLASS(SqlDatabaseTest)
    {
    public:
        //TEST_METHOD_INITIALIZE(setUp)
        //{
        //    vector_ = { 1, 2, 3, 4, 5 };
        //}

        TEST_METHOD(testAddDatabase)
        {
            SqlDatabase sqlDatabase = SqlDatabase::addDatabase("testDatabase");
            SqlDatabase sqlDatabase = SqlDatabase::addDatabase("testDatabase2");
            SqlDatabase sqlDatabase = SqlDatabase::addDatabase("testDatabase3");

        }

    };
}