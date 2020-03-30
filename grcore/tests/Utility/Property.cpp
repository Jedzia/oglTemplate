//
// Created by Jedzia on 01.11.2018.
//

#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <cstdio>

#include <gtest/gtest.h>


using std::cout;
using std::endl;

TEST(Property, start) {
    //remove("backup_test.db3");
    //SQLite::Database srcDB("backup_test.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    //srcDB.exec("CREATE TABLE backup_test (id INTEGER PRIMARY KEY, value TEXT)");
    //ASSERT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (1, \"first\")"));
    //ASSERT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (2, \"second\")"));
    //EXPECT_THROW(SQLite::Backup backup(srcDB, srcDB), SQLite::Exception);
    //EXPECT_THROW(SQLite::Backup backup(srcDB, "main", srcDB, "main"), SQLite::Exception);
    //const std::string name("main");
    //EXPECT_THROW(SQLite::Backup backup(srcDB, name, srcDB, name), SQLite::Exception);
    //remove("backup_test.db3");

    int i = 1;
    ASSERT_EQ(1, i);
}

TEST(Property, no_fail) {
    int i = 42;
    ASSERT_EQ(42, i);
}

class PropertySuite : public ::testing::Test {

protected:
protected:
    virtual void TearDown() {

    }

    virtual void SetUp() {

    }

};

TEST_F(PropertySuite, TestName) {
    ASSERT_EQ(6, 6);
}
