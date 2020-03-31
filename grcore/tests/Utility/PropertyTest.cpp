//
// Created by Jedzia on 01.11.2018.
//

#include <cassert>
#include <cstdio>
#include <grcore/Utility/Property.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
//
#include <gtest/gtest.h>

using std::cout;
using std::endl;

TEST(Property, feed_function) {
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

    int a = 7;
    std::function<int(void)> f = [&a]() { return a; };
    auto prop = grcore::util::Property(f);

    ASSERT_EQ(a, f());
    ASSERT_EQ(a, prop.Get());
}

TEST(Property, feed_lambda) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_EQ(a, -42);
    ASSERT_EQ(a, prop.Get());
}

TEST(Property, tripped) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    a = -41;
    ASSERT_TRUE(prop.HasChanged());
}

TEST(Property, tripped_complex) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    a = -42;
    ASSERT_FALSE(prop.HasChanged());
    a = -41;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
}

TEST(Property, tripped_multiple) {
    int a = 555555555;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    a = 777777777;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    a = 666666666;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    a = 555555555;
    ASSERT_TRUE(prop.HasChanged());
    a = 555555554;
    ASSERT_TRUE(prop.HasChanged());
    a = 555555553;
    ASSERT_TRUE(prop.HasChanged());
    a = -155555555;
}

TEST(Property, released) {
    int a = 0;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    a = 0;
    ASSERT_FALSE(prop.HasChanged());
    a = 1;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
}

TEST(Property, released_multiple) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    a = -42;
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
}

TEST(Property, no_fail) {
    int i = 42;
    ASSERT_EQ(42, i);
}

class PropertySuite : public ::testing::Test {
protected:
    double m_x = 6.0;
    double getX() const {
        return m_x;
    }

protected:
    //grcore::util::Property m_prop = grcore::util::Property([]() { return 5; });
    grcore::util::Property<std::function<double(void)>> m_prop1{[&]() { return m_x; }};
    grcore::util::Property<std::function<int(void)>> m_prop2{[&]() { return m_x; }};
protected:

    virtual void TearDown() {}

    virtual void SetUp() {}
};

TEST_F(PropertySuite, TestName) {
    ASSERT_EQ(6.0, m_x);
    ASSERT_EQ(6.0, m_prop1.Get());
    ASSERT_EQ(6, m_prop2.Get());
    ASSERT_FALSE(m_prop1.HasChanged());
    ASSERT_FALSE(m_prop2.HasChanged());
    m_x = 6.001;
    ASSERT_TRUE(m_prop1.HasChanged());
    // so there is no warning caused by the double to int conversion
    ASSERT_EQ(6, m_prop2.Get());
    ASSERT_FALSE(m_prop2.HasChanged());
}
